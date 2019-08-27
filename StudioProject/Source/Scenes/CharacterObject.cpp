#include "CharacterObject.h"
#include "StudioProjectScene.h"
#include "../Rendering/Particles.h"

int CharacterObject::m_Count = 0;

CharacterObject::CharacterObject(CHARACTEROBJECT_TYPE typeValue)
	:
	m_dLeftRight(false),
	isMoving(false),
	counted(false)
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

void CharacterObject::setCurrentItem(ItemObject* input)
{
	currentItem = input;
}

void CharacterObject::setStatistics(CharacterStats input)
{
	Statistics = input;
}
void CharacterObject::setResting(bool input)
{
	resting = input;
}
void CharacterObject::setWorkingHard(bool input)
{
	WorkingHard = input;
}
void CharacterObject::setAsleep(bool input)
{
	asleep = input;
}
void CharacterObject::setGiveUp(bool input)
{
	giveUp = input;
}
void CharacterObject::setCounted(bool input)
{
	counted = input;
}
void CharacterObject::setM_dLeftRight(bool input)
{
	m_dLeftRight = input;
}
void CharacterObject::setIsMoving(bool input)
{
	isMoving = input;
}

ItemObject* CharacterObject::getCurrentItem()
{
	return currentItem;
}
CharacterStats CharacterObject::getStatistics()
{
	return Statistics;
}
bool CharacterObject::getResting()
{
	return resting;
}
bool CharacterObject::getWorkingHard()
{
	return WorkingHard;
}
bool CharacterObject::getAsleep()
{
	return asleep;
}
bool CharacterObject::getGiveUp()
{
	return giveUp;
}
bool CharacterObject::getCounted()
{
	return counted;
}
bool CharacterObject::getM_dLeftRight()
{
	return m_dLeftRight;
}
bool CharacterObject::getIsMoving()
{
	return isMoving;
}

void CharacterObject::Update(double dt)
{
	if (!giveUp)
	{
		if (Statistics.m_frustration < 100 && resting == false)
		{
			Statistics.m_frustration += 5.8f / Statistics.m_experience * 1 / m_Count * dt;
		}
		if (Statistics.m_frustration > 0 && asleep == true)
		{
			Statistics.m_frustration -= 7.f / Statistics.m_experience * 1 / m_Count * dt;
		}
		if (Statistics.m_frustration > 0 && resting == true)
		{
			Statistics.m_frustration -= 5.8f / Statistics.m_experience * 1 / m_Count * dt;
		}
		if (Statistics.m_frustration < 100 && WorkingHard == true && resting == false)
		{
			Statistics.m_frustration += 10.5f / Statistics.m_experience * 1 / m_Count * dt;
		}
		if (Statistics.m_frustration < 0.005f)
		{
			Statistics.m_frustration = 0.005f;
		}
		if (Statistics.m_rest > 0 && resting == false && WorkingHard == false)
		{
			Statistics.m_rest -= 0.5f  *  Statistics.m_experience * dt / m_Count;
		}
		if (Statistics.m_rest < 100 && resting == true)
		{
			Statistics.m_rest += 0.1f  *  Statistics.m_experience * dt / m_Count;
		}
		if (Statistics.m_rest < 100 && WorkingHard == true)
		{
			Statistics.m_rest -= 1.f  *  Statistics.m_experience * dt / m_Count;
		}
		if (Statistics.m_rest < 100 && asleep == true)
		{
			Statistics.m_rest += 1.f  *  Statistics.m_experience * dt / m_Count;
		}
		if (Statistics.m_rest < 0.005f)
		{
			Statistics.m_rest = 0.005f;
		}
		if (Statistics.m_motivation > 0 && resting == false)
		{
			Statistics.m_motivation -= 0.5f * Statistics.m_experience * dt / m_Count;
		}
		if (Statistics.m_motivation < 100 && resting == true)
		{
			Statistics.m_motivation += 0.5f * Statistics.m_experience * dt / m_Count;
		}
		if (Statistics.m_motivation < 100 && resting == false && WorkingHard == true)
		{
			Statistics.m_motivation += 1.f * Statistics.m_experience * dt / m_Count;
		}
		if (Statistics.m_motivation < 0.00f)
		{
			Statistics.m_motivation = 0.0005f;
		}
		if (Statistics.m_rest < 0.00f)
		{
			Statistics.m_rest = 0.005f;
		}
		if (Statistics.m_workDone < 100 && resting == false && WorkingHard == false)
		{
			Statistics.m_workDone += 5.50f / Statistics.m_experience * Statistics.m_motivation / Statistics.m_rest *  dt / m_Count;
		}
		if (Statistics.m_workDone < 100 && WorkingHard == true && resting == false)
		{
			Statistics.m_workDone += 8.f / Statistics.m_experience * Statistics.m_motivation / Statistics.m_rest *  dt / m_Count;
		}
		if (Statistics.m_workDone < 100 && asleep == true)
		{
			Statistics.m_workDone += 0.0f;
		}
		if (Statistics.m_frustration >= 100 || Statistics.m_rest <= 0 || Statistics.m_motivation <= 0)
		{
			giveUp = true;
		}
	}
	if (giveUp == true && counted == false)
	{
		m_Count -= 1;
		counted = true;
	}
}
void CharacterObject::reset()
{
	Statistics.m_frustration = 0.005f;
	Statistics.m_motivation = 100.f;
	Statistics.m_rest = 100.f;
	Statistics.m_workDone = 0.0f;
	giveUp = false;
	m_Count = 4;
}
void CharacterObject::UpdateMovement(double dt, float m_worldWidth, float m_worldHeight)
{
	if (Application::IsKeyPressed('D') || Application::IsKeyPressed('A') || Application::IsKeyPressed('S') || Application::IsKeyPressed('W'))
	{
		isMoving = true;
		if (Application::IsKeyPressed('D') && pos.x < m_worldWidth - scale.x/2 - 17)
		{
			pos.x += 1;
			m_dLeftRight = false;
		}
		if (Application::IsKeyPressed('A') && pos.x > 0 + scale.x/2 + 16 )
		{
			pos.x -= 1;
			m_dLeftRight = true;
		}
		if (Application::IsKeyPressed('W') && pos.y < m_worldHeight - scale.y / 2 - 15)
		{
			cout << m_worldHeight << endl;
			cout << pos.y << endl;
			pos.y += 1;
			m_dLeftRight = false;
		}
		if (Application::IsKeyPressed('S') && pos.y > 0 + scale.y / 2 + 10)
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