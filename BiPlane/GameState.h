#ifndef GAMESTATE_INCLUDED
#define GAMESTATE_INCLUDED

class GameState {
public:
	GameState() {};
	~GameState() {};

	virtual bool update(float t) = 0;
};

#endif