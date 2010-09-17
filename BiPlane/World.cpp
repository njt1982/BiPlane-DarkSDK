#include "World.h"


// World Constructor
World::World(void) {
	// Define dimesions
	// TODO: Move these to a settings class
	this->width = 240.0f;
	this->height = 150.0f;

	// Grab a reference to the ID Handler - better to do this once than repeatedly grab the singleton
	MyIdHandler* mih = &MyIdHandler::get();

	// SKY
	this->skyId = mih->getObjectId();
	dbMakeObjectPlain(this->skyId, this->width, this->height);
	 dbPositionObject(this->skyId,           0, this->height / 2.0, 5);
	    dbPointObject(this->skyId,           0, this->height / 2.0, 0);
		dbColorObject(this->skyId, this->skyColor);


	// GROUND
	this->groundHeight = 10.0f;
	this->groundId = mih->getObjectId();
	dbMakeObjectPlain(this->groundId, this->width, 50.0f);
	 dbPositionObject(this->groundId, 0, this->groundHeight, 0);
	    dbPointObject(this->groundId, 0, this->groundHeight + 1.0, 0);
	    dbColorObject(this->groundId, this->groundColor);


	for (int i = 0; i < 10; i++) {
		this->clouds.push_back(Cloud(this->width, this->height));
	}
}

// Public function to get the ground altitude
float World::getGroundHeight(void) { return this->groundHeight; }


// Public function to update the clouds in the world based on a specified time step
void World::updateCloudPositions(float t) {
	std::vector<Cloud>::iterator cloud;

	cloud = clouds.begin();
	while (cloud != clouds.end()) {
		cloud->move(t);
		cloud->edgeCheck(this->width);
		++cloud;
	}
}

// Public "getter" functions for the World dimensions
float World::getWidth(void)  { return this->width; }
float World::getHeight(void) { return this->height; }


// Destructor method
World::~World(void) {}