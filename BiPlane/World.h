#pragma once

#include <time.h>
#include "MyLib.h"
#include "Player.h"

//const float WORLD_WIDTH = 240.0f;
//const float WORLD_HEIGHT = 150.0f;

const int CLOUD_COUNT = 4;



class Cloud {
	float x, y, speed;

public:
	Cloud() {}
	Cloud(float x, float y, float speed);

	float getX() { return this->x; }
	float getY() { return this->y; }
	float getSpeed() { return this->speed; }
	void move(float t) { x += speed * t; }
};




class World {
	float width, height;
	int numClouds;
	Cloud clouds[CLOUD_COUNT];
	
public:
	World(void);
	~World(void);

	int getSkyColor() { return 0x5050FF; }
	int getGroundColor() { return 0x50FF50; }
	
	float getWidth() { return width; }
	float getHeight() { return height; }

	Cloud getCloud(int id);
	void updateCloudPositions(void);

	void checkPlayerBoundaries(Player *p);
};
