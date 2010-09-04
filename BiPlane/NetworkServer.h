#pragma once

#include <time.h>
#include <enet/enet.h>

const float WORLD_WIDTH = 240.0f;
const float WORLD_HEIGHT = 150.0f;

const int CLOUD_COUNT = 4;
const int CLOUD_OFFSET = 10;



class NetworkServer {
public:
	NetworkServer(void);
	~NetworkServer(void);
};
