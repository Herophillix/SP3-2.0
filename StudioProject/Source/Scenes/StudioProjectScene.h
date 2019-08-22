#ifndef STUDIOPROJECT_SCENE_H
#define STUDIOPROJECT_SCENE_H

#include "SceneBase.h"
#include "CharacterObject.h"
#include <vector>

class StudioProjectScene : public SceneBase
{
	enum GEOMETRY_TYPE
	{
		GEO_BACKGROUND,
		GEO_CUBE,
		GEO_QUAD,
		// GEOs for stats
		GEO_CHARONEFRUST,
		GEO_CHARONEMOTIVE,
		GEO_CHARONEREST,
		GEO_CHARONEWD,

		GEO_CHARTWOFRUST,
		GEO_CHARTWOMOTIVE,
		GEO_CHARTWOREST,
		GEO_CHARTWOWD,

		GEO_CHARTHREEFRUST,
		GEO_CHARTHREEMOTIVE,
		GEO_CHARTHREEREST,
		GEO_CHARTHREEWD,

		GEO_CHARFOURFRUST,
		GEO_CHARFOURMOTIVE,
		GEO_CHARFOURREST,
		GEO_CHARFOURWD,
		//Props
		GEO_TELEVISION,
		//end
		GEO_PARTICLE_TEST,
		GEO_SPRITE_ANIMATION,
		GEO_SPRITE_TEST2,
		GEO_FROG_JUMP,
		GEO_WALKRIGHT,
		GEO_WALKLEFT,
		GEO_ARROW,
		NUM_GEOMETRY
	};
public:
	StudioProjectScene();
	~StudioProjectScene();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();

	void RenderGO(CharacterObject *go);
	Particles* getParticle();
	void UpdateParticles(double dt);
	void RenderParticles(Particles *particle);
	void RenderAnimation();
	CharacterObject* FetchGO();

	void RenderBG();
	void RenderCharacter1();
	void RenderCharacter2();
	void RenderCharacter3();
	void RenderCharacter4();
	void RenderStats1();
	void RenderStats2();
	void RenderStats3();
	void RenderStats4();
	void RenderArrow();


	Vector3 vel;
	Vector3 pos;
private:
	std::vector<CharacterObject *> m_goList;
	std::vector<Particles* > m_particleList;
	float m_speed;
	float m_worldWidth;
	float m_worldHeight;
	int m_Count;
	float m_eventTimer;
	float color;
	bool b_transitioning;
	CharacterObject *charOne;
	CharacterObject *charTwo;
	CharacterObject *charThree;
	CharacterObject *charFour;
	CharacterObject *prevChar;
	CharacterObject *currentChar;
	CharacterObject *Television;
	CharacterObject *Television2;
	CharacterObject *Television3;
	CharacterObject *Television4;
	//Particles Variable
	int m_particleCount;
	int MAX_PARTICLE;
	Vector3 m_Gravity;

	float m_worldWidthDiv8;

	//Mesh* meshList[NUM_GEOMETRY];

	// Testing Stuff
	GameObject* TestCube1;
	GameObject* TestCube2;
	GameObject* TestCube3;
	GameObject* TestCube4;
};

#endif // !STUDIOPROJECT_SCENE_H
