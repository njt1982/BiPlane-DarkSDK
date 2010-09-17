// Include some core libraries
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// #include <enet/enet.h>

// Include some custom libraries
#include "MyLib.h"				// Contains the Frame Timer amongst other things
#include "DarkGDK.h"			// The Graphics Engine
#include "BiPlaneGameState.h"	// The Game State controller class


// Hard coded variable for conveniently toggling fullscreeen
const bool FULLSCREEN = FALSE;




// the main entry point for the application is this function
void DarkGDK ( void ){
	// Seed the random number generator
	srand(time(NULL));

	// Configure the engine to run as fast as possible (no frame rate cap)
	dbSyncOn();
	dbSyncRate(0);

	// If fullscreen, configure to a, currently, hard coded setting
	if (FULLSCREEN) {
		dbSetWindowOff();
		dbMaximizeWindow();
		dbSetDisplayModeAntialias(1680, 1050, 32, 1, 0, 0);
		dbSetCameraAspect(0, 1680.0 / 1050.0);
	}
	// Otherwise, configure a windowed display
	else {
		dbSetDisplayModeAntialias(1280, 800, 32, 1, 0, 0);
		dbSetCameraAspect(0, 1280.0 / 800.0);
		dbSetWindowPosition(32, 32);
	}

	// Create a new Game State - this is a general game controlling class
	BiPlaneGameState *gs = new BiPlaneGameState();


	// This forces the timer to initialise
	MyTimer::get();
	float t;

	// our main loop
	while (LoopGDK()) {
		// Tick the timer & frame rate for this loop
		MyTimer::get().tick();
		t = MyTimer::get().getT();
		dbText(0, 0, dbStr((float)(1.0 / t)));

		// Issue an Update to the GameState system, passing the frameTime into it
		gs->update(t);

		// Update the display
		dbSync();
	}

	// Do a little house keeping
	delete gs;
	return;
}