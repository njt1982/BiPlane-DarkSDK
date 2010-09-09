#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <enet/enet.h>

#include "MyLib.h"
#include "DarkGDK.h"
#include "BiPlaneGameState.h"

const bool FULLSCREEN = FALSE;




// the main entry point for the application is this function
void DarkGDK ( void ){
	srand(time(NULL));

	dbSyncOn();
	dbSyncRate(0);

	if (FULLSCREEN) {
		dbSetWindowOff();
		dbMaximizeWindow();
		dbSetDisplayModeAntialias(1680, 1050, 32, 1, 0, 0);
		dbSetCameraAspect(0, 1680.0 / 1050.0);
	}
	else {
		dbSetDisplayModeAntialias(1280, 800, 32, 1, 0, 0);
		dbSetCameraAspect(0, 1280.0 / 800.0);
		dbSetWindowPosition(32, 32);
	}


	BiPlaneGameState *gs = new BiPlaneGameState();


	// This forces the timer to initialise
	MyTimer::get();
	float t;

	// our main loop
	while (LoopGDK()) {
		// Tick the timer for this loop
		MyTimer::get().tick();
		t = MyTimer::get().getT();
		dbText(0, 0, dbStr((float)(1.0 / t)));

		gs->update(t);

		// update the screen
		dbSync();
	}

	delete gs;
	return;
}