#pragma once
#include "CharacterObject.h"
#include "ItemObject.h"
#include "MenuObject.h"
#include <vector>

using namespace std;

class Screen
{
public:
	enum SCREEN_AREA
	{
		UpL,
		UpR,
		BotL,
		BotR
	};
	Screen(SCREEN_AREA Area);
	~Screen();
	void Init(float m_worldWidth, float m_worldHeight);
	void Update(double dt, Vector3 v_mousepos, Vector3 rel_mousepos, Vector3 v_mousescale);

	CharacterObject* Character;
	vector<ItemObject*> m_itemList;
	MenuObject* UseItem;
	int ScreenArea;
};