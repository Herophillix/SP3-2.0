#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "Vector3.h"
#include "../Rendering/Mesh.h"
#include "../Application.h"

class GameObject
{
public:
	int type;
	Vector3 pos;
	//Vector3 vel;
	Vector3 scale;
	bool active;
	int health;
	bool isDown;
	//double reload;
	//int hp;
	////Main Character Stats
	//float experience;
	//float frustration;
	//float motivation;
	//float rest;
	//float workDone;
	//bool giveUp;
	//bool m_dLeftRight;
	//bool isMoving;

	//bool getDirection();
	//void setDirection(bool leftTrue);
	//bool getState();
	//void setState(bool moving);

	//Vector3 dir;
	//float momentOfInertia;
	//float angularVelocity;

	GameObject();
	~GameObject();
};

#endif