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

};


class StatManager
{
public:
	~StatManager();
	static StatManager* GetInstance();
	void UpdateStats(float C01M, float C01F, float C02M, float C02F, float C03M, float C03F,float C04M, float C04F);
	CharacterStats GetChar01();
	CharacterStats GetChar02();
	CharacterStats GetChar03();
	CharacterStats GetChar04();

private:
	StatManager();
	static StatManager* SM_Instance;

	CharacterStats m_char01;
	CharacterStats m_char02;
	CharacterStats m_char03;
	CharacterStats m_char04;
};


#endif // !STAT_MANAGER_H

