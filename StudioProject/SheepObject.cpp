#include "SheepObject.h"



SheepObject::SheepObject(sheepGameType typeValue)
	:spreadAngle(0),
	health(100),
	cooldown(2.f),
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
