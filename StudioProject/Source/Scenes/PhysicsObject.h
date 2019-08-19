#ifndef PHYSICS_OBJECT_H
#define PHYSICS_OBJECT_H

#include "GameObject.h"
#include "../Application.h"

class PhysicsObject : public GameObject
{
public:
	enum PHYSICSOBJECT_TYPE
	{
		GO_NONE = 0,
		GO_BALL,
		GO_WALL,
		GO_PILLAR,
		GO_TRACE,
		GO_CUBE,
		GO_ARROW,
		GO_TOTAL, //must be last
	};
	Vector3 vel;
	float mass;

	PhysicsObject(PHYSICSOBJECT_TYPE typeValue = GO_NONE);
	~PhysicsObject();

	bool UpBound;
	bool DownBound;
	bool LeftBound;
	bool RightBound;

	//James 13/8/2019
	Vector3 normal;
	// End James 13/8/2019
	virtual void CollisionResponse(PhysicsObject* go, double dt);
	virtual void Update(double dt, float m_worldWidth = 0.f, float m_worldHeight = 0.f);

	static Vector3 WindDirection;
};

#endif