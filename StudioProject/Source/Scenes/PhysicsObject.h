#ifndef PHYSICS_OBJECT_H
#define PHYSICS_OBJECT_H

#include "GameObject.h"

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
		GO_TOTAL, //must be last
	};
	Vector3 vel;
	float mass;

	PhysicsObject(PHYSICSOBJECT_TYPE typeValue = GO_NONE);
	~PhysicsObject();

	//James 13/8/2019
	Vector3 normal;
	// End James 13/8/2019
	virtual void CollisionResponse(PhysicsObject* go, double dt);
};

#endif