#include "SceneMainMenu.h"

MainMenuObject::MainMenuObject(MAINMENU_OBJECTTYPE typevalue) :
	highlighted(false),
	fontColor(0,0,0),
	xOffset(0.f)
{
	type = typevalue;
}

void MainMenuObject::setHighlighted(bool input)
{
	highlighted = input;
}
void MainMenuObject::setxOffset(float input, bool additive)
{
	if (additive)
	{
		xOffset += input;
	}
	else
	{
		xOffset = input;
	}
}
void MainMenuObject::setFontColor(Color input)
{
	fontColor = input;
}
void MainMenuObject::setText(string input)
{
	Text = input;
}

bool MainMenuObject::getHighlighted()
{
	return highlighted;
}
float MainMenuObject::getxOffset()
{
	return xOffset;
}
Color MainMenuObject::getFontColor()
{
	return fontColor;
}
string MainMenuObject::getText()
{
	return Text;
}

MainMenuObject::~MainMenuObject()
{
}
