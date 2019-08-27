
#include "GameObject.h"

GameObject::GameObject()
	: type(0),
	scale(1, 1, 1),
	active(false)
{
}

GameObject::~GameObject()
{
}

void GameObject::setType(int input)
{
	type = input;
}
void GameObject::setPos(Vector3 input, bool additive)
{
	if (additive)
	{
		pos += input;
	}
	else
	{
		pos = input;
	}
}
void GameObject::setScale(Vector3 input, bool additive)
{
	if (additive)
	{
		scale += input;
	}
	else
	{
		scale = input;
	}
}
void GameObject::setActive(bool input)
{
	active = input;
}

int GameObject::getType()
{
	return type;
}
Vector3 GameObject::getPos()
{
	return pos;
}
Vector3 GameObject::getScale()
{
	return scale;
}
bool GameObject::getActive()
{
	return active;
}
