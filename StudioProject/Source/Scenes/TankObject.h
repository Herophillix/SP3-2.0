#pragma once

#include "PhysicsObject.h"
#include "TankChildObject.h"

class TankObject : public PhysicsObject
{
public:
	TankObject(PHYSICSOBJECT_TYPE typeValue);
	~TankObject();
	void CollisionResponse(PhysicsObject* go, double dt);
	void Update(double dt, float m_worldWidth, float m_worldHeight);

	static int TankCount;
	static int TankIndex;
	static TankObject* currentTank;

	//TankChildObject Head;
	//TankChildObject Cannon;
};