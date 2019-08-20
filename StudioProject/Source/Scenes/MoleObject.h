#pragma once

#include "GameObject.h"

class MoleObject : public GameObject
{
public:
	enum MOLEOBJECT_TYPE
	{
		GO_NONE,
		GO_HAMMER,
		GO_MOLE,
		GO_MOLE_BRONZE,
		GO_MOLE_SILVER,
		GO_MOLE_GOLD,
		GO_MOLE_BOMB,
		GO_MOLE_FROST,
		GO_STATS,
		GO_RESULTS,
		GO_TOTAL
	};
	MoleObject(MOLEOBJECT_TYPE typeValue = GO_NONE);
	~MoleObject();
	float mole_yOffset;
	float mole_lifeTime;
	bool mole_goUp;
	bool mole_hit;
};