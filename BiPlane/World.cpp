#include "World.h"


Cloud::Cloud(float x, float y, float z, float speed) {
	this->x = x;
	this->y = y;
	this->z = z;
	this->speed = speed;
}




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
	this->groundId = MyIdHandler::get().getObjectId();
	dbMakeObjectPlain(this->groundId, this->width, 50.0f);
	 dbPositionObject(this->groundId, 0, 10, 0);
	    dbPointObject(this->groundId, 0, 100, 0);
	    dbColorObject(this->groundId, this->groundColor);


	this->cloudTextureId = MyIdHandler::get().getImageId();
	dbLoadImage("Media/cloud1.png", this->cloudTextureId);

	for (int i = 0; i < CLOUD_COUNT; i++) {
		float x = (MyLib::randFloat() * this->width) - (0.5f * this->width);
		float y = (0.5f * MyLib::randFloat() * this->height) + (0.5f * this->height);
		float z = (i * -0.1) - 10.0;
		float speed = (MyLib::randFloat() - 0.5) * 15.0f;

		
		Cloud c = Cloud(x, y, z, speed);
		c.setObjectId(MyIdHandler::get().getObjectId());

		dbMakeObjectPlain(c.getObjectId(), 96.0, 96.0);
		dbPositionObject(c.getObjectId(), c.getX(), c.getY(), c.getZ());
		dbPointObject(c.getObjectId(), c.getX(), c.getY(), -100);

		dbTextureObject(c.getObjectId(), this->cloudTextureId);
		dbSetObjectTransparency(c.getObjectId(), 5);

		this->clouds.push_back(c);
	}
}

Cloud* World::getCloud(int id) {
	return &this->clouds[id];
}


void World::updateCloudPositions(void) {
	float t = MyTimer::get().getT();

	Cloud *c;
	for (int i = 0; i < CLOUD_COUNT; i++) {
		c = &this->clouds[i];
		c->move(t);
		dbPositionObject(c->getObjectId(), c->getX(), c->getY(), c->getZ());

	}
}


void World::addPlayer(void) {
	Player p = Player(0.0f, 60.0f);
	p.setMass(2.0f);
	p.setSpeed(40.0f);
	p.setThrottle(5.0f);

	this->players.push_back(p);
}

Player* World::getPlayer(int id) {
	return &this->players.at(id);
}


void World::checkPlayerBoundaries(Player *p) {
	if (p->getX() < (-this->width / 2.0f)) {
		p->setX(p->getX() + this->width);
	}
	else if (p->getX() > (this->width / 2.0)) {
		p->setX(p->getX() - this->width);
	}
}


World::~World(void) {}