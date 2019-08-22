#ifndef  PARTICLES_H
#define PARTICLES_H

#include <Vector3.h>

using namespace std;

enum ParticleObject_TYPE
{
	P_ParticleTest,
	P_MOLE_SMOKE,
	P_TOTAL,
};

class Particles
{
public:
	Particles(ParticleObject_TYPE = P_ParticleTest);
	~Particles();

	ParticleObject_TYPE type;
	
	Vector3 pos;
	Vector3 vel;
	Vector3 scale;
	float lifeTime;
	float rotation;
	float rotationSpeed;

	bool active;
};

#endif // ! PARTICLES_H