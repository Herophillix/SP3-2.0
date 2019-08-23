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
	currentItem = nullptr;
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
		frustration += 5.8f / experience * 1 / m_Count * dt;
	}
	if(frustration > 0 && resting == true)
	{
		frustration -= 5.8f / experience * 1 / m_Count * dt;
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

void CharacterObject::UpdateMovement(double dt, float m_worldWidth, float m_worldHeight)
{
	if (Application::IsKeyPressed('D') || Application::IsKeyPressed('A') || Application::IsKeyPressed('S') || Application::IsKeyPressed('W'))
	{
		isMoving = true;
		if (Application::IsKeyPressed('D') && pos.x < m_worldWidth - scale.x/2)
		{
			pos.x += 1;
			m_dLeftRight = false;
		}
		if (Application::IsKeyPressed('A') && pos.x > 0 + scale.x/2)
		{
			pos.x -= 1;
			m_dLeftRight = true;
		}
		if (Application::IsKeyPressed('W') && pos.y < m_worldHeight - scale.y / 2)
		{
			cout << m_worldHeight << endl;
			cout << pos.y << endl;
			pos.y += 1;
			m_dLeftRight = false;
		}
		if (Application::IsKeyPressed('S') && pos.y > 0 + scale.y / 2)
		{
			pos.y -= 1;
			m_dLeftRight = true;
		}
	}
	else
	{
		isMoving = false;
	}
}

bool CharacterObject::CheckCollision(ItemObject* go2)
{
	CharacterObject* go = this;
	if (fabs(go->pos.x - go2->pos.x) <= go->scale.x / 2 + go2->scale.x / 2
		&& fabs(go->pos.y - go2->pos.y) <= go->scale.y / 2 + go2->scale.y / 2)
	{
		currentItem = go2;
		return true;
	}
	else
	{
		currentItem = nullptr;
		return false;
	}
}