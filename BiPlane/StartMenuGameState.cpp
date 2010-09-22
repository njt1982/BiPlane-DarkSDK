#include "StartMenuGameState.h"

StartMenuGameState::StartMenuGameState(void) {
	this->leftMouseDown = false;
	this->state = 0;

	LPDIRECT3DDEVICE9 device = dbGetDirect3DDevice( );
	CEGUI::Direct3D9Renderer& guiRenderer = CEGUI::Direct3D9Renderer::create(device);

	CEGUI::System::create(guiRenderer);

	this->gui = CEGUI::System::getSingletonPtr();

	CEGUI::DefaultResourceProvider* guiResporceProvider = static_cast<CEGUI::DefaultResourceProvider*>(this->gui->getResourceProvider());
	guiResporceProvider->setResourceGroupDirectory("schemes", "./media/CEGUI/schemes/");
	guiResporceProvider->setResourceGroupDirectory("imagesets", "./media/CEGUI/imagesets/");
	guiResporceProvider->setResourceGroupDirectory("fonts", "./media/CEGUI/fonts/");
	guiResporceProvider->setResourceGroupDirectory("layouts", "./media/CEGUI/layouts/");
	guiResporceProvider->setResourceGroupDirectory("looknfeels", "./media/CEGUI/looknfeel/");
	guiResporceProvider->setResourceGroupDirectory("lua_scripts", "./media/CEGUI/lua_scripts/");
	guiResporceProvider->setResourceGroupDirectory("schemas", "./media/CEGUI/xml_schemas/");

	CEGUI::Imageset::setDefaultResourceGroup("imagesets");
	CEGUI::Font::setDefaultResourceGroup("fonts");
	CEGUI::Scheme::setDefaultResourceGroup("schemes");
	CEGUI::WidgetLookManager::setDefaultResourceGroup("looknfeels");
	CEGUI::WindowManager::setDefaultResourceGroup("layouts");
	CEGUI::ScriptModule::setDefaultResourceGroup("lua_scripts");

	CEGUI::XMLParser* parser = gui->getXMLParser();
	if (parser->isPropertyPresent("SchemaDefaultResourceGroup")) {
		parser->setProperty("SchemaDefaultResourceGroup", "schemas");
	}

	CEGUI::SchemeManager::getSingleton().create("TaharezLook.scheme");
	CEGUI::FontManager::getSingleton().create("DejaVuSans-10.font");

	this->gui->setDefaultFont("DejaVuSans-10");
	this->gui->setDefaultMouseCursor("TaharezLook", "MouseArrow");
	this->gui->setDefaultTooltip("TaharezLook/Tooltip");
	
	CEGUI::WindowManager& wmgr = CEGUI::WindowManager::getSingleton();
	
	CEGUI::Window* myRoot = wmgr.loadWindowLayout("Noodle.layout");
	this->gui->setGUISheet(myRoot);

	wmgr.getWindow("Root/frmMain/startServer")->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&StartMenuGameState::clickHandler, this));
	wmgr.getWindow("Root/frmMain/connect")->subscribeEvent    (CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&StartMenuGameState::clickHandler, this));
	wmgr.getWindow("Root/frmConnect/connect")->subscribeEvent (CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&StartMenuGameState::clickHandler, this));
	wmgr.getWindow("Root/frmConnect/cancel")->subscribeEvent  (CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&StartMenuGameState::clickHandler, this));
}


bool StartMenuGameState::clickHandler(const CEGUI::EventArgs &event) {
    const CEGUI::MouseEventArgs& me = static_cast<const CEGUI::MouseEventArgs&>(event);
	CEGUI::String senderID = me.window->getName();

	if (senderID == "Root/frmMain/startServer") {
		this->state = 1;
		return true;
	}
	else if (senderID == "Root/frmConnect/connect") {
		this->state = 2;
		return true;
	}
	else if (senderID == "Root/frmMain/connect" ) {
		CEGUI::WindowManager& wmgr = CEGUI::WindowManager::getSingleton();
		wmgr.getWindow("Root/frmMain")->hide();
		wmgr.getWindow("Root/frmConnect")->show();
		wmgr.getWindow("Root/frmConnect")->activate();
		return true;
	}
	else if (senderID == "Root/frmConnect/cancel") {
		CEGUI::WindowManager& wmgr = CEGUI::WindowManager::getSingleton();
		wmgr.getWindow("Root/frmConnect")->hide();
		wmgr.getWindow("Root/frmMain")->show();
		wmgr.getWindow("Root/frmMain")->activate();
		return true;
	}

	return false;
}



bool StartMenuGameState::update(float t) {
	// Push the mouse position to the GUI handler
	this->gui->injectMousePosition((float)dbMouseX(), (float)dbMouseY());

	// Get the mouse buttons status
	int mouseButtons = dbMouseClick();

	// If we previously have not pressed the left button...
	if(!leftMouseDown) {
		/// and the left button is now pressed (using a bitmask)
		if((mouseButtons & 0x01) == 0x01) {
			// Then we have pressed it - and inject the event to the gui handler
			leftMouseDown = true;
			this->gui->injectMouseButtonDown(CEGUI::LeftButton);
		}
	}
	// Otherwise we have previously pressed the button...
	else {
		// .. Are we pressing it now though? If not...
		if((mouseButtons & 0x01) == 0x00) {
			// ... then remove the semaphore and send an event to the gui handler
			leftMouseDown = false;
			this->gui->injectMouseButtonUp(CEGUI::LeftButton);
		}
	}
	/*
	for(unsigned int sc = 0; sc < 256; sc++) {
		if(!scanCodes[sc]) {
			if(dbKeyState(sc)) {
				scanCodes[sc] = true;
				this->gui->injectKeyDown(sc);
			}
		}
		else {
			if(!dbKeyState(sc)) {
				scanCodes[sc] = false;
				this->gui->injectKeyUp(sc);

				bool leftShift = dbKeyState(42);
				bool rightShift = dbKeyState(54);
				bool shifted = leftShift || rightShift;
				unsigned char c = ScanCodeToASCIIConverter::getInstance()->convert(sc, shifted);

				if((c > 0) && (c <= 255)) {
					this->guiinjectChar(c);
				}
			}
		}
	}
	*/


	this->gui->renderGUI();

	return (this->state == 0);
}

int StartMenuGameState::getState(void) {
	return this->state;
}

StartMenuGameState::~StartMenuGameState(void) {}