#ifndef GAMESTATE_INCLUDED
#define GAMESTATE_INCLUDED

/**
 * Base GameState class
 */
class GameState {
public:
	GameState() {};
	~GameState() {};

	virtual bool update(float t) = 0;
};

#endif