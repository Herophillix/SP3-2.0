#pragma once
#include "PhysicsObject.h"
class SheepObject : public PhysicsObject
{
public:
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
		E_LIGHTNING,
		E_WARNING,
		E_TOTAL
	};
	bool getDirection();
	void setDirection(bool leftTrue);
	bool getState();
	void setState(bool moving);
	void UpdateMovement(double dt);
	SheepObject(sheepGameType typeValue = E_NONE);
	~SheepObject();

	void setIsDown(bool);
	void setOnCoolDown(bool);
	void setHealth(float, bool additive = false);
	void setCooldown(float, bool additive = false);
	void setMana(float, bool additive = false);
	void setSpreadAngle(float, bool additive = false);
	void setM_dLeftRight(bool);
	void setIsMoving(bool);
	void setMouseAngle(float, bool additive = false);

	bool getIsDown();
	bool getOnCooldown();
	float getHealth();
	float getCooldown();
	float getMana();
	float getSpreadAngle();
	bool getM_dLeftRight();
	bool getIsMoving();
	float getMouseAngle();

private:
	bool isDown;
	bool onCooldown;
	float health;
	float cooldown;
	float Mana;
	float spreadAngle;
	bool m_dLeftRight;
	bool isMoving;
	float mouseAngle;
};

