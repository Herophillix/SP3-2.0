#ifndef STAT_MANAGER_H
#define STAT_MANAGER_H
#include <iostream>
#include <sstream>
#include <vector>
#include "Mtx44.h"
#include "../Utility.h"
#include "CharacterStats.h"

class StatManager
{
public:
	~StatManager();
	static StatManager* GetInstance();
	CharacterStats GetChar01();
	CharacterStats GetChar02();
	CharacterStats GetChar03();
	CharacterStats GetChar04();
	int GetDayNo();


	CharacterStats m_char01;
	CharacterStats m_char02;
	CharacterStats m_char03;
	CharacterStats m_char04;
	// These functions ADD ON to the characters stats
	void UpdateChar01M(float motivation);
	void UpdateChar01F(float frustration);
	void UpdateChar02M(float motivation);
	void UpdateChar02F(float frustration);
	void UpdateChar03M(float motivation);
	void UpdateChar03F(float frustration);
	void UpdateChar04M(float motivation);
	void UpdateChar04F(float frustration);

	void UpdateChar01R(float rest);
	void UpdateChar02R(float rest);
	void UpdateChar03R(float rest);
	void UpdateChar04R(float rest);

	void UpdateChar01WD(float workDone);
	void UpdateChar02WD(float workDone);
	void UpdateChar03WD(float workDone);
	void UpdateChar04WD(float workDone);

	void UpdateDay(int day);

	void SetCharsOriginalValues();
	void ResetValues();

	void SetBool_Mole(bool set);
	void SetBool_Maze(bool set);
	void SetBool_Tank(bool set);
	void SetBool_Sheep(bool set);
	void SetBool_Frogger(bool set);

	bool GetBool_Game(int gameID);

	void SetPrevGame(int gameID);
	int GetPrevGame();

private:
	StatManager();
	static StatManager* SM_Instance;
	int m_DayNo;
	int m_prevGame;

	// Meaning if they are good to be reseted
	bool m_resetMaze;		// 1
	bool m_resetMole;		// 2
	bool m_resetTank;		// 3
	bool m_resetFrogger;	// 4
	bool m_resetSheep;		// 5
};


#endif // !STAT_MANAGER_H

