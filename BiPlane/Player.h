#pragma once

class Player {
float x, y, speed, angle, angleDelta, mass, throttle;

public:
	Player(float x, float y);
	Player(void);
	~Player(void);

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

	void pitchUp(void);
	void pitchDown(void);
	void pitchReturn(void);

	void updateAngle(void);
	void updateSpeed(void);
	void updatePosition(void);
};