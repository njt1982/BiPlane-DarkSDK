#ifndef CLOUD_INCLUDED
#define CLOUD_INCLUDED

#include "DarkGDK.h"
#include "MyLib.h"


class Cloud {
	float x, y, z, speed, rotateSpeed, angle, size;
	int id;

	int instanceId;

	static int textureImageId, counter;

	//void makeInstance(void);
	//void destroyInstance(void);

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