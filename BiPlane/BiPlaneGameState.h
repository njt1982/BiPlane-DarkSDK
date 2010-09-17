#ifndef BIPLANEGAMESTATE_INCLUDED
#define BIPLANEGAMESTATE_INCLUDED

// Get some core libraries
#include <iostream>
#include <map>

// Get some custom libraries
#include "gamestate.h"		// Extendable base class
#include "Player.h"			// A Player class - stores info about the player
#include "World.h"			// A World class - stores info about the world
#include "BiPlaneGameUI.h"	// A UI Class - defines the HUD for the human player

// TODO: Expose this as a game setting
const int CLOUD_OFFSET = 10;


/**
 * BiPlaneGameState extends the GameState class
 * This defines a game (world, players, etc)
 */
class BiPlaneGameState : public GameState {
	World* w;
	BiPlaneGameUI* gameUI;

	std::map<unsigned int, Player> players;

	void addPlayer(unsigned int playerId);
	void checkPlayerBoundaries(Player *p);

public:
	BiPlaneGameState(void);
	~BiPlaneGameState(void);

	bool update(float t);
};

#endif