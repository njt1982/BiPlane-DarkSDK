#include "Cloud.h"

// Initialize the static Texture Image ID and the Counter
int Cloud::textureImageId = NULL;
int Cloud::counter = 0;

// Define a new cloud. The width and height parameters and for the World the cloud will "live" in
Cloud::Cloud(float width, float height) {
	this->x = (MyLib::randFloat() * width) - (0.5f * width);
	this->y = (0.5f * MyLib::randFloat() * height) + (0.5f * height);
	this->z = (++counter * -0.1f) - 10.0f;
	this->angle = 0.0f;

	// Clouds can only go in the same direction... Thanks to my wife for pointing this out!
	this->speed = MyLib::randFloat() * 20.0f;
	this->rotateSpeed = (MyLib::randFloat() - 0.5f) * 10.0f;
	this->size = 96.0;

	// Initialize the InstanceId
	this->instanceId = 0;

	// Get an object ID from the ID Handler singleton
	this->id = MyIdHandler::get().getObjectId();

	// Create a game engine object
	dbMakeObjectPlain(this->id, this->size, this->size);
	dbPositionObject(this->id, this->x, this->y, this->z);
	dbPointObject(this->id, this->x, this->y, this->z - 1.0f);

	// If we've not loaded the texture yet, load it and store the texture ID in the static reference variable
	if (this->textureImageId == NULL) {
		this->textureImageId = MyIdHandler::get().getImageId();
		dbLoadImage("Media/cloud1.png", this->textureImageId);
	}

	// Texture the game engine object
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