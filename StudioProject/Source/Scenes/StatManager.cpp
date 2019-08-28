#include "StatManager.h"

StatManager* StatManager::SM_Instance = nullptr;

StatManager::~StatManager()
{
}

StatManager* StatManager::GetInstance()
{
	if (SM_Instance == nullptr)
	{
		SM_Instance = new StatManager;
	}
	return SM_Instance;
}

StatManager::StatManager()
{
	m_char01.m_motivation = 40;
	m_char02.m_motivation = 45;
	m_char03.m_motivation = 99;
	m_char04.m_motivation = 20;

	m_char01.m_frustration = 30;
	m_char02.m_frustration = 40;
	m_char03.m_frustration = 25;
	m_char04.m_frustration = 53;

	m_char01.m_originMotivation = 0;
	m_char02.m_originMotivation = 0;
	m_char03.m_originMotivation = 0;
	m_char04.m_originMotivation = 0;

	m_char01.m_originFrustration = 0;
	m_char02.m_originFrustration = 0;
	m_char03.m_originFrustration = 0;
	m_char04.m_originFrustration = 0;

	m_resetMole = false;
	m_resetMaze = false;
	m_resetTank = false;
	m_resetSheep = false;
	m_resetFrogger = false;

}

CharacterStats StatManager::GetChar01()
{
	return m_char01;
}

CharacterStats StatManager::GetChar02()
{
	return m_char02;
}

CharacterStats StatManager::GetChar03()
{
	return m_char03;
}

CharacterStats StatManager::GetChar04()
{
	return m_char04;
}

int StatManager::GetDayNo()
{
	return m_DayNo;
}

// The if statements are for the minigames if the player gets an s rank or f rank
void StatManager::UpdateChar01M(float motivation)
{
	m_char01.m_motivation = motivation;
	if (m_char01.m_motivation > 100.f)
	{
		m_char01.m_motivation = 100.f;
	}
	else if (m_char01.m_motivation < 0.f)
	{
		m_char01.m_motivation = 0.f;
	}
}

void StatManager::UpdateChar01F(float frustration)
{
	m_char01.m_frustration = frustration;
	if (m_char01.m_frustration > 100.f)
	{
		m_char01.m_frustration = 100.f;
	}
	else if (m_char01.m_frustration < 0.f)
	{
		m_char01.m_frustration = 0.f;
	}
}

void StatManager::UpdateChar02M(float motivation)
{
	m_char02.m_motivation = motivation;
	if (m_char02.m_motivation > 100.f)
	{
		m_char02.m_motivation = 100.f;
	}
	else if (m_char02.m_motivation < 0.f)
	{
		m_char02.m_motivation = 0.f;
	}
}

void StatManager::UpdateChar02F(float frustration)
{
	m_char02.m_frustration = frustration;
	if (m_char02.m_frustration > 100.f)
	{
		m_char02.m_frustration = 100.f;
	}
	else if (m_char02.m_frustration < 0.f)
	{
		m_char02.m_frustration = 0.f;
	}
}

void StatManager::UpdateChar03M(float motivation)
{
	m_char03.m_motivation = motivation;
	if (m_char03.m_motivation > 100.f)
	{
		m_char03.m_motivation = 100.f;
	}
	else if (m_char03.m_motivation < 0.f)
	{
		m_char03.m_motivation = 0.f;
	}
}

void StatManager::UpdateChar03F(float frustration)
{
	m_char03.m_frustration = frustration;
	if (m_char03.m_frustration > 100.f)
	{
		m_char03.m_frustration = 100.f;
	}
	else if (m_char03.m_frustration < 0.f)
	{
		m_char03.m_frustration = 0.f;
	}
}

void StatManager::UpdateChar04M(float motivation)
{
	m_char04.m_motivation = motivation;
	if (m_char04.m_motivation > 100.f)
	{
		m_char04.m_motivation = 100.f;
	}
	else if (m_char04.m_motivation < 0.f)
	{
		m_char04.m_motivation = 0.f;
	}
}

