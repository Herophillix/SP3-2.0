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

	void setMole_yOffset(float, bool additive = false);
	void setMole_lifeTime(float, bool additive = false);
	void setMole_goUp(bool);
	void setMole_hit(bool);

	float getMole_yOffset();
	float getMole_lifeTime();
	bool getMole_goUp();
	bool getMole_hit();

private:

	float mole_yOffset;
	float mole_lifeTime;
	bool mole_goUp;
	bool mole_hit;
};