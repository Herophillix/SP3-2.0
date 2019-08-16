#pragma once

#include "PhysicsObject.h"

class TankChildObject : public PhysicsObject
{
public:
	enum TANKCHILDOBJECT_TYPE
	{
		T_NONE,
		T_HEAD,
		T_CANNON,
		T_TOTAL
	};
	TankChildObject(TANKCHILDOBJECT_TYPE typeValue);
	~TankChildObject();
	void Update(double dt, float m_worldWidth, float m_worldHeight);

	Vector3 offset;
	Vector3 normal_position;

	float angle_normal;
	float angle_normal_prev;
	float angle_offset;

	int level;
};