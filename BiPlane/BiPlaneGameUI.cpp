#include "BiPlaneGameUI.h"

BiPlaneGameUI* BiPlaneGameUI::instance = NULL;

BiPlaneGameUI::BiPlaneGameUI(void) {
	MyIdHandler* mih = &MyIdHandler::get();

	this->speedoImageId = mih->getImageId();
	this->speedoSpriteId = mih->getSpriteId();
	this->speedoNeedleImageId = mih->getImageId();
	this->speedoNeedleSpriteId = mih->getSpriteId();


	dbLoadImage("Media/speedo.png", this->speedoImageId, 1);
	dbLoadImage("Media/needle.png", this->speedoNeedleImageId, 1);


	dbSprite(this->speedoSpriteId, 0, 0, this->speedoImageId);
	dbHideSprite(this->speedoSpriteId);
	dbSetSpriteAlpha(this->speedoSpriteId, 33);

	dbSprite(this->speedoNeedleSpriteId, 0, 0, this->speedoNeedleImageId);
	dbHideSprite(this->speedoNeedleSpriteId);
	dbOffsetSprite(this->speedoNeedleSpriteId, 42, 38);
	dbSetSpriteAlpha(this->speedoNeedleSpriteId, 33);


	this->speedoX = dbScreenWidth() - dbSpriteWidth(this->speedoSpriteId) - 16;
	this->speedoY = dbScreenHeight() - dbSpriteHeight(this->speedoSpriteId) - 16;

	this->needleX = this->speedoX + (dbSpriteWidth(this->speedoSpriteId) / 2);
	this->needleY = this->speedoY + (dbSpriteHeight(this->speedoSpriteId) / 2);
}

void BiPlaneGameUI::setSpeed(float s) {
	// TODO: Better angle calculation, possible based on a players Max speed
	float angle = -100 + (s * 2.0);
	dbRotateSprite(this->speedoNeedleSpriteId, angle);
}


void BiPlaneGameUI::drawSpeedo(void) {
	//dbPasteImage(this->speedoImageId, this->speedoX, this->speedoY, 1);
	dbPasteSprite(this->speedoSpriteId, this->speedoX, this->speedoY);
	// TODO: Un-hardcode speedo half-width (128)
	dbPasteSprite(this->speedoNeedleSpriteId, this->needleX, this->needleY);
}



BiPlaneGameUI& BiPlaneGameUI::getInstance(void) {
	if (instance == NULL) {
		instance = new BiPlaneGameUI();
	}
	return *instance;
}




BiPlaneGameUI::~BiPlaneGameUI(void) {}