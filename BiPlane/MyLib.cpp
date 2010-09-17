#include "MyLib.h"

// Handy function to return a 0.0f - 1.0f
float MyLib::randFloat(void) { return (float)rand() / (float)RAND_MAX; }



// Initialise the Timer singleton instance
MyTimer* MyTimer::myInstance = NULL;

// Constructor method
MyTimer::MyTimer(void) {
	this->t = 0.0f;
	this->lastTime = dbTimer();
}
// Destructor method
MyTimer::~MyTimer(void) {}

// Public "get" method to grab the singleton
MyTimer& MyTimer::get() {
	if (myInstance == NULL) {
		myInstance = new MyTimer();
	}
	return *myInstance;
}

// Public method to "tick" the internal timer. Uses a weighted average
void MyTimer::tick(void) {
	this->t = (0.95 * this->t) + (0.05 * (0.001 * (dbTimer() - this->lastTime)));
	this->lastTime = dbTimer();
}





// Initialize the ID Handler Singleton instance
MyIdHandler* MyIdHandler::instance = NULL;

// Constructor Method
MyIdHandler::MyIdHandler(void) {
	for (int i = 100; i >0; i--) {
		this->objects.push(i);
		this->images.push(i);
		this->sprites.push(i);
	}
}

// Public "get" method to grab the singleton
MyIdHandler& MyIdHandler::get(void) {
	if (instance == NULL) {
		instance = new MyIdHandler();
	}
	return *instance;
}

// Public Object ID handling function
int MyIdHandler::getObjectId(void) {
	int i = objects.top();
	objects.pop();
	return i;
}
// Public Image ID handling function
int MyIdHandler::getImageId(void) {
	int i = images.top();
	images.pop();
	return i;
}
// Public Sprite ID handling function
int MyIdHandler::getSpriteId(void) {
	int i = sprites.top();
	sprites.pop();
	return i;
}

// Public "return" functions for putting ID's back into the stack
void MyIdHandler::putObjectIdBack(int i) { objects.push(i); }
void MyIdHandler::putImageIdBack(int i)  { images.push(i); }
void MyIdHandler::putSpriteIdBack(int i) { sprites.push(i); }

