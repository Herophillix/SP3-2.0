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
	void DeactivateTank();

	bool Contains(PhysicsObject* Input);

	static int TankCount;
	static int TankIndex;
	static TankObject* currentTank;
	static TankObject* previousTank;

	SubTankObject* Head;
	SubTankObject* LeftBorder;
	SubTankObject* RightBorder;
	PhysicsObject* Ball;

	int health;
};