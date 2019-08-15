#include "Particles.h"



Particles::Particles(ParticleObject_TYPE typeValue) :
	type(typeValue),
	pos(0,0,0),
	lifeTime(0),
	scale(1,1,1),
	rotation(0),
	rotationSpeed(0),
	active(false)
{
}


Particles::~Particles()
{
}
