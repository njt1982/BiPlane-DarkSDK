#ifndef MYLIB_INCLUDED
#define MYLIB_INCLUDED

// Load some core libraries
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <stack>

// Load some custom libraries
#include "DarkGDK.h"		// Load the Graphics Engine



/**
 * Custom class for holding some "one off" static functions
 */
class MyLib {
public:
	static float randFloat(void);
};



/**
 * A Timer Singleton
 */
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



/**
 * An ID Handler Singleton
 */
class MyIdHandler {
	std::stack<int> objects;
	std::stack<int> images;
	std::stack<int> sprites;

	static MyIdHandler* instance;

	MyIdHandler(void);
	~MyIdHandler(void) {}

public:
	static MyIdHandler& get();
	int getObjectId(void);
	int getImageId(void);
	int getSpriteId(void);

	void MyIdHandler::putObjectIdBack(int i);
	void MyIdHandler::putImageIdBack(int i);
	void MyIdHandler::putSpriteIdBack(int i);
};
#endif