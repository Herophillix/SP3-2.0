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
	m_char02.m_motivation = 0;
	m_char03.m_motivation = 0;
	m_char04.m_motivation = 0;

	m_char01.m_frustration = 0;
	m_char02.m_frustration = 0;
	m_char03.m_frustration = 0;
	m_char04.m_frustration = 0;

	m_char01.m_originMotivation = 0;
	m_char02.m_originMotivation = 0;
	m_char03.m_originMotivation = 0;
	m_char04.m_originMotivation = 0;

	m_char01.m_originFrustration = 0;
	m_char02.m_originFrustration = 0;
	m_char03.m_originFrustration = 0;
	m_char04.m_originFrustration = 0;

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

void StatManager::UpdateChar01M(float motivation)
{
	m_char01.m_motivation += motivation;
}

void StatManager::UpdateChar01F(float frustration)
{
	m_char01.m_frustration += frustration;
}

void StatManager::UpdateChar02M(float motivation)
{
	m_char02.m_motivation += motivation;
}

void StatManager::UpdateChar02F(float frustration)
{
	m_char02.m_frustration += frustration;
}

void StatManager::UpdateChar03M(float motivation)
{
	m_char03.m_motivation += motivation;
}

void StatManager::UpdateChar03F(float frustration)
{
	m_char03.m_frustration += frustration;
}

void StatManager::UpdateChar04M(float motivation)
{
	m_char04.m_motivation += motivation;
}

void StatManager::UpdateChar04F(float frustration)
{
	m_char04.m_frustration += frustration;
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
