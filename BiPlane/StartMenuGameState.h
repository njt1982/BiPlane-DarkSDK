#ifndef STARTMENUGAMESTATE_INCLUDED
#define STARTMENUGAMESTATE_INCLUDED

// Load some custom libraries
#include "DarkGDK.h"		// Load the Graphics Engine
#include "gamestate.h"
#include "CEGUI.h"
#include "RendererModules\Direct3D9\CEGUIDirect3D9Renderer.h"

class StartMenuGameState : public GameState {
	CEGUI::System *gui;

	bool leftMouseDown;
public:
	StartMenuGameState(void);
	~StartMenuGameState(void);

	bool update(float t);
};

#endif