#ifndef FROG_OBJECT_H
#define FROG_OBJECT_H
#include "SceneFrog.h"
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
		GO_TOTAL
	};
private:
	FrogObject();
	~FrogObject();
	// SET
	void setJump();
	void setMove();
	void setHP();
	// GET
	bool getJump();
	bool getMove();
	int getHP();

	int hp;
	bool isJump;
	bool isMove;

};

#endif