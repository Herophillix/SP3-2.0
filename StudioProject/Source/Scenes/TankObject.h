#pragma once

#include "PhysicsObject.h"
#include "SubTankObject.h"
#include <vector>

using namespace std;

class SubTankObject;

class TankObject : public PhysicsObject
{
public:
	TankObject(PHYSICSOBJECT_TYPE typeValue);
	~TankObject();
	void CollisionResponse(PhysicsObject* go, double dt);
	void Update(double dt, float m_worldWidth = 0.f, float m_worldHeight = 0.f);
	void Init(vector<PhysicsObject*>* m_goList);
	void ActivateTank();
	void DeactivateTank();

	static const int MaxTank = 8;
	static int PlayerTankCount;
	static int EnemyTankCount;
	static int TankIndex;
	static TankObject* currentTank;
	static TankObject* previousTank;

	SubTankObject* Head;
	SubTankObject* LeftBorder;
	SubTankObject* RightBorder;
	PhysicsObject* Ball;

	int health;
	bool isPlayer;
	float radius;
	Vector3 middlepos;
	float fuel;
};