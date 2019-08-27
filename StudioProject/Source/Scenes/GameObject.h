#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "Vector3.h"
#include "../Rendering/Mesh.h"
#include "../Application.h"

class GameObject
{
public:
	GameObject();
	~GameObject();
	void setType(int);
	void setPos(Vector3, bool additive = false);
	void setScale(Vector3, bool additive = false);
	void setActive(bool);

	int getType();
	Vector3 getPos();
	Vector3 getScale();
	bool getActive();
	int type;
	Vector3 pos;
	//Vector3 vel;
	Vector3 scale;
	bool active;
private:

};

#endif