#include "World.h"


Cloud::Cloud(float x, float y, float speed) {
	this->x = x;
	this->y = y;
	this->speed = speed;
}




World::World(void) {
	this->width = 240.0f;
	this->height = 150.0f;

	for (int i = 0; i < CLOUD_COUNT; i++) {
		float x = MyLib::randFloat() * this->width;
		float y = (0.5f * MyLib::randFloat() * this->height) + (0.5f * this->height);
		float speed = (MyLib::randFloat() - 0.5) * 15.0f;


		this->clouds[i] = Cloud(x, y, speed);
	}
}

Cloud World::getCloud(int id) {
	return this->clouds[id];
}


void World::updateCloudPositions(void) {
	float t = MyTimer::get().getT();

	for (int i = 0; i < CLOUD_COUNT; i++) {
		this->clouds[i].move(t);
	}
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