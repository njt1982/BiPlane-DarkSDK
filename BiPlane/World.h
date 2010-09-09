#pragma once

#include <time.h>
#include <iostream>
#include <vector>
#include "MyLib.h"
#include "Player.h"
#include "DarkGDK.h"



const int CLOUD_COUNT = 4;



class Cloud {
	float x, y, z, speed;
	int id;

public:
	Cloud() {}
	Cloud(float x, float y, float z,float speed);

	float getX() { return this->x; }
	float getY() { return this->y; }
	float getZ() { return this->z; }
	float getSpeed() { return this->speed; }
	void move(float t) { x += speed * t; }

	int getObjectId() { return this->id; }
	void setObjectId(int id) { this->id = id; }
};






class World {
	float width, height;
	std::vector<Cloud> clouds;
	std::vector<Player> players;

	int skyId, groundId, cloudTextureId;
	const static int skyColor = 0x5050FF;
	const static int groundColor = 0x50FF50;

public:
	World(void);
	~World(void);

	
	float getWidth() { return width; }
	float getHeight() { return height; }

	Cloud* getCloud(int id);
	void updateCloudPositions(void);

	void addPlayer(void);
	Player* getPlayer(int id);

	void checkPlayerBoundaries(Player *p);
};