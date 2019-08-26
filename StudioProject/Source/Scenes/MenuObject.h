#pragma once

#include "GameObject.h"

class MenuObject : public GameObject
{
public:
	enum MENUOBJECT_TYPE
	{
		M_NONE,
		M_FORMATION_1,
		M_FORMATION_2,
		M_FORMATION_3,
		M_FORMATION_4,
		M_FORMATION_5,
		M_FORMATION_6,
		M_HOW_TO_PLAY,

		M_START,
		M_STENCIL_PLUS,
		M_STENCIL_MINUS,
		M_BACK,

		M_CONTINUE,

		M_USE_ITEM,
		M_TOTAL
	};

	MenuObject(MENUOBJECT_TYPE typeValue, Vector3 scale_default);
	~MenuObject();
	void Update(Vector3 v_mousepos);

	Vector3 scale_default;
	bool changed;
};