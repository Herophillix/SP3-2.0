#include "SceneMainMenu.h"

MainMenuObject::MainMenuObject(MAINMENU_OBJECTTYPE typevalue) :
	highlighted(false),
	fontColor(0,0,0),
	xOffset(0.f)
{
	type = typevalue;
}

MainMenuObject::~MainMenuObject()
{
}
