#ifndef CLOUD_INCLUDED
#define CLOUD_INCLUDED


class Cloud {
	float x, y, z, speed;
	int id;

public:
	Cloud() {}
	Cloud(float x, float y, float z,float speed);

	float getX();
	float getY();
	float getZ();
	float getSpeed();
	void move(float t);

	int getObjectId();
	void setObjectId(int id);
};

#endif