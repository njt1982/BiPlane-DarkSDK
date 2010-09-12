#include "World.h"



World::World(void) {
	this->width = 240.0f;
	this->height = 150.0f;

	// SKY
	this->skyId = MyIdHandler::get().getObjectId();
	dbMakeObjectPlain(this->skyId, this->width, this->height);
	 dbPositionObject(this->skyId,           0, this->height / 2.0, 5);
	    dbPointObject(this->skyId,           0, this->height / 2.0, 0);
		dbColorObject(this->skyId, this->skyColor);


	// GROUND
	this->groundHeight = 10.0f;
	this->groundId = MyIdHandler::get().getObjectId();
	dbMakeObjectPlain(this->groundId, this->width, 50.0f);
	 dbPositionObject(this->groundId, 0, this->groundHeight, 0);
	    dbPointObject(this->groundId, 0, this->groundHeight + 1.0, 0);
	    dbColorObject(this->groundId, this->groundColor);


	for (int i = 0; i < 10; i++) {
		this->clouds.push_back(Cloud(this->width, this->height));
	}
}

float World::getGroundHeight(void) { return this->groundHeight; }



Cloud* World::getCloud(int id) {
	return &this->clouds[id];
}


void World::updateCloudPositions(float t) {
	std::vector<Cloud>::iterator cloud;

	cloud = clouds.begin();
	while (cloud != clouds.end()) {
		cloud->move(t);
		cloud->edgeCheck(this->width);
		++cloud;
	}
}

float World::getWidth(void)  { return this->width; }
float World::getHeight(void) { return this->height; }






World::~World(void) {}