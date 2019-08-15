#pragma once

#include "GameObject.h"

class CharacterObject : public GameObject
{
public:
	enum CHARACTEROBJECT_TYPE
	{
		GO_NONE,
		GO_CUBE,
		GO_QUAD,
		GO_SPRITE_TEST,
		GO_CHAR01,
		GO_CHAR02,
		GO_CHAR03,
		GO_CHAR04,
		GO_TOTAL
	};
	//Main Character Stats
	static int m_Count;

	float experience;
	float frustration;
	float motivation;
	float rest;
	float workDone;
	bool giveUp;
	bool m_dLeftRight;
	bool isMoving;

	bool getDirection();
	void setDirection(bool leftTrue);
	bool getState();
	void setState(bool moving);

	CharacterObject(CHARACTEROBJECT_TYPE typeValue = GO_NONE);
	~CharacterObject();

	void Update(double dt);
	void UpdateMovement(double dt);
};