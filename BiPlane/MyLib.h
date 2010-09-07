#pragma once

#include "DarkGDK.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <stack>



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




class MyIdHandler {
	std::stack<int> ids;
	static MyIdHandler* instance;

	MyIdHandler(void);
	~MyIdHandler(void) {}

public:
	static MyIdHandler& get();
	int getId(void);
};