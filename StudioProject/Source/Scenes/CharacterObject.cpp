#include "CharacterObject.h"
#include "StudioProjectScene.h"

int CharacterObject::m_Count = 0;

CharacterObject::CharacterObject(CHARACTEROBJECT_TYPE typeValue)
	:
	motivation(100),
	rest(100),
	frustration(0),
	workDone(0),
	m_dLeftRight(false)
{
	type = typeValue;
	m_Count++;
}

CharacterObject::~CharacterObject()
{
}

bool CharacterObject::getDirection()
{
	return m_dLeftRight;
}

void CharacterObject::setDirection(bool leftTrue)
{
	m_dLeftRight = leftTrue;
}

bool CharacterObject::getState()
{
	return isMoving;
}

void CharacterObject::setState(bool move)
{
	isMoving = move;
}

void CharacterObject::Update(double dt)
{
	if (frustration < 100)
	{
		frustration += 0.4f / experience * 1 / m_Count * dt;
	}
	if (rest > 0)
	{
		rest -= 1.5f  *  experience * dt / m_Count;
	}
	else
	{
		rest = 0.005f;
	}
	if (motivation > 0)
	{
		motivation -= 0.5f * experience * dt / m_Count;
	}
	else
	{
		rest = 0.005f;
	}
	if (workDone < 100)
	{
		workDone += 0.25f / experience * motivation / rest *  dt / m_Count;
	}
}

void CharacterObject::UpdateMovement(double dt)
{
	if (Application::IsKeyPressed('D') || Application::IsKeyPressed('A'))
	{
		isMoving = true;
		if (Application::IsKeyPressed('D'))
		{
			pos.x += 1;
			m_dLeftRight = false;
		}
		if (Application::IsKeyPressed('A'))
		{
			pos.x -= 1;
			m_dLeftRight = true;
		}
	}
	else
	{
		isMoving = false;
	}
}