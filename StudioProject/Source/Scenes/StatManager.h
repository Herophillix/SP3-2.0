#ifndef STAT_MANAGER_H
#define STAT_MANAGER_H
#include <iostream>
#include <sstream>
#include <vector>
#include "Mtx44.h"
#include "../Utility.h"

struct CharacterStats
{
	float m_frustration;
	float m_motivation;
	float m_originFrustration;
	float m_originMotivation;


	float m_rest;
	float m_workDone;
};


class StatManager
{
public:
	~StatManager();
	static StatManager* GetInstance();
	CharacterStats GetChar01();
	CharacterStats GetChar02();
	CharacterStats GetChar03();
	CharacterStats GetChar04();


	// These functions ADD ON to the characters stats
	void UpdateChar01M(float motivation);
	void UpdateChar01F(float frustration);
	void UpdateChar02M(float motivation);
	void UpdateChar02F(float frustration);
	void UpdateChar03M(float motivation);
	void UpdateChar03F(float frustration);
	void UpdateChar04M(float motivation);
	void UpdateChar04F(float frustration);

	void SetCharsOriginalValues();
	void ResetValues();

private:
	StatManager();
	static StatManager* SM_Instance;

	CharacterStats m_char01;
	CharacterStats m_char02;
	CharacterStats m_char03;
	CharacterStats m_char04;
	int m_DayNo;
};


#endif // !STAT_MANAGER_H

