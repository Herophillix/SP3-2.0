#pragma once

#include "GameObject.h"

class ItemObject : public GameObject
{
public:
	enum ITEMOBJECT_TYPE
	{
		I_NONE,
		I_TELEVISION,
		I_COMPUTER,
		I_TOTAL
	};

	enum SCREEN_AREA
	{
		UpL,
		UpR,
		BotL,
		BotR
	};

	static bool ItemisBounded;
	static bool ItemisSelected;
	static int CurrentScreenID;

	ItemObject(ITEMOBJECT_TYPE typeValue, SCREEN_AREA ScreenID);
	~ItemObject();

	void Update(Vector3 v_mousepos, Vector3 v_mousescale);
	bool bounded;
	bool selected;
	bool inRightScreen;
	int ScreenID;
};
