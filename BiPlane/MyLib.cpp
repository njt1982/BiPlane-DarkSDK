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
	this->t = (0.8 * this->t) + (0.2 * (0.001 * (dbTimer() - this->lastTime)));
	this->lastTime = dbTimer();
}








MyIdHandler* MyIdHandler::instance = NULL;

MyIdHandler::MyIdHandler(void) {
	for (int i = 100; i >0; i--) {
		this->ids.push(i);
	}
}


MyIdHandler& MyIdHandler::get(void) {
	if (instance == NULL) {
		instance = new MyIdHandler();
	}
	return *instance;
}

int MyIdHandler::getId(void) {
	int i = ids.top();
	ids.pop();
	return i;
}