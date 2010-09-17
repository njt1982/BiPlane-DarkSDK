#ifndef WORLD_INCLUDED
#define WORLD_INCLUDED

// Load some core libraries
#include <time.h>

// Load some custom libraries
#include "MyLib.h"
#include "DarkGDK.h"
#include "Player.h"
#include "Cloud.h"




/**
 * Custom "World" Class - defines the game environment (width, height, etc). + Create World entities
 */
class World {
	float width, height, groundHeight, ceilingHeight;
	std::vector<Cloud> clouds;

	int skyId, groundId, cloudTextureId;
	const static int skyColor = 0x5050FF;
	const static int groundColor = 0x50FF50;

public:
	World(void);
	~World(void);

	
	float getWidth();
	float getHeight();

	float getGroundHeight();

	void updateCloudPositions(float t);
};

#endif