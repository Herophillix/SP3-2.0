#include "SubTankObject.h"
#include "SceneTank.h"

SubTankObject::SubTankObject(PHYSICSOBJECT_TYPE typeValue, SUBTANKOBJECT_TYPE type, TankObject* TankParent)
{
	this->type = typeValue;
	TankType = type;
	parent = TankParent;
}

SubTankObject::~SubTankObject()
{

}

void SubTankObject::Update(double dt, float m_worldWidth, float m_worldHeight)
{
	/*float tempvel = 50 * dt;
	if (Application::IsKeyPressed('A'))
	{
		pos.x -= tempvel;
	}
	else if (Application::IsKeyPressed('D'))
	{
		pos.x += tempvel;
	}
	if (Application::IsKeyPressed('S'))
	{
		pos.y -= tempvel;
	}
	else if (Application::IsKeyPressed('W'))
	{
		pos.y += tempvel;
	}*/
}

void SubTankObject::CollisionResponse(PhysicsObject* go, double dt)
{
	if (go == parent->getBall())
	{
		return;
	}
	else
	{
		SubTankObject* go2 = this;
		switch (go2->TankType)
		{
		case T_HEAD:
		{
			go->setActive(false);
			if (go->getType() != PhysicsObject::GO_TRACE)
			{
				parent->setHealth(-1, true);
				if (!parent->getIsPlayer())
				{
					SceneTank::score += 250;
				}
				parent->setBall(nullptr);
			}
			break;
		}
		default:
		{
			switch (go2->type)
			{
			case PhysicsObject::GO_WALL:
			{
				// BALL-WALL COLLISION
				go->vel = go->vel - 1.98f * go->vel.Dot(go2->normal) * go2->normal;
				if (go->vel.Length() > 0)
				{
					go->vel = Math::Clamp(go->vel.Length(), 0.f, 75.f) * go->vel.Normalized();
				}
				break;
			}
			case PhysicsObject::GO_PILLAR:
			{
				// BALL-PILLAR COLLISION
				Vector3 N = (go2->pos - go->getPos()).Normalized();
				go->vel = go->vel - 2 * go->vel.Dot(N) * N;
				break;
			}
			default:
				break;
			}
			break;
		}
		}
	}
}