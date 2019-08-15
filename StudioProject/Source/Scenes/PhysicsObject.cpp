#include "PhysicsObject.h"

PhysicsObject::PhysicsObject(PHYSICSOBJECT_TYPE typeValue)
	:
	normal(0, 1, 0),
	mass(1.f)
{
	type = typeValue;
}

PhysicsObject::~PhysicsObject()
{
}

void PhysicsObject::CollisionResponse(PhysicsObject* go, double dt)
{
	PhysicsObject* go2 = this;
	switch (go2->type)
	{
	case PhysicsObject::GO_BALL:
	{
		// BALL-BALL COLLISION
		float m1 = go->mass;
		Vector3 u1 = go->vel;
		Vector3 v1;

		float m2 = go2->mass;
		Vector3 u2 = go2->vel;
		Vector3 v2;

		//initialkineticenergy = 0.5f * m1 * u1.LengthSquared() + 0.5f * m2 * u2.LengthSquared();

		go->vel = u1 - (2 * m2 / (m1 + m2)) * ((u1 - u2).Dot(go->pos - go2->pos) / (go->pos - go2->pos).LengthSquared() * (go->pos - go2->pos));
		if (go->type != PhysicsObject::GO_TRACE)
		{
			go2->vel = u2 - (2 * m2 / (m1 + m2)) * ((u2 - u1).Dot(go2->pos - go->pos) / (go2->pos - go->pos).LengthSquared() * (go2->pos - go->pos));
		}

		v1 = go->vel;
		v2 = go2->vel;

		/*finalkineticenergy = 0.5f * m1 * u1.LengthSquared() + 0.5f * m2 * u2.LengthSquared();
		if (m_goList[GameObject::indextracked] == go || m_goList[GameObject::indextracked] == go2)
		{
			m_timerstarted = false;
		}*/
		break;
	}
	case PhysicsObject::GO_WALL:
	{
		// BALL-WALL COLLISION
		go->vel = go->vel - 2 * go->vel.Dot(go2->normal) * go2->normal;
		//if (go2->member == GameObject::M_WALL_NORMAL)
		//{
		//	go->vel *= 0.90f;
		//}
		//if (go2->member == GameObject::M_FLIPPER || go2->member == GameObject::M_WALL_ROTATE || go2->member == GameObject::M_WALL_MOVING)
		//{
		//	// PREVENTS THE BALL FROM FALLING THROUGH / ANGULAR MOMENTUM
		//	Vector3 temp = go2->pos - go->pos;
		//	Vector3 N = go2->normal;
		//	if (temp.Dot(go2->normal) < 0)
		//	{
		//		N = -N;
		//	}
		//	Vector3 collisionloc = go->pos - Vector3(m_worldWidth * 0.7f, m_worldHeight * 0.5f, 0) + (go->scale.x / 2 + go2->scale.x) * N;
		//	float distance = (collisionloc - go2->offset).Length();
		//	//float velocity = 2 * Math::PI / * (fabs(go2->angle_normal - go2->angle_normal_prev) / dt)
		//	go->vel += fabs(go2->angle_normal - go2->angle_normal_prev) * (1 / static_cast<float>(dt)) * -N * distance;
		//}
		//else if (go2->member >= GameObject::M_WALL_INNER && go2->member <= GameObject::M_WALL_OUTER)
		//{
		//	// PREVENTS THE BALL FROM CLIPPING THROUGH THE WALL
		//	Vector3 temp = go2->pos - go->pos;
		//	Vector3 N = go2->normal;
		//	if (temp.Dot(go2->normal) < 0)
		//	{
		//		N = -N;
		//	}
		//	Vector3 collisionloc = (go->pos - Vector3(m_worldWidth * 0.25f, m_worldHeight * 0.5f, 0)) * 0.5f + (go->scale.x / 2 + go2->scale.x) * N;
		//	float distance = (collisionloc - go2->offset).Length();
		//	go->vel += fabs(go2->angle_normal - go2->angle_normal_prev) * (1 / static_cast<float>(dt)) * -N * distance;
		//}
		//// DAMPENS THE VELOCITY
		//if (m_goList[GameObject::indextracked] == go || m_goList[GameObject::indextracked] == go2)
		//{
		//	m_timerstarted = false;
		//}
		break;
	}
	case PhysicsObject::GO_PILLAR:
	{
		// BALL-PILLAR COLLISION
		Vector3 N = (go2->pos - go->pos).Normalized();
		//	switch (go2->member)
		//	{
		//	case GameObject::M_BUMPER:
		//	{
		//		go->vel = go->vel - 2.1f * go->vel.Dot(N) * N;
		//		break;
		//	}
		//	case GameObject::M_BUMPER_POWER:
		//	{
		//		go2->prevcollide = go2->collide;
		//		go2->collide = true;
		//		go2->tracker = go;
		//		break;
		//	}
		//	case GameObject::M_POWERUP_EXTRABALL:
		//	{
		//		go2->active = false;
		//		GameObject* temp = FetchGO();
		//		temp->type = GameObject::GO_BALL;
		//		temp->pos.Set(m_worldWidth * 0.25f, m_worldHeight * 0.5f, 0);
		//		temp->scale.Set(3, 3, 1);
		//		temp->vel.SetZero();
		//		go->buffertime = 0.f;
		//		numball++;
		//		break;
		//	}
		//	case GameObject::M_POWERUP_MULTIPLIERINCREASE:
		//	{
		//		if (multiplier < 3)
		//		{
		//			multiplier++;
		//		}
		//		go2->active = false;
		//		break;
		//	}
		//	case GameObject::M_BUMPER_DISPOSABLE:
		//	{
		//		go->vel = go->vel - 2.1f * go->vel.Dot(N) * N;
		//		go2->active = false;
		//		break;
		//	}
		//	default:
		//	{
		go->vel = go->vel - 2 * go->vel.Dot(N) * N;
		//		break;
		//	}
		//	}
		break;
		//	go->vel *= 0.9f;
	}
	}
}