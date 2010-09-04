#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <enet/enet.h>

#include "MyLib.h"
#include "DarkGDK.h"


#include "World.h"
#include "Player.h"

const int CLOUD_OFFSET = 10;






// the main entry point for the application is this function
void DarkGDK ( void ){
	srand(time(NULL));

	World *w = new World();


	// turn on sync rate and set maximum rate to 60 fps
	dbSyncOn();
	dbSyncRate(75);

	dbSetDisplayModeAntialias(1280, 800, 32, 0, 2, 0);
	dbSetCameraAspect(0, 1.6);
	dbSetWindowPosition(0, 0);

	// SKY
	dbMakeObjectPlain(1, w->getWidth(), w->getHeight());
	dbPositionObject(1, 0, w->getHeight() / 2.0, 5);
	dbPointObject(1, 0,  w->getHeight() / 2.0, 0);
	dbColorObject(1, w->getSkyColor());


	// GROUND
	dbMakeObjectPlain(2, w->getWidth(), 50.0f);
	dbPositionObject(2, 0, 10, 0);
	dbPointObject(2, 0, 100, 0);
	dbColorObject(2, w->getGroundColor());







	for (int i = 0; i < CLOUD_COUNT; i++) {
		Cloud c = w->getCloud(i);

		int obj = CLOUD_OFFSET + i;
		dbMakeObjectPlain(obj, 96.0, 96.0);
		dbPositionObject(obj, c.getX(), c.getY(), (i * -0.1) - 10.0);
		dbPointObject(obj, c.getX(), c.getY(), -15);

		dbLoadImage("Media/cloud1.png", obj);
		dbTextureObject(obj, obj);
		dbSetObjectTransparency(obj, 5);
	}	



	Player p = Player(0.0f, 60.0f);
	p.setMass(2.0f);
	p.setSpeed(40.0f);
	p.setThrottle(5.0f);

	dbLoadObject("Media/BiPlane-uv.x", 100);
	dbLoadImage("Media/plane.bmp", 100);
	dbTextureObject(100, 100);
	dbPositionObject(100, p.getX(), p.getY(), 0);
	dbRotateObject(100, 0, 0, p.getAngle());


	dbMakeObjectPlain(99, dbObjectSizeX(100), dbObjectSizeZ(100));
	dbPositionObject(99, p.getX(), dbObjectPositionY(2) + 0.1, 0);
	dbPointObject(99, p.getX(), dbObjectPositionY(2) + 100, 0);
	dbLoadImage("Media/shadow.png", 99);
	dbTextureObject(99, 99);
	dbSetObjectTransparency(99, 1);



	dbPositionCamera(0,  w->getHeight() / 2.0, -120);
	dbPointCamera(0,  w->getHeight() / 2.0, 0);
	dbSetPointLight(0, dbCameraPositionX(), dbCameraPositionY(), dbCameraPositionZ());

	if (enet_initialize() != 0) {
		fprintf(stderr, "An error occured while initiating ENet.\n");
		return;
	}


	// This forces the timer to initialise
	MyTimer::get();

	// our main loop
	while (LoopGDK()) {
		// Tick the timer for this loop
		MyTimer::get().tick();


		dbText(0, 0, dbStr((float)(1.0 / MyTimer::get().getT())));
		
		dbText(0, 10, dbStr(p.getSpeed()));
	
		if (dbUpKey()) {
			p.pitchUp();
		}
		else if (dbDownKey()) {
			p.pitchDown();
		}
		else {
			p.pitchReturn();
		}


		p.updateAngle();
		p.updateSpeed();
		p.updatePosition();
		w->checkPlayerBoundaries(&p);


		dbRotateObject(100, 0, 0, p.getAngle());
		dbPositionObject(100, p.getX(), p.getY(), 0);
		dbPositionObject(99, p.getX(), dbObjectPositionY(99), 0);

		float s = 100.0 * (1.0 - (p.getY() / w->getWidth()));
		if (s > 100.0) s = 100;
		else if (s < 0) s = 0;
		
		dbFadeObject(99, s);
		dbScaleObject(99, s, s, s);
	




		// UPDATE THE CLOUD(S)
		w->updateCloudPositions();
		for (int i = 0; i < CLOUD_COUNT; i++) {
			int obj = CLOUD_OFFSET + i;
			Cloud c = w->getCloud(i);

			// TODO: Sort out the Z-Depth here...
			dbPositionObject(obj, c.getX(), c.getY(), dbObjectPositionZ(obj));

			/*
			if (cloudSpeed[i] > 0 ) {
				if (cloudPos[i] - (dbObjectSizeX(obj) / 2.0) > (WORLD_WIDTH / 2.0)) {
					cloudPos[i] -= WORLD_WIDTH;
					if (dbObjectExist(obj + 10)) { dbDeleteObject(obj + 10); }
				}
				else if (cloudPos[i] + (dbObjectSizeX(obj) / 2.0) > (WORLD_WIDTH / 2.0)) {
					if (!dbObjectExist(obj + 10)) {
						dbInstanceObject(obj + 10, obj);
						dbPositionObject(obj + 10, 0, 0, 0);
						dbPointObject(obj + 10, 0, 0, -5);
						dbSetObjectTransparency(obj + 10, 5);
					}
					dbPositionObject(obj + 10, cloudPos[i] - WORLD_WIDTH, dbObjectPositionY(obj), dbObjectPositionZ(obj));
				}
			}
			else if (cloudSpeed[i] < 0 ) {
				if (cloudPos[i] + (dbObjectSizeX(obj) / 2.0) < (-WORLD_WIDTH / 2.0)) {
					cloudPos[i] += WORLD_WIDTH;
					if (dbObjectExist(obj + 10)) { dbDeleteObject(obj + 10); }
				}
				else if (cloudPos[i] - (dbObjectSizeX(obj) / 2.0) < (-WORLD_WIDTH / 2.0)) {
					if (!dbObjectExist(obj + 10)) {
						dbInstanceObject(obj + 10, obj);
						dbPositionObject(obj + 10, 0, 0, 0);
						dbPointObject(obj + 10, 0, 0, -5);
						dbSetObjectTransparency(obj + 10, 5);
					}
					dbPositionObject(obj + 10, cloudPos[i] + WORLD_WIDTH, dbObjectPositionY(obj), dbObjectPositionZ(obj));
				}
			}
			dbPositionObject(obj, cloudPos[i], dbObjectPositionY(obj), dbObjectPositionZ(obj));
			*/
		}



		// update the screen
		dbSync ( );
	}

	// return back to windows
	atexit(enet_deinitialize);
	return;
}