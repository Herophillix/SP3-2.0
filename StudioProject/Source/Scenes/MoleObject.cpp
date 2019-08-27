
#include "MoleObject.h"
#include "SceneMole.h"

MoleObject::MoleObject(MOLEOBJECT_TYPE typeValue):
	mole_yOffset(0),
	mole_lifeTime(10.5f),
	mole_goUp(false),
	mole_hit(false)
{
	type = typeValue;
}

void MoleObject::setMole_yOffset(float input, bool additive)
{
	if (additive)
	{
		mole_yOffset += input;
	}
	else
	{
		mole_yOffset = input;
	}
}
void MoleObject::setMole_lifeTime(float input, bool additive)
{
	if (additive)
	{
		mole_lifeTime += input;
	}
	else
	{
		mole_lifeTime = input;
	}
}
void MoleObject::setMole_goUp(bool input)
{
	mole_goUp = input;
}
void MoleObject::setMole_hit(bool input)
{
	mole_hit = input;
}

float MoleObject::getMole_yOffset()
{
	return mole_yOffset;
}
float MoleObject::getMole_lifeTime()
{
	return mole_lifeTime;
}
bool MoleObject::getMole_goUp()
{
	return mole_goUp;
}
bool MoleObject::getMole_hit()
{
	return mole_hit;
}

MoleObject::~MoleObject()
{
}