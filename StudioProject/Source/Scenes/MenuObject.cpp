#include "MenuObject.h"

MenuObject::MenuObject(MENUOBJECT_TYPE typeValue, Vector3 scale_default)
{
	type = typeValue;
	scale = scale_default;
	this->scale_default = scale_default;
	changed = false;
}

MenuObject::~MenuObject()
{

}

bool MenuObject::getChanged()
{
	return changed;
}

void MenuObject::setChanged(bool input)
{
	changed = input;
}

void MenuObject::Update(Vector3 v_mousepos)
{
	if (v_mousepos.x >= pos.x - scale.x/2 &&
		v_mousepos.x <= pos.x + scale.x / 2 &&
		v_mousepos.y >= pos.y - scale.y / 2 &&
		v_mousepos.y <= pos.y + scale.y / 2)
	{
		scale = scale_default * 1.5f;
		static bool bLButtonState = false;
		if (!bLButtonState && Application::IsMousePressed(0))
		{
			bLButtonState = true;
			std::cout << "LBUTTON DOWN" << std::endl;
			changed = changed ? false : true;
		}
		else if (bLButtonState && !Application::IsMousePressed(0))
		{
			bLButtonState = false;
		}
	}
	else
	{
		scale = scale_default;
	}
}