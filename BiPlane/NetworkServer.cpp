#include "NetworkServer.h"

NetworkServer::NetworkServer(void) {
	srand(time(NULL));
/*
	float cloudPos[CLOUD_COUNT];
	float cloudSpeed[CLOUD_COUNT];
	for (int i = 0; i < CLOUD_COUNT; i++) {
		cloudPos[i] = (float)(rand() % (int)WORLD_WIDTH);
		cloudSpeed[i] = (float)(((rand() % 300) / 10.0f) - 15.0f);
		
		int obj = CLOUD_OFFSET + i;
		dbMakeObjectPlain(obj, 96.0, 96.0);
		dbPositionObject(obj, cloudPos[i], 50 + (rand() % 50), (i * -0.1) - 10.0);
		dbPointObject(obj, cloudPos[i], dbObjectPositionY(obj), -15);

		dbLoadImage("Media/cloud1.png", obj);
		dbTextureObject(obj, obj);
		dbSetObjectTransparency(obj, 5);
	}	
*/

}

NetworkServer::~NetworkServer(void)
{
}
