#include "TankObject.h"
#include "SceneTank.h"

TankObject* TankObject::currentTank = nullptr;
TankObject* TankObject::previousTank = nullptr;
int TankObject::PlayerTankCount = 0;
int TankObject::EnemyTankCount = 0;
int TankObject::TankIndex = 0;

TankObject::TankObject(PHYSICSOBJECT_TYPE typeValue)
{
	Ball = nullptr;
	RightBorder = nullptr;
	LeftBorder = nullptr;
	Head = nullptr;
	type = typeValue;
	health = 2;
	isPlayer = false;
	radius = 0;
	fuel = 100;
}

TankObject::~TankObject()
{
}

void TankObject::setBall(PhysicsObject* input)
{
	Ball = input;
}

void TankObject::setHealth(int input, bool additive)
{
	if (additive)
	{
		health += input;
	}
	else
	{
		health = input;
	}
}

void TankObject::setIsPlayer(bool input)
{
	isPlayer = input;
}
void TankObject::setRadius(float input, bool additive)
{
	if (additive)
	{
		radius += input;
	}
	else
	{
		radius = input;
	}
}
void TankObject::setFuel(float input, bool additive)
{
	if (additive)
	{
		fuel += input;
	}
	else
	{
		fuel = input;
	}
}

SubTankObject* TankObject::getHead()
{
	return Head;
}
SubTankObject* TankObject::getLeftBorder()
{
	return LeftBorder;
}
SubTankObject* TankObject::getRightBorder()
{
	return RightBorder;
}
PhysicsObject* TankObject::getBall()
{
	return Ball;
}

int TankObject::getHealth()
{
	return health;
}
bool TankObject::getIsPlayer()
{
	return isPlayer;
}
float TankObject::getRadius()
{
	return radius;
}
float TankObject::getFuel()
{
	return fuel;
}

void TankObject::Update(double dt, float m_worldWidth, float m_worldHeight)
{
	if (Ball != nullptr)
	{
		if (!Ball->getActive())
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
	if (isPlayer && fuel > 0)
	{
		float tempvel = 50 *(float) dt;
		if (Application::IsKeyPressed('A') || Application::IsKeyPressed('D')
			|| Application::IsKeyPressed('S') || Application::IsKeyPressed('W'))
		{
			fuel -= tempvel * 2;
		}
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
	}
	LeftBorder->setPos(Vector3(pos.x - scale.y / 2, pos.y, 0));
	RightBorder->setPos(Vector3(pos.x + scale.y / 2, pos.y, 0));
	Head->setPos(Vector3(pos.x, pos.y + scale.x * 1.5f, 0));
}

void TankObject::DeactivateTank()
{
	active = false;
	LeftBorder->setActive(false);
	RightBorder->setActive(false);
	Head->setActive(false);
	Ball = nullptr; 
	if (isPlayer)
	{
		--PlayerTankCount;
		SceneTank::score -= 500;
		if (SceneTank::score < 0)
		{
			SceneTank::score = 0;
		}
	}
	else
	{
		--EnemyTankCount;
		SceneTank::score += 1000;
	}
	//--TankCount;
}

void TankObject::ActivateTank()
{
	fuel = 100;
	health = 2;
	if (!active)
	{
		active = true;
		LeftBorder->setActive(true);
		RightBorder->setActive(true);
		Head->setActive(true);
		if (isPlayer)
		{
			++PlayerTankCount;
		}
		else
		{
			++EnemyTankCount;
		}
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
}

void TankObject::Init(vector<PhysicsObject*>* m_goList)
{
	LeftBorder = new SubTankObject(PhysicsObject::GO_PILLAR, SubTankObject::T_BARRIER, this);
	LeftBorder->setScale(Vector3(scale.x / 2, scale.x / 2, 1));
	LeftBorder->setPos(Vector3(pos.x - scale.y / 2, pos.y, 0));
	LeftBorder->setActive(true);
	m_goList->push_back(LeftBorder);

	RightBorder = new SubTankObject(PhysicsObject::GO_PILLAR, SubTankObject::T_BARRIER, this);
	RightBorder->setScale(Vector3(scale.x / 2, scale.x / 2, 1));
	RightBorder->setPos(Vector3(pos.x + scale.y / 2, pos.y, 0));
	RightBorder->setActive(true);
	m_goList->push_back(RightBorder);

	Head = new SubTankObject(PhysicsObject::GO_PILLAR, SubTankObject::T_HEAD, this);
	Head->setScale(Vector3(scale.x, scale.x, 1));
	Head->setPos(Vector3(pos.x, pos.y + scale.x * 1.5f, 0));
	Head->setActive(true);
	m_goList->push_back(Head);

	radius = Head->getScale().x / 2 + scale.x;
}