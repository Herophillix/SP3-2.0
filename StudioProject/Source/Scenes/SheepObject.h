#pragma once
#include "PhysicsObject.h"
class SheepObject : public PhysicsObject
{
public:
	bool isDown;
	bool onCooldown;
	float health;
	float cooldown;
	float spreadAngle;
	enum sheepGameType
	{
		E_NONE,
		E_SHEEP,
		E_SHEEPFLIPPED,
		E_LINUX,
		E_PLAYER,
		E_WALL,
		E_EYES,
		E_FIREBALL,
		E_TRACE,
		E_WARNING,
		E_TOTAL
	};
	bool m_dLeftRight;
	bool isMoving;
	float mouseAngle;
	bool getDirection();
	void setDirection(bool leftTrue);
	bool getState();
	void setState(bool moving);
	void UpdateMovement(double dt);
	SheepObject(sheepGameType typeValue = E_NONE);
	~SheepObject();
};

