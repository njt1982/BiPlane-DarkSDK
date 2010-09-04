#pragma once

class MyLib {
public:
	static float randFloat(void);
};




class MyTimer {
float t, lastTime;

public:
	static MyTimer* myInstance;

	MyTimer(void);
	~MyTimer(void);

	static MyTimer& get();
	float getT(void) { return this->t; }
	void tick(void);
};