#ifndef WORLD_INCLUDED
#define WORLD_INCLUDED


#include <time.h>
#include "MyLib.h"
#include "Player.h"
#include "DarkGDK.h"
#include "Cloud.h"


const int CLOUD_COUNT = 4;




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
	//float getCeilingHeight();

	Cloud* getCloud(int id);
	void updateCloudPositions(void);
};

#endif