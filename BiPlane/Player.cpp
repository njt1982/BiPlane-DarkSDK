#include "Player.h"
#include "MyLib.h"
#include "DarkGDK.h"


Player::Player(void) {}
Player::~Player(void) {}



Player::Player(float x, float y) {
	this->x = x;
	this->y = y;

	this->throttle = this->speed = this->angleDelta = this->angle = this->mass = 0.0f;

	this->objId = MyIdHandler::get().getObjectId();
	this->textureId = MyIdHandler::get().getImageId();

	dbLoadObject("Media/BiPlane-uv.x", this->objId);
	dbLoadImage("Media/plane.bmp", this->textureId);
	dbTextureObject(this->objId, this->textureId);


	this->shadowId = MyIdHandler::get().getObjectId();
	this->shadowTextureId = MyIdHandler::get().getImageId();

	dbMakeObjectPlain(this->shadowId, dbObjectSizeX(this->objId), dbObjectSizeZ(this->objId));
	dbPositionObject(this->shadowId, this->x, dbObjectPositionY(2) + 0.1, 0);
	dbPointObject(this->shadowId, this->x, dbObjectPositionY(2) + 100, 0);
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
void Player::setAngle(float angle) { this->angle = angle; }
void Player::setAngleDelta(float angleDelta) { this->angleDelta = angleDelta; }
void Player::setMass(float mass) { this->mass = mass; }
void Player::setThrottle(float throttle) { this->throttle = throttle; }


// TODO: This should be "time based"
void Player::pitchUp(void)     { this->angleDelta = (0.9 * this->angleDelta) + (0.1 * -180.0); }
void Player::pitchDown(void)   { this->angleDelta = (0.9 * this->angleDelta) + (0.1 * 180.0); }
void Player::pitchReturn(void) { this->angleDelta = (0.9 * this->angleDelta); }


void Player::updateAngle(void) {
	this->angle += this->angleDelta * MyTimer::get().getT();

	if (this->angle < -180) {
		this->angle += 360.0;
	}
	else if (this->angle > 180) {
		this->angle -= 360.0;
	}
}


// TODO: Use radians instead of degrees!!
void Player::updateSpeed(void) {
	float t = MyTimer::get().getT();

	this->speed += t * this->throttle;
	this->speed -= dbSin(this->angle ) * t * 9.8f * this->mass;

	if (this->speed < 0.0f) {
		//STALLED!!!
		this->speed = 0.0f;
	}
	else if (this->speed > 70.0f) {
		// TERMINAL VELOCITY
		this->speed = 70.0f;
	}
}


void Player::updatePosition(void) {
	float s = this->speed * MyTimer::get().getT();

	this->x += dbCos(this->angle) * s;
	this->y += dbSin(this->angle) * s;

	dbPositionObject(this->objId, this->x, this->y, 0);
	dbRotateObject(this->objId, 0, 0, this->angle);

	dbPositionObject(this->shadowId, this->x, dbObjectPositionY(2) + 0.1, 0);
}