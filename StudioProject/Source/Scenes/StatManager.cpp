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
	m_char01.m_motivation = 0;
	m_char02.m_motivation = 0;
	m_char03.m_motivation = 0;
	m_char04.m_motivation = 0;

	m_char01.m_frustration = 0;
	m_char02.m_frustration = 0;
	m_char03.m_frustration = 0;
	m_char04.m_frustration = 0;
}

void StatManager::UpdateStats(float C01M, float C01F, float C02M, float C02F, float C03M, float C03F, float C04M, float C04F)
{
	m_char01.m_motivation = C01M;
	m_char02.m_motivation = C02M;
	m_char03.m_motivation = C03M;
	m_char04.m_motivation = C04M;

	m_char01.m_frustration = C01F;
	m_char02.m_frustration = C02F;
	m_char03.m_frustration = C03F;
	m_char04.m_frustration = C04F;
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
