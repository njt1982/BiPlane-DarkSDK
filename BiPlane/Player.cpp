#include "Player.h"
#include "MyLib.h"
#include "DarkGDK.h"


Player::Player(void) {}
Player::~Player(void) {}



Player::Player(float x, float y, float groundHeight) {
	this->startX = x;
	this->startY = y;

	this->local = true;
	this->mass = 0.0f;
	this->dragCoefficient = 0.1;

	this->restartPlayer();

	this->objId = MyIdHandler::get().getObjectId();
	this->textureId = MyIdHandler::get().getImageId();

	dbLoadObject("Media/BiPlane-uv.x", this->objId);
	dbLoadImage("Media/plane.bmp", this->textureId);
	dbTextureObject(this->objId, this->textureId);


	this->shadowId = MyIdHandler::get().getObjectId();
	this->shadowTextureId = MyIdHandler::get().getImageId();

	dbMakeObjectPlain(this->shadowId, dbObjectSizeX(this->objId), dbObjectSizeZ(this->objId));
	dbPositionObject(this->shadowId, this->x, groundHeight + 0.1, 0);
	dbPointObject(this->shadowId, this->x, groundHeight + 100, 0);
	dbLoadImage("Media/shadow.png", this->shadowTextureId);
	dbTextureObject(this->shadowId, this->shadowTextureId);
	dbSetObjectTransparency(this->shadowId, 1);
}

float Player::getX(void)          { return this->x; }
float Player::getY(void)          { return this->y; }
float Player::getSpeed(void)      { return this->speed; }
float Player::getAngle(void)      { return this->angle; }
float Player::getAngleDelta(void) { return this->angleDelta; }
float Player::getMass(void)       { return this->mass; }
float Player::getThrottle(void)   { return this->throttle; }

void Player::setX(float x) { this->x = x; }
void Player::setY(float y) { this->y = y; }
void Player::setSpeed(float speed) { this->speed = speed; }
void Player::setAngle(float angle) { this->angle = angle; this->angleDelta = 0.0f; }
void Player::setAngleDelta(float angleDelta) { this->angleDelta = angleDelta; }
void Player::setMass(float mass) { this->mass = mass; }
void Player::setThrottle(float throttle) { this->throttle = throttle; }

void Player::setStalled(void) {
	this->stalled = true;
}

bool Player::isLocal(void) { return this->local; }
bool Player::isStalled(void) { return this->stalled; }
bool Player::isTakingOff(void) { return this->takingOff; }


// TODO: This should be "time based"
void Player::pitchUp(void)     { this->angleDelta = (0.9 * this->angleDelta) + (0.1 * 180.0); }
void Player::pitchDown(void)   { this->angleDelta = (0.9 * this->angleDelta) - (0.1 * 180.0); if (this->takingOff) { this->takingOff = false; } }
void Player::pitchReturn(void) { this->angleDelta = (0.9 * this->angleDelta); }


void Player::restartPlayer(void) {
	this->x = this->startX;
	this->y = this->startY;
	this->angle = 90.0f;
	this->speed = 0.0f;
	this->throttle = 15.0f;
	this->angleDelta = this->speedX = this->speedY = 0.0f;
	this->stalled = false;
	this->takingOff = true;
}


void Player::updateAngle(float t) {
	this->angle += this->angleDelta * t;

	if (this->angle < -180) {
		this->angle += 360.0;
	}
	else if (this->angle > 180) {
		this->angle -= 360.0;
	}
}


// TODO: Use radians instead of degrees!!
void Player::updateSpeed(float t) {
	if (this->stalled) {
		this->speedY += t * -9.8f * this->mass;
		float fallingAngle = dbAtanFull(this->speedX, this->speedY);
		float squaredSpeed = (this->speedX * this->speedX) + (this->speedY * this->speedY);

		// Compare squaredSpeed against our "threshold" speed squared (eg, 225 = 15*15)
		float stallThreshold = 40.0f;
		if (squaredSpeed > (stallThreshold * stallThreshold) && fabs(fallingAngle - this->angle) < 20.0) {
			// This is to avoid Square Rooting every time - its a slow operation
			this->speed = sqrt(squaredSpeed);
			this->stalled = false;
		}

		if (this->stalled) return;
	}

	// Apply gravity
	this->speed += dbCos(this->angle) * t * -9.8f * this->mass;
	this->speed += t * this->throttle;

	// We need drag to pull us back... This should help us acheive a "terminal velocity"
	// Drag only applied above a minimum speed
	// TODO: This seems wrong...
	if (this->speed > 20.0) {
		float drag = pow((this->speed - 20.0) * this->dragCoefficient, 2);
		this->speed -= t * drag;
	}

	// Set the component speeds - this is important if we've stalled!
	this->speedX = dbSin(this->angle) * this->speed;
	this->speedY = dbCos(this->angle) * this->speed;


	// Stall the plan if we NOT taking off and the speed is less than 20
	if (!this->takingOff && this->speed < 20.0f) {
		this->setStalled();
	}
}




void Player::updatePosition(float t) {
	// Move the plane based on component speed and time
	this->x += this->speedX * t;
	this->y += this->speedY * t;

	// Rotate and position the player's object,
	dbPositionObject(this->objId, this->x, this->y, 0);
	dbRotateObject(this->objId, 0, 0, this->angle);

	// ... And its shadow
	dbPositionObject(this->shadowId, this->x, dbObjectPositionY(2) + 0.1, 0);
}


void Player::moveObject(float worldHeight) {
	dbRotateObject(this->objId, 0, 0, 90.0f - this->angle);
	dbPositionObject(this->objId, this->x, this->y, 0);
	dbPositionObject(this->shadowId, this->x, dbObjectPositionY(this->shadowId), 0);

	float s = 100.0 * (1.0 - (this->y / worldHeight));
	if (s > 100.0) s = 100;
	else if (s < 0) s = 0;
	
	dbFadeObject(this->shadowId, s);
	dbScaleObject(this->shadowId, s, s, s);
}