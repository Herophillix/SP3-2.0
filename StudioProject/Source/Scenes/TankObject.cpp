#include "TankObject.h"

TankObject* TankObject::currentTank = nullptr;
int TankObject::TankCount = 0;
int TankObject::TankIndex = 0;

TankObject::TankObject(PHYSICSOBJECT_TYPE typeValue)
{
	type = typeValue;
	++TankCount;
}

TankObject::~TankObject()
{
	--TankCount;
}

void TankObject::Update(double dt, float m_worldWidth, float m_worldHeight)
{
	float tempvel = 100 * dt;
	if (Application::IsKeyPressed('A'))
	{
		pos.x -= tempvel;
	}
	if (Application::IsKeyPressed('D'))
	{
		pos.x += tempvel;
	}
}

void TankObject::CollisionResponse(PhysicsObject* go, double dt)
{
	PhysicsObject* go2 = this;
	go->vel = go->vel - 1.98f * go->vel.Dot(go2->normal) * go2->normal;
	if (go->vel.Length() > 0)
	{
		go->vel = Math::Clamp(go->vel.Length(), 0.f, 75.f) * go->vel.Normalized();
	}
	if (this != currentTank)
	{
	}
}