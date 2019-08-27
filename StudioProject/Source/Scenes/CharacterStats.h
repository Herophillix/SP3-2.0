#pragma once

class CharacterStats
{
public:
	float m_frustration;
	float m_motivation;
	float m_originFrustration;
	float m_originMotivation;
	float m_experience;


	float m_rest;
	float m_workDone;
	CharacterStats()
	{
		m_frustration = 0.f;
		m_motivation = 0.f;
		m_originFrustration = 0.f;
		m_originMotivation = 0.f;
		m_rest = 0.f;
		m_workDone = 0.f;
		m_experience = 0.f;
	}
	~CharacterStats()
	{

	}
};