#include "SheepObject.h"

SheepObject::SheepObject(sheepGameType typeValue)
	:spreadAngle(0),
	health(100),
	cooldown(1.f),
	onCooldown(false),
	isDown(false),
	m_dLeftRight(false),
	isMoving(false)
{
	type = typeValue;
}

bool SheepObject::getDirection()
{
	return m_dLeftRight;
}

void SheepObject::setDirection(bool leftTrue)
{
	m_dLeftRight = leftTrue;
}

bool SheepObject::getState()
{
	return isMoving;
}

void SheepObject::setState(bool move)
{
	isMoving = move;
}

void SheepObject::setIsDown(bool input)
{
	isDown = input;
}
void SheepObject::setOnCoolDown(bool input)
{
	onCooldown = input;
}
void SheepObject::setHealth(float input, bool additive)
{
	if (additive)
	{
		health += input;
	}
	else
	{
		health = input;
	}
}
void SheepObject::setCooldown(float input, bool additive)
{
	if (additive)
	{
		cooldown += input;
	}
	else
	{
		cooldown = input;
	}
}
void SheepObject::setMana(float input, bool additive)
{
	if (additive)
	{
		Mana += input;
	}
	else
	{
		Mana = input;
	}
}
void SheepObject::setSpreadAngle(float input, bool additive)
{

	if (additive)
	{
		spreadAngle += input;
	}
	else
	{
		spreadAngle = input;
	}
}
void SheepObject::setM_dLeftRight(bool input)
{
	m_dLeftRight = input;
}
void SheepObject::setIsMoving(bool input)
{
	isMoving = input;
}
void SheepObject::setMouseAngle(float input, bool additive)
{
	if (additive)
	{
		mouseAngle += input;
	}
	else
	{
		mouseAngle = input;
	}
}

bool SheepObject::getIsDown()
{
	return isDown;
}
bool SheepObject::getOnCooldown()
{
	return onCooldown;
}
float SheepObject::getHealth()
{
	return health;
}
float SheepObject::getCooldown()
{
	return cooldown;
}
float SheepObject::getMana()
{
	return Mana;
}
float SheepObject::getSpreadAngle()
{
	return spreadAngle;
}
bool SheepObject::getM_dLeftRight()
{
	return m_dLeftRight;
}
bool SheepObject::getIsMoving()
{
	return isMoving;
}
float SheepObject::getMouseAngle()
{
	return mouseAngle;
}

void SheepObject::UpdateMovement(double dt)
{
	if (Application::IsKeyPressed('D') || Application::IsKeyPressed('A'))
	{
		isMoving = true;
		if (pos.x < 165)
		{
			if (Application::IsKeyPressed('D'))
			{
				pos.x += 1;
				m_dLeftRight = false;
			}
		}
		if (pos.x > 15)
		{
			if (Application::IsKeyPressed('A'))
			{
				pos.x -= 1;
				m_dLeftRight = true;
			}
		}
	}
	else
	{
		isMoving = false;
	}
}
SheepObject::~SheepObject()
{
}
