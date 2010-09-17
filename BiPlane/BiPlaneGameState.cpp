#include "BiPlaneGameState.h"

// Creator method
BiPlaneGameState::BiPlaneGameState(void) {
	// Create a world
	w = new World();

	// Grab a reference to the GameUI (used later to allow an update loop to control the speedo)
	gameUI = &BiPlaneGameUI::getInstance();

	// Add the local player
	this->addPlayer(1);

	// TODO: Add more local or other remote players

	// Define the camera and light positions
	dbPositionCamera(0, w->getHeight() / 2.0, -120);
	dbPointCamera(0, w->getHeight() / 2.0, 0);
	dbSetPointLight(0, dbCameraPositionX(), dbCameraPositionY(), dbCameraPositionZ());
}


// Update method - this is called every loop
bool BiPlaneGameState::update(float t) {
	// Create an itterator of Players - keeps it flexible
	std::map<unsigned int, Player>::iterator pIterator;

	// Define a Player pointer - keeps the following code clean and readable
	Player *p;

	// Go through the iterator of players
	for (pIterator = players.begin(); pIterator != players.end(); pIterator++) {
		// Grab the player object
		p = &pIterator->second;

		// If the player is local...
		if (p->isLocal()) {
			// DEBUG CODE: show speed and height
			// TODO: Improve speedo and add altometer
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

		// Is the player on screen, or has he crashed, gone too high or looped off the edge
		this->checkPlayerBoundaries(p);

		// Update the angle
		p->updateAngle(t);

		// Update the speed
		p->updateSpeed(t);

		// Update the position (based on angle and speed above)
		p->updatePosition(t);

		// Move the object
		p->moveObject(w->getHeight());

		// If the player is local, then update the speedo
		if (p->isLocal()) {
			gameUI->setSpeed(p->getSpeed());
		}
	}

	// Update the cloud positions
	w->updateCloudPositions(t);

	// Render the GameUI
	gameUI->render();

	// The loop completed sucessfully!
	return true;
}


// Private method for adding a new plauer to the world.
void BiPlaneGameState::addPlayer(unsigned int playerId) {
	// Create a new Player object, defining starting X and Y, along with the ground height.
	Player p = Player(-w->getWidth() * 0.45f, w->getGroundHeight() + 0.5f, w->getGroundHeight());

	// Define a player mass (TODO: players will be able to define their own plane stats)
	p.setMass(3.0f);

	// Add this player to the list
	this->players[playerId] = p;
}


// Private boundary checking method
void BiPlaneGameState::checkPlayerBoundaries(Player *p) {
	// Check against screen horizontal edges.
	// If off the left, push over to the right
	if (p->getX() < (-w->getWidth() / 2.0f)) {
		p->setX(p->getX() + w->getWidth());
	}
	// If off the right, push over to the left.
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


