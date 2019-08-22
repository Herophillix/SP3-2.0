#include "FrogObject.h"

FrogObject::FrogObject(FROGOBJECT_TYPE typevalue) :
	Frog_pos(0, 10, 0),
	Frog_jumpVel(0, 0, 0),
	hp(3),
	isMove(false),
	isJump(false),
	isInvincible(false),
	timerInvincibility(0),
	score(0),
	coinLeft(0),
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

bool FrogObject::getInvincible()
{
	return isInvincible;
}

int FrogObject::getScore()
{
	return score;
}

int FrogObject::getCoin()
{
	return coinLeft;
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

void FrogObject::setCoin(int coin)
{
	coinLeft = coin;
}

void FrogObject::setScore(int sco)
{
	score = sco;
}
// FUNCTIONS

void FrogObject::plusCoin(FrogObject* frog)
{
	frog->coinLeft += 1;
}

void FrogObject::FrogInvincibilityFrame(FrogObject *go, double dt)
{
	if (timerInvincibility < dt)
	{
		timerInvincibility += dt;
		go->setInvincible(true);
	}
	if (timerInvincibility >= dt)
	{
		go->setInvincible(false);
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
		if (!go->getInvincible())
		{
			go->hp -= 1;
			go->setInvincible(true);
			timerInvincibility = 0;
		//	go->FrogInvincibilityFrame(go, dt);
		}
		else if (go->getInvincible())
		{
			if (timerInvincibility >= 2)
			{
				go->setInvincible(false);
			}
		}
		break;
	}
	case FrogObject::GO_COIN:
	{
		go->score += 100;
		go->coinLeft -= 1;
		go2->active = false;
		break;
	}
	}
}