#pragma once
#include "Source/Scenes/PhysicsObject.h"
class SheepObject : public PhysicsObject
{
private:
	int health;
	float fireRate;
	float spreadAngle;

public:
	enum sheepGameType
	{
		E_NONE,
		E_SHEEP,
		E_TURRET,
		E_TOTAL
	};
	SheepObject(sheepGameType typeValue = E_NONE);
	~SheepObject();
};

