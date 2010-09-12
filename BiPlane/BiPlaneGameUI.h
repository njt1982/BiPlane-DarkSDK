#ifndef BIPLANEGAMEUI_INCLUDED
#define BIPLANEGAMEUI_INCLUDED

#include "MyLib.h"


class BiPlaneGameUI {
	static BiPlaneGameUI* instance;

	int speedoImageId, speedoNeedleImageId, speedoSpriteId, speedoNeedleSpriteId, speedoX, speedoY, needleX, needleY;

	BiPlaneGameUI(void);
	~BiPlaneGameUI(void);
public:
	static BiPlaneGameUI& getInstance();

	void setSpeed(float s);
	void drawSpeedo(void);
};


#endif