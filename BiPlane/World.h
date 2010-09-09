//#pragma once

#ifndef WORLD_INCLUDED
#define WORLD_INCLUDED


#include <time.h>
#include <iostream>
#include <vector>
#include "MyLib.h"
#include "Player.h"
#include "DarkGDK.h"
#include "Cloud.h"


const int CLOUD_COUNT = 4;




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

	
	float getWidth();
	float getHeight();

	Cloud* getCloud(int id);
	void updateCloudPositions(void);

	void addPlayer(void);
	Player* getPlayer(int id);

	void checkPlayerBoundaries(Player *p);
};

#endif