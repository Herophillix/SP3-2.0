#ifndef FROG_OBJECT_H
#define FROG_OBJECT_H

#include "GameObject.h"
#include "../SoundEngine.h"

class FrogObject : public GameObject
{
public:
	enum FROGOBJECT_TYPE
	{
		GO_NONE,
		GO_FROG,
		GO_ROCK,
		GO_TRAP,
		GO_COIN,
		GO_PLATFORM,
		GO_TOTAL
	};
	FrogObject(FROGOBJECT_TYPE typevalue = GO_NONE);
	~FrogObject();

	Vector3 Frog_pos;
	Vector3 Frog_jumpVel;
	Vector3 Frog_vel;



	// SET
	void setJump(bool Jump);
	void setMove(bool Move);
	void setHP(int health);
	void setInvincible(bool invin);
	void setCoin(int coins);
	void setScore(int score);
	void setSide(bool leftTrue);
	// GET
	bool getJump();
	bool getMove();
	int getHP();
	bool getInvincible();
	int getScore();
	int getCoin();
	bool getSide();


	// Functions
	void CollisionResponse(FrogObject *go, FrogObject* go2, double dt);
	void FrogInvincibilityFrame(FrogObject *go, double dt);
	void plusCoin(FrogObject* frog);
	CSoundEngine SoundSystem;


	void setNormal(Vector3);
	void setHp(int, bool additive = false);
	void setTimerInvicibility(double, bool additive = false);

	Vector3 getNormal();
	int getHp();
	double getTimerInvicibility();


private:
	bool isJump;
	bool isLeft;
	bool isInvincible;
	int coinLeft;
	int score;

	Vector3 normal;
	int hp;
	double timerInvincibility;
};

#endif