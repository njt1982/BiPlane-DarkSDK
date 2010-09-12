#ifndef PLAYER_INCLUDED
#define PLAYER_INCLUDED




class Player {
	float x, y, speed, speedX, speedY, dragCoefficient, angle, angleDelta, mass, throttle, startX, startY;
	int objId, textureId, shadowId, shadowTextureId;
	bool local, stalled, takingOff;

public:
	Player(float x, float y, float groundHeight);
	Player(void);
	~Player(void);

	bool isLocal(void);

	float getX(void);
	float getY(void);
	float getSpeed(void);
	float getAngle(void);
	float getAngleDelta(void);
	float getMass(void);
	float getThrottle(void);

	void setX(float x);
	void setY(float y);
	void setSpeed(float speed);
	void setAngle(float angle);
	void setAngleDelta(float angleDelta);
	void setMass(float mass);
	void setThrottle(float throttle);

	void setStalled(void);
	bool isStalled(void);

	bool isTakingOff(void);

	void pitchUp(void);
	void pitchDown(void);
	void pitchReturn(void);

	void updateAngle(void);
	void updateSpeed(void);
	void updatePosition(void);

	void restartPlayer(void);

	void moveObject(float worldHeight);
};


#endif