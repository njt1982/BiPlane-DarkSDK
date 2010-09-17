#include "BiPlaneGameUI.h"

// Initialise the internal instance object
BiPlaneGameUI* BiPlaneGameUI::instance = NULL;


// Implement the creator method
BiPlaneGameUI::BiPlaneGameUI(void) {
	// Get the ID Handling singlton
	MyIdHandler* mih = &MyIdHandler::get();

	// Grab some ID's for the speedo and needle (one for the image, one for the sprite)
	this->speedoImageId = mih->getImageId();
	this->speedoSpriteId = mih->getSpriteId();
	this->speedoNeedleImageId = mih->getImageId();
	this->speedoNeedleSpriteId = mih->getSpriteId();

	// Load the resources
	dbLoadImage("Media/speedo.png", this->speedoImageId, 1);
	dbLoadImage("Media/needle.png", this->speedoNeedleImageId, 1);

	// Define the speedo sprite
	dbSprite(this->speedoSpriteId, 0, 0, this->speedoImageId);
	dbHideSprite(this->speedoSpriteId);
	dbSetSpriteAlpha(this->speedoSpriteId, 33);

	// Define the needle sprite, offsetting it's center so it pivots nicely
	dbSprite(this->speedoNeedleSpriteId, 0, 0, this->speedoNeedleImageId);
	dbHideSprite(this->speedoNeedleSpriteId);
	dbOffsetSprite(this->speedoNeedleSpriteId, 43, 12);
	dbSetSpriteAlpha(this->speedoNeedleSpriteId, 33);

	// Define the position of the speedo...
	this->speedoX = dbScreenWidth() - dbSpriteWidth(this->speedoSpriteId) - 16;
	this->speedoY = dbScreenHeight() - dbSpriteHeight(this->speedoSpriteId) - 16;

	// ... an the needle
	this->needleX = this->speedoX + (dbSpriteWidth(this->speedoSpriteId) / 2);
	this->needleY = this->speedoY + (dbSpriteHeight(this->speedoSpriteId) / 2);
}

// Set the speedo speed value
void BiPlaneGameUI::setSpeed(float s) {
	// TODO: Better angle calculation, possible based on a players Max speed?
	// -100 is the starting angle and the rotation is "twice the speed".
	float angle = -90 + (s * 2.0);

	// Rotate the needle to the configured angle
	dbRotateSprite(this->speedoNeedleSpriteId, angle);
}


// Public render method
void BiPlaneGameUI::render(void) {
	this->drawSpeedo();
}


// Private "render" function for the speedo
void BiPlaneGameUI::drawSpeedo(void) {
	// TODO: Why am I pasting the sprites?!

	// Display the speedo
	dbPasteSprite(this->speedoSpriteId, this->speedoX, this->speedoY);

	// Display the needle
	// TODO: Un-hardcode speedo half-width (128)
	dbPasteSprite(this->speedoNeedleSpriteId, this->needleX, this->needleY);
}

// Public function to grab the class' as a singleton
BiPlaneGameUI& BiPlaneGameUI::getInstance(void) {
	if (instance == NULL) {
		instance = new BiPlaneGameUI();
	}
	return *instance;
}


// Destructor class
// TODO: Release the sprites and images
BiPlaneGameUI::~BiPlaneGameUI(void) {}