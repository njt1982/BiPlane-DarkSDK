#include "Player.h"
#include "MyLib.h"
#include "DarkGDK.h"


Player::Player(void) {}
Player::~Player(void) {}



Player::Player(float x, float y) {
	this->x = x;
	this->y = y;

	this->throttle = this->speed = this->angleDelta = this->angle = this->mass = 0.0f;
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
}