void StatManager::UpdateChar04F(float frustration)
{
	m_char04.m_frustration = frustration;
	if (m_char04.m_frustration > 100.f)
	{
		m_char04.m_frustration = 100.f;
	}
	else if (m_char04.m_frustration < 0.f)
	{
		m_char04.m_frustration = 0.f;
	}
}

void StatManager::UpdateChar01R(float rest)
{
	m_char01.m_rest = rest;
	if (m_char01.m_rest > 100.f)
	{
		m_char01.m_rest = 100.f;
	}
	else if (m_char01.m_rest < 0.f)
	{
		m_char01.m_rest = 0.f;
	}
}

void StatManager::UpdateChar02R(float rest)
{
	m_char02.m_rest = rest;
	if (m_char02.m_rest > 100.f)
	{
		m_char02.m_rest = 100.f;
	}
	else if (m_char02.m_rest < 0.f)
	{
		m_char02.m_rest = 0.f;
	}
}

void StatManager::UpdateChar03R(float rest)
{
	m_char03.m_rest = rest;
	if (m_char03.m_rest > 100.f)
	{
		m_char03.m_rest = 100.f;
	}
	else if (m_char03.m_rest < 0.f)
	{
		m_char03.m_rest = 0.f;
	}
}

void StatManager::UpdateChar04R(float rest)
{
	m_char04.m_rest = rest;
	if (m_char04.m_rest > 100.f)
	{
		m_char04.m_rest = 100.f;
	}
	else if (m_char04.m_rest < 0.f)
	{
		m_char04.m_rest = 0.f;
	}
}

void StatManager::SetCharsOriginalValues()
{
	m_char01.m_originMotivation = m_char01.m_motivation;
	m_char01.m_originFrustration = m_char01.m_frustration;

	m_char02.m_originMotivation = m_char02.m_motivation;
	m_char02.m_originFrustration = m_char02.m_frustration;

	m_char03.m_originMotivation = m_char03.m_motivation;
	m_char03.m_originFrustration = m_char03.m_frustration;

	m_char04.m_originMotivation = m_char04.m_motivation;
	m_char04.m_originFrustration = m_char04.m_frustration;
}

void StatManager::ResetValues()
{
	m_char01.m_motivation = m_char01.m_originMotivation;
	m_char01.m_frustration = m_char01.m_originFrustration;

	m_char02.m_motivation = m_char02.m_originMotivation;
	m_char02.m_frustration = m_char02.m_originFrustration;

	m_char03.m_motivation = m_char03.m_originMotivation;
	m_char03.m_frustration = m_char03.m_originFrustration;

	m_char04.m_motivation = m_char04.m_originMotivation;
	m_char04.m_frustration = m_char04.m_originFrustration;
}

void StatManager::SetBool_Mole(bool set)
{
	m_resetMole = set;
}

void StatManager::SetBool_Maze(bool set)
{
	m_resetMaze = set;
}

void StatManager::SetBool_Tank(bool set)
{
	m_resetTank = set;
}

void StatManager::SetBool_Sheep(bool set)
{
	m_resetSheep = set;
}

void StatManager::SetBool_Frogger(bool set)
{
	m_resetFrogger = set;
}

bool StatManager::GetBool_Game(int gameID)
{
	switch (gameID)
	{
	case 1:
		return m_resetMaze;
		break;
	case 2:
		return m_resetMole;
		break;
	case 3:
		return m_resetTank;
		break;
	case 4:
		return m_resetFrogger;
		break;
	case 5:
		return m_resetSheep;
		break;
	default:
		return false;
		break;
	}
}

void StatManager::SetPrevGame(int gameID)
{
	m_prevGame = gameID;
}

int StatManager::GetPrevGame()
{
	return m_prevGame;
}

void StatManager::UpdateChar01WD(float workDone)
{
	m_char01.m_workDone += workDone;
}

void StatManager::UpdateChar02WD(float workDone)
{
	m_char02.m_workDone += workDone;
}

void StatManager::UpdateChar03WD(float workDone)
{
	m_char03.m_workDone += workDone;
}

void StatManager::UpdateChar04WD(float workDone)
{
	m_char04.m_workDone += workDone;
}

void StatManager::UpdateDay(int day)
{
	m_DayNo += day;
}
