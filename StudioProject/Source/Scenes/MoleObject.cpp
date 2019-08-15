
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

MoleObject::~MoleObject()
{
}