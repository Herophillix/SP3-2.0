#include "FrogObject.h"

FrogObject::FrogObject(FROGOBJECT_TYPE typevalue) :
	Frog_pos(0, 10, 0),
	Frog_jumpVel(0, 0, 0),
	hp(3),
	isMove(false),
	isJump(false),
	Frog_vel(0, 0, 0)
	
{
	type = typevalue;
}

FrogObject::~FrogObject()
{

}
// GETS
bool FrogObject::getJump()
{
	return isJump;
}

bool FrogObject::getMove()
{
	return isMove;
}

int FrogObject::getHP()
{
	return hp;
}

// SETS

void FrogObject::setJump(bool jump)
{
	isJump = jump;
}

void FrogObject::setMove(bool move)
{
	isMove = move;
}

void FrogObject::setHP(int health)
{
	hp = health;
}

void FrogObject::setInvincible(bool invin)
{
	isInvincible = invin;
}

// FUNCTIONS

void FrogObject::FrogInvincibilityFrame(FrogObject *go, double dt)
{
	double timerInvincibility;
	timerInvincibility += dt;
	while (timerInvincibility < 5)
	{
		isInvincible = true;
	}
	if (timerInvincibility >= 5)
	{
		isInvincible = false;
	}
}

void FrogObject::CollisionResponse(FrogObject* go, FrogObject* go2, double dt)
{
	float m_worldHeight = 200.f;
	float m_worldWidth = m_worldHeight * (float)Application::GetWindowWidth() / Application::GetWindowHeight();
	switch (go2->type)
	{
	case FrogObject::GO_PLATFORM:
	{
		if (go->getJump())
		{
			go->Frog_vel.y = 0;
			go->setJump(false);
		}
		break;
	}
	case FrogObject::GO_ROCK:
	{
		if (isInvincible == false)
		{
			go->hp -= 1;
			go->FrogInvincibilityFrame(go, dt);
		}
		break;
	}
	}
}