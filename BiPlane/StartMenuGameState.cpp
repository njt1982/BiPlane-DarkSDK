#include "StartMenuGameState.h"

StartMenuGameState::StartMenuGameState(void) {
	this->leftMouseDown = false;

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
}


bool StartMenuGameState::update(float t) {
	int mouseButtons = dbMouseClick();

	if(!leftMouseDown) {
		if((mouseButtons & 0x01) == 0x01) {
			leftMouseDown = true;
			this->gui->injectMouseButtonDown(CEGUI::LeftButton);
		}
	}
	else {
		if((mouseButtons & 0x01) == 0x00) {
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

	this->gui->injectMousePosition((float)dbMouseX(), (float)dbMouseY());

	this->gui->renderGUI();

	return true;
}


StartMenuGameState::~StartMenuGameState(void) {}