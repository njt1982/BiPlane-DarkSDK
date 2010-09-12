#include "BiPlaneGameState.h"

BiPlaneGameState::BiPlaneGameState(void) {
	w = new World();
	gameUI = &BiPlaneGameUI::getInstance();

	// Add the local player
	this->addPlayer(1);


	dbPositionCamera(0, w->getHeight() / 2.0, -120);
	dbPointCamera(0, w->getHeight() / 2.0, 0);
	dbSetPointLight(0, dbCameraPositionX(), dbCameraPositionY(), dbCameraPositionZ());
}



bool BiPlaneGameState::update(float t) {
	//Player* p = &this->players.at(0);
	//players.begin();
	std::map<unsigned int, Player>::iterator pIterator;

	Player *p;
	for (pIterator = players.begin(); pIterator != players.end(); pIterator++) {
		p = &pIterator->second;
		if (p->isLocal()) {
			dbText(0, 10, dbStr(p->getSpeed()));
			dbText(0, 20, dbStr(p->getY()));
			
			// TODO: Abstract into a controller class
			// If we're NOT taking off, OR (implicitly, we are and) our speed is above 30
			if (!p->isTakingOff() || p->getSpeed() > 30.0f) {
				if (dbUpKey()) {
					p->pitchUp();
				}
				else if (dbDownKey()) {
					p->pitchDown();
				}
				else {
					p->pitchReturn();
				}
			}
		}


		this->checkPlayerBoundaries(p);
		p->updateAngle();
		p->updateSpeed();
		p->updatePosition();
		p->moveObject(w->getHeight());

		if (p->isLocal()) {
			gameUI->setSpeed(p->getSpeed());
		}
	}





	// UPDATE THE CLOUD(S)
	w->updateCloudPositions();
	for (int i = 0; i < CLOUD_COUNT; i++) {
		int obj = CLOUD_OFFSET + i;
		Cloud* c = w->getCloud(i);

		// TODO: Sort out the Z-Depth here...
		dbPositionObject(obj, c->getX(), c->getY(), dbObjectPositionZ(obj));

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

	gameUI->drawSpeedo();
	return true;
}


void BiPlaneGameState::addPlayer(unsigned int playerId) {
	Player p = Player(-w->getWidth() * 0.45f, w->getGroundHeight() + 0.5f, w->getGroundHeight());
	p.setMass(3.0f);

	this->players[playerId] = p;
}



void BiPlaneGameState::checkPlayerBoundaries(Player *p) {
	// Check against screen horizontal edges
	if (p->getX() < (-w->getWidth() / 2.0f)) {
		p->setX(p->getX() + w->getWidth());
	}
	else if (p->getX() > (w->getWidth() / 2.0)) {
		p->setX(p->getX() - w->getWidth());
	}

	// Have we hit the floor? // TODO: BETTER CRASH!!!
	if (p->getY() < w->getGroundHeight()) {
		p->restartPlayer();
	}
	//TODO: Figure out how to work out the ceiling height
	//else if (p->getY() > w->getHeight() - 20.0f) {
	else if (p->getY() > 140.0f) {
		p->setStalled();
	}
}



BiPlaneGameState::~BiPlaneGameState(void) {}


