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
	void Update(double dt, float m_worldWidth = 0.f, float m_worldHeight = 0.f);

	void setOffset(Vector3, bool additive = false);
	void setNormal_Position(Vector3, bool additive = false);
	void setAngle_Normal(float, bool additive = false);
	void setAngle_Normal_Prev(float, bool additive = false);
	void setAngle_Offset(float, bool additive = false);
	void setLevel(int, bool additive = false);

	Vector3 getOffset();
	Vector3 getNormal_Position();
	float getAngle_Normal();
	float getAngle_Normal_Prev();
	float getAngle_Offset();
	int getLevel();

private:
	Vector3 offset;
	Vector3 normal_position;

	float angle_normal;
	float angle_normal_prev;
	float angle_offset;

	int level;
};

#endif