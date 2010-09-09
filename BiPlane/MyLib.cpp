#include "MyLib.h"


float MyLib::randFloat(void) { return (float)rand() / (float)RAND_MAX; }




MyTimer* MyTimer::myInstance = NULL;

MyTimer::MyTimer(void) {
	this->t = 0.0f;
	this->lastTime = dbTimer();
}
MyTimer::~MyTimer(void) {}

MyTimer& MyTimer::get() {
	if (myInstance == NULL) {
		myInstance = new MyTimer();
	}
	return *myInstance;
}
void MyTimer::tick(void) {
	this->t = (0.95 * this->t) + (0.05 * (0.001 * (dbTimer() - this->lastTime)));
	this->lastTime = dbTimer();
}








MyIdHandler* MyIdHandler::instance = NULL;

MyIdHandler::MyIdHandler(void) {
	for (int i = 100; i >0; i--) {
		this->objects.push(i);
		this->images.push(i);
	}
}


MyIdHandler& MyIdHandler::get(void) {
	if (instance == NULL) {
		instance = new MyIdHandler();
	}
	return *instance;
}

int MyIdHandler::getObjectId(void) {
	int i = objects.top();
	objects.pop();
	return i;
}
int MyIdHandler::getImageId(void) {
	int i = images.top();
	images.pop();
	return i;
}
