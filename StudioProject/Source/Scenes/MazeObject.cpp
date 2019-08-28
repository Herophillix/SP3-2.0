#include "MazeObject.h"

MazeObject::MazeObject()
{
	angle_normal = 0.f;
	angle_normal_prev = 0.f;
	angle_offset = 0.f;
	level = 0;
}

MazeObject::~MazeObject()
{

}

void MazeObject::setOffset(Vector3 input, bool additive)
{
	if (additive)
	{
		offset += input;
	}
	else
	{
		offset = input;
	}
}

void MazeObject::setNormal_Position(Vector3 input, bool additive)
{
	if (additive)
	{
		normal_position += input;
	}
	else
	{
		normal_position = input;
	}
}

void MazeObject::setAngle_Normal(float input, bool additive)
{
	if (additive)
	{
		angle_normal += input;
	}
	else
	{
		angle_normal = input;
	}
}

void MazeObject::setAngle_Normal_Prev(float input, bool additive)
{
	if (additive)
	{
		angle_normal_prev += input;
	}
	else
	{
		angle_normal_prev = input;
	}
}

void MazeObject::setAngle_Offset(float input, bool additive)
{
	if (additive)
	{
		angle_offset += input;
	}
	else
	{
		angle_offset = input;
	}
}

void MazeObject::setLevel(int input, bool additive)
{
	if (additive)
	{
		level += input;
	}
	else
	{
		level = input;
	}
}

Vector3 MazeObject::getOffset()
{
	return offset;
}

Vector3 MazeObject::getNormal_Position()
{
	return normal_position;
}

float MazeObject::getAngle_Normal()
{
	return angle_normal;
}

float MazeObject::getAngle_Normal_Prev()
{
	return angle_normal_prev;
}

float MazeObject::getAngle_Offset()
{
	return angle_offset;
}

int MazeObject::getLevel()
{
	return level;
}

void MazeObject::Update(double dt, float m_worldWidth, float m_worldHeight)
{
	float tempvel = Math::DegreeToRadian(30);
	angle_normal_prev = angle_normal;
	if ((level == MazeObject::G_ZERO || level == MazeObject::G_TWO))
	{
		if (Application::IsKeyPressed('A'))
		{
			angle_normal += tempvel * static_cast<float>(dt);
			angle_offset += tempvel * static_cast<float>(dt);
		}
		else if (Application::IsKeyPressed('D'))
		{
			angle_normal -= tempvel * static_cast<float>(dt);
			angle_offset -= tempvel * static_cast<float>(dt);
		}
		else
		{
			angle_normal += tempvel / 3.f * static_cast<float>(dt);
			angle_offset += tempvel / 3.f * static_cast<float>(dt);
		}
	}
	else
	{
		if (Application::IsKeyPressed('S'))
		{
			angle_normal += tempvel * static_cast<float>(dt);
			angle_offset += tempvel * static_cast<float>(dt);
		}
		else if (Application::IsKeyPressed('W'))
		{
			angle_normal -= tempvel * static_cast<float>(dt);
			angle_offset -= tempvel * static_cast<float>(dt);
		}
		else
		{
			angle_normal -= tempvel / 3.f * static_cast<float>(dt);
			angle_offset -= tempvel / 3.f * static_cast<float>(dt);
		}
	}
	normal = Vector3(cosf(angle_normal), sinf(angle_normal), 0);
	normal_position = Vector3(cosf(angle_offset), sinf(angle_offset), 0);
	pos.x = m_worldWidth * 0.5f;
	pos.y = m_worldHeight * 0.5f;
	pos += offset.Length() * normal_position;
}

void MazeObject::CollisionResponse(PhysicsObject* go, double dt)
{
	MazeObject* go2 = this;
	float m_worldHeight = 200.f;
	float m_worldWidth = m_worldHeight * (float)Application::GetWindowWidth() / Application::GetWindowHeight();
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

		go->vel = u1 - (2 * m2 / (m1 + m2)) * ((u1 - u2).Dot(go->getPos() - go2->pos) / (go->getPos() - go2->pos).LengthSquared() * (go->getPos() - go2->pos));
		if (go->getType() != PhysicsObject::GO_TRACE)
		{
			go2->vel = u2 - (2 * m2 / (m1 + m2)) * ((u2 - u1).Dot(go2->pos - go->getPos()) / (go2->pos - go->getPos()).LengthSquared() * (go2->pos - go->getPos()));
		}

		v1 = go->vel;
		v2 = go2->vel;
		break;
	}
	case PhysicsObject::GO_WALL:
	{
		go->vel = go->vel - 1.98 * go->vel.Dot(go2->normal) * go2->normal;
		Vector3 temp = go2->pos - go->getPos();
		Vector3 N = go2->normal;
		if (temp.Dot(go2->normal) < 0)
		{
			N = -N;
		}
		Vector3 collisionloc = (go->getPos() - Vector3(m_worldWidth * 0.5f, m_worldHeight * 0.5f, 0)) * 0.5f + (go->getScale().x / 2 + go2->scale.x) * N;
		float distance = (collisionloc - go2->offset).Length();
		go->vel += fabs(go2->angle_normal - go2->angle_normal_prev) * (1 / static_cast<float>(dt)) * -N * distance;
		if (go->vel.Length() > 0)
		{
			go->vel = Math::Clamp(go->vel.Length(), 0.f, 65.f) * go->vel.Normalized();
		}
		break;
	}
	case PhysicsObject::GO_PILLAR:
	{
		Vector3 N = (go2->pos - go->getPos()).Normalized();
		go->vel = go->vel - 2 * go->vel.Dot(N) * N;
		break;
	}
	}
}