#ifndef CLOUD_INCLUDED
#define CLOUD_INCLUDED

// Include custom libraries
#include "DarkGDK.h"
#include "MyLib.h"


/**
 * Cloud class - defines a cloud's postion, speed, rotationspeed, angle and size
 */
class Cloud {
	float x, y, z, speed, rotateSpeed, angle, size;
	int id;

	int instanceId;
	static int textureImageId, counter;

public:
	Cloud() {}
	Cloud(float width, float height);

	float getX();
	float getY();
	float getZ();
	float getSpeed();

	void move(float t);
	void edgeCheck(float width);

	int getObjectId();
	void setObjectId(int id);
};

#endif