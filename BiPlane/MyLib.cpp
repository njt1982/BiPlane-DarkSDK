#include "MyLib.h"
#include "DarkGDK.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>


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