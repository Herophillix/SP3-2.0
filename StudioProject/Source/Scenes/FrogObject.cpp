#include "FrogObject.h"

FrogObject::FrogObject(FROGOBJECT_TYPE typevalue) :
	Frog_pos(0, 10, 0),
	Frog_jumpVel(0, 0, 0),
	hp(3),
	isLeft(false),
	isJump(false),
	isInvincible(false),
	timerInvincibility(0),
	score(0),
	coinLeft(0),
	Frog_vel(0, 0, 0)

{
	type = typevalue;
	SoundSystem.AddSound("Collected_coin", "Sounds//Frog_coin_collect.wav");
	SoundSystem.AddSound("rock", "Sounds//Frog_rock_impact.wav");
}

FrogObject::~FrogObject()
{

}
// GETS
bool FrogObject::getJump()
{
	return isJump;
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

void FrogObject::setNormal(Vector3 input)
{
	normal = input;
}
void FrogObject::setHp(int input, bool additive)
{
	if (additive)
	{
		hp += input;
	}
	else
	{
		hp = input;
	}
}
void FrogObject::setTimerInvicibility(double input, bool additive)
{
	if (additive)
	{
		timerInvincibility += input;
	}
	else
	{
		timerInvincibility = input;
	}
}
bool FrogObject::getSide()
{
	return isLeft;
}
// SETS

void FrogObject::setJump(bool jump)
{
	isJump = jump;
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

void FrogObject::setSide(bool leftTrue)
{
	isLeft = leftTrue;
}

// FUNCTIONS
Vector3 FrogObject::getNormal()
{
	return normal;
}

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
			go->pos.y -= 3;
			timerInvincibility = 0;
			SoundSystem.PlayASound("rock");
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
		SoundSystem.PlayASound("Collected_coin");
		go2->active = false;
		break;
	}
	}
}
