#include "SheepObject.h"



SheepObject::SheepObject(sheepGameType typeValue)
	:spreadAngle(0),
	health(100),
	fireRate(0.337)
{
	type = typeValue;
}


SheepObject::~SheepObject()
{
}
