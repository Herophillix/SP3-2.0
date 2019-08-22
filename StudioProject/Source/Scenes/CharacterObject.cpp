#include "CharacterObject.h"
#include "StudioProjectScene.h"
#include "../Rendering/Particles.h"

int CharacterObject::m_Count = 0;

CharacterObject::CharacterObject(CHARACTEROBJECT_TYPE typeValue)
	:
	motivation(100),
	rest(100),
	frustration(0),
	workDone(0),
	m_dLeftRight(false),
	isMoving(false)
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
	if (frustration < 100 && resting == false)
	{
		frustration += 0.8f / experience * 1 / m_Count * dt;
	}
	if(frustration > 0 && resting == true)
	{
		frustration -= 0.8f / experience * 1 / m_Count * dt;
	}
	if (frustration < 0.005f)
	{
		frustration = 0.005f;
	}
	if (rest > 0 && resting == false)
	{
		rest -= 0.5f  *  experience * dt / m_Count;
	}
	if (rest < 100 && resting == true)
	{
		rest += 0.5f  *  experience * dt / m_Count;
	}
	if(rest < 0.005f)
	{
		rest = 0.005f;
	}
	if (motivation > 0 && resting == false)
	{
		motivation -= 0.5f * experience * dt / m_Count;
	}
	if (motivation < 100 && resting == true)
	{
		motivation += 0.5f * experience * dt / m_Count;
	}
	if(rest < 0.00f)
	{
		rest = 0.005f;
	}
	if (workDone < 100 && resting == false)
	{
		workDone += 0.50f / experience * motivation / rest *  dt / m_Count;
	}
}

void CharacterObject::UpdateMovement(double dt)
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