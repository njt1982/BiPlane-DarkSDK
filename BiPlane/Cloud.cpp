#include "Cloud.h"

int Cloud::textureImageId = NULL;
int Cloud::counter = 0;

Cloud::Cloud(float width, float height) {
	this->x = (MyLib::randFloat() * width) - (0.5f * width);
	this->y = (0.5f * MyLib::randFloat() * height) + (0.5f * height);
	this->z = (++counter * -0.1f) - 10.0f;
	this->angle = 0.0f;

	// Clouds can only go in the same direction... Thanks to my wife for pointing this out!
	this->speed = MyLib::randFloat() * 20.0f;
	this->rotateSpeed = (MyLib::randFloat() - 0.5f) * 10.0f;

	this->size = 96.0;

	this->instanceId = 0;


	this->id = MyIdHandler::get().getObjectId();

	dbMakeObjectPlain(this->id, this->size, this->size);
	dbPositionObject(this->id, this->x, this->y, this->z);
	dbPointObject(this->id, this->x, this->y, this->z - 1.0f);

	if (this->textureImageId == NULL) {
		this->textureImageId = MyIdHandler::get().getImageId();
		dbLoadImage("Media/cloud1.png", this->textureImageId);
	}

	dbTextureObject(this->id, this->textureImageId);
	dbSetObjectTransparency(this->id, 5);
}



float Cloud::getX() { return this->x; }
float Cloud::getY() { return this->y; }
float Cloud::getZ() { return this->z; }
float Cloud::getSpeed() { return this->speed; }

void Cloud::move(float t) {
	this->x += this->speed * t;
	this->angle += this->rotateSpeed * t;

	dbPositionObject(this->id, this->x, this->y, this->z);
	// TODO: Un-hardcode cloud rotation
	dbRotateObject(this->id, 0.0f, 180.0f, this->angle);
}


void Cloud::edgeCheck(float world_width) {
	if (this->x - (this->size / 2.0f) > (world_width / 2.0f)) {
		this->x -= world_width + this->size;
	}
}


int Cloud::getObjectId() { return this->id; }
void Cloud::setObjectId(int id) { this->id = id; }