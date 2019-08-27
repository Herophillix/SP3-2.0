#include "ItemObject.h"

bool ItemObject::ItemisBounded = false;
bool ItemObject::ItemisSelected = false;
int ItemObject::CurrentScreenID = UpL;

ItemObject::ItemObject(ITEMOBJECT_TYPE typeValue, SCREEN_AREA ScreenID)
{
	type = typeValue;
	this->ScreenID = ScreenID;
	bounded = false;
	selected = false;
}

ItemObject::~ItemObject()
{

}

void ItemObject::Update(Vector3 v_mousepos, Vector3 v_mousescale)
{
	if (!selected)
	{
		bounded = false;
		ItemisBounded = false;
	}
	if (ScreenID == CurrentScreenID)
	{
		if (v_mousepos.x >= pos.x - scale.x / 2 - v_mousescale.x / 2 &&
			v_mousepos.x <= pos.x + scale.x / 2 + v_mousescale.x / 2 &&
			v_mousepos.y >= pos.y - scale.y / 2 - v_mousescale.y / 2 &&
			v_mousepos.y <= pos.y + scale.y / 2 + v_mousescale.y / 2)
		{
			static bool bLButtonState = false;
			bounded = true;
			if (!bLButtonState && Application::IsMousePressed(0))
			{
				bLButtonState = true;
				std::cout << "LBUTTON DOWN" << std::endl;
				selected = true;
				ItemisSelected = true;
			}
			else if (bLButtonState && !Application::IsMousePressed(0))
			{
				bLButtonState = false;
			}
		}
		else
		{
			static bool bLButtonState = false;
			if (!bLButtonState && Application::IsMousePressed(0))
			{
				bLButtonState = true;
				std::cout << "LBUTTON DOWN" << std::endl;
				selected = false;
				ItemisSelected = false;
			}
			else if (bLButtonState && !Application::IsMousePressed(0))
			{
				bLButtonState = false;
			}
		}
	}
	else if(selected)
	{
		selected = false;
	}
}