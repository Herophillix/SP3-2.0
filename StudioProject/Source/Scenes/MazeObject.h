#ifndef MAZEOBJECT_H
#define MAZEOBJECT_H

#include "PhysicsObject.h"
#include "../Application.h"

class MazeObject : public PhysicsObject
{
public:
	enum LEVEL
	{
		G_ZERO,
		G_ONE,
		G_TWO,
		G_THREE,
		G_TOTAL
	};
	MazeObject();
	~MazeObject();
	void CollisionResponse(PhysicsObject* go, double dt);
	void Update(double dt, float m_worldWidth, float m_worldHeight);

	Vector3 offset;
	Vector3 normal_position;

	float angle_normal;
	float angle_normal_prev;
	float angle_offset;

	int level;
};

#endif