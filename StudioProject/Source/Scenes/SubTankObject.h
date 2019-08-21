#pragma once

#include "PhysicsObject.h"
#include "TankObject.h"

class TankObject;

class SubTankObject : public PhysicsObject
{
public:
	enum SUBTANKOBJECT_TYPE
	{
		T_NONE,
		T_HEAD,
		T_BARRIER,
		T_TOTAL
	};
	SubTankObject(PHYSICSOBJECT_TYPE typeValue, SUBTANKOBJECT_TYPE type, TankObject* TankParent);
	~SubTankObject();
	void Update(double dt, float m_worldWidth = 0.f, float m_worldHeight = 0.f);
	void CollisionResponse(PhysicsObject* go, double dt);

	TankObject* parent;
	int TankType;

	/*Vector3 offset;
	Vector3 normal_position;

	float angle_normal;
	float angle_normal_prev;
	float angle_offset;

	int level;*/
};