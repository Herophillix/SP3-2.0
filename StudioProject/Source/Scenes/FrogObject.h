#ifndef FROG_OBJECT_H
#define FROG_OBJECT_H

#include "GameObject.h"

class FrogObject : public GameObject
{
public:
	enum FROGOBJECT_TYPE
	{
		GO_NONE,
		GO_FROG,
		GO_ROCK,
		GO_TRAP,
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
	// GET
	bool getJump();
	bool getMove();
	int getHP();

	// Functions
	void CollisionResponse(FrogObject *go, FrogObject* go2, double dt);
	void FrogInvincibilityFrame(FrogObject *go, double dt);

	Vector3 normal;


private:

	int hp;
	bool isJump;
	bool isMove;
	bool isInvincible;


};

#endif