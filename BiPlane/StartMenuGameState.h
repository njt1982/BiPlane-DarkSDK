#ifndef STARTMENUGAMESTATE_INCLUDED
#define STARTMENUGAMESTATE_INCLUDED

// Include some core libraries

// Load some custom libraries
#include "DarkGDK.h"		// Load the Graphics Engine
#include "gamestate.h"
#include "CEGUI.h"
#include "RendererModules\Direct3D9\CEGUIDirect3D9Renderer.h"

class StartMenuGameState : public GameState {
	CEGUI::System *gui;

	bool leftMouseDown;
	int state;

	bool clickHandler(const CEGUI::EventArgs& event);
public:
	StartMenuGameState(void);
	~StartMenuGameState(void);

	bool update(float t);
	int getState(void);
};

#endif