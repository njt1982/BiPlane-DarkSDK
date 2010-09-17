#ifndef BIPLANEGAMEUI_INCLUDED
#define BIPLANEGAMEUI_INCLUDED

// Grab some libraries
#include "MyLib.h"

/**
 * A BiPlaneGameUI class is used for the HUD - speedo, ammo (TODO), health (TODO), etc
 * This class is run as a Singleton
 */
class BiPlaneGameUI {
	static BiPlaneGameUI* instance;

	int speedoImageId, speedoNeedleImageId, speedoSpriteId, speedoNeedleSpriteId, speedoX, speedoY, needleX, needleY;

	BiPlaneGameUI(void);
	~BiPlaneGameUI(void);

	void drawSpeedo(void);
public:
	static BiPlaneGameUI& getInstance();

	void setSpeed(float s);
	void render(void);
};

#endif