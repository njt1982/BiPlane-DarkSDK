#include "Cloud.h"

Cloud::Cloud(float x, float y, float z, float speed) {
	this->x = x;
	this->y = y;
	this->z = z;
	this->speed = speed;
}

float Cloud::getX() { return this->x; }
float Cloud::getY() { return this->y; }
float Cloud::getZ() { return this->z; }
float Cloud::getSpeed() { return this->speed; }

void Cloud::move(float t) { this->x += speed * t; }

int Cloud::getObjectId() { return this->id; }
void Cloud::setObjectId(int id) { this->id = id; }