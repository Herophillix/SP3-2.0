#include "TankObject.h"

TankObject* TankObject::currentTank = nullptr;
TankObject* TankObject::previousTank = nullptr;
int TankObject::TankCount = 0;
int TankObject::TankIndex = 0;

TankObject::TankObject(PHYSICSOBJECT_TYPE typeValue)
{
	Ball = nullptr;
	RightBorder = nullptr;
	LeftBorder = nullptr;
	Head = nullptr;
	type = typeValue;
	++TankCount;
	health = 2;
}

TankObject::~TankObject()
{
}

void TankObject::Update(double dt, float m_worldWidth, float m_worldHeight)
{
	if (Ball != nullptr)
	{
		if (!Ball->active)
		{
			Ball = nullptr;
		}
	}
	if (health <= 0)
	{
		DeactivateTank();
	}
	if (this != currentTank)
	{
		return;
	}
	float tempvel = 50 * dt;
	if (Application::IsKeyPressed('A') && !LeftBorder->LeftBound)
	{
		pos.x -= tempvel;
	}
	if (Application::IsKeyPressed('D') && !RightBorder->RightBound)
	{
		pos.x += tempvel;
	}
	if (Application::IsKeyPressed('S') && !DownBound)
	{
		pos.y -= tempvel;
	}
	if (Application::IsKeyPressed('W') && !Head->UpBound)
	{
		pos.y += tempvel;
	}
	LeftBorder->pos.Set(pos.x - scale.y / 2, pos.y, 0);
	RightBorder->pos.Set(pos.x + scale.y / 2, pos.y, 0);
	Head->pos.Set(pos.x, pos.y + scale.x * 1.5f, 0);
}

void TankObject::DeactivateTank()
{
	active = false;
	LeftBorder->active = false;
	RightBorder->active = false;
	Head->active = false;
	Ball = nullptr; 
	//--TankCount;
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

void TankObject::Init(vector<PhysicsObject*>* m_goList)
{
	LeftBorder = new SubTankObject(PhysicsObject::GO_PILLAR, SubTankObject::T_BARRIER, this);
	LeftBorder->scale.Set(scale.x / 2, scale.x / 2, 1);
	LeftBorder->pos.Set(pos.x - scale.y / 2, pos.y, 0);
	LeftBorder->active = true;
	m_goList->push_back(LeftBorder);

	RightBorder = new SubTankObject(PhysicsObject::GO_PILLAR, SubTankObject::T_BARRIER, this);
	RightBorder->scale.Set(scale.x / 2, scale.x / 2, 1);
	RightBorder->pos.Set(pos.x + scale.y / 2, pos.y, 0);
	RightBorder->active = true;
	m_goList->push_back(RightBorder);

	Head = new SubTankObject(PhysicsObject::GO_PILLAR, SubTankObject::T_HEAD, this);
	Head->scale.Set(scale.x, scale.x, 1);
	Head->pos.Set(pos.x, pos.y + scale.x * 1.5f, 0);
	Head->active = true;
	m_goList->push_back(Head);
}

bool TankObject::Contains(PhysicsObject* Input)
{
	if (Input == this || Input == Head || Input == RightBorder || Input == LeftBorder)
	{
		return true;
	}
	else
	{
		return false;
	}
}