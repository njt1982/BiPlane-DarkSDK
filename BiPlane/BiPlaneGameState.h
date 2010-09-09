#ifndef BIPLANEGAMESTATE_INCLUDED
#define BIPLANEGAMESTATE_INCLUDED

#include "gamestate.h"

#include <iostream>
#include <map>


#include "Player.h"
#include "World.h"

const int CLOUD_OFFSET = 10;



class BiPlaneGameState : public GameState {
	World* w;
	std::map<unsigned int, Player> players;

	void addPlayer(unsigned int playerId);
	void checkPlayerBoundaries(Player *p);

public:
	BiPlaneGameState(void);
	~BiPlaneGameState(void);

	bool update(float t);
};



#endif