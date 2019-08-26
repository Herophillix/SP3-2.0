#ifndef SCENEMOLE_H
#define SCENEMOLE_H
#include "scenebase.h"
#include "StudioProjectScene.h"
#include "StatManager.h"
#include "GameObject.h"
#include "MoleObject.h"
#include "ResultObject.h"
#include "../SoundEngine.h"
#include "Results.h"
#include <vector>
class SceneMole : public SceneBase
{
public:
	SceneMole();
	~SceneMole();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();

	void RenderGO(MoleObject *go);
	Particles* getParticle();
	void UpdateParticles(double dt);
	void RenderParticles(Particles *particle);
	void RenderAnimation();
	void UpdateAnimations(double dt);
	MoleObject* FetchGO();

	// Game Functions
	void RenderMachine(); // the machine and the moles
	void RenderUI();
	void GameEndCalculations();
	void ResetVars();
	//void RenderResults();

	// Mole Functions
	void UpdateMoles(double dt); // update mole variables

	// Hammer Functions
	void InitHammerPosList();
	void UpdateHammerPos(char wasd); // update hammer variables
	bool HammerCollisionCheck();

private:

	std::vector<MoleObject *> m_goList;
	std::vector<Particles* > m_particleList;
	float m_speed;
	float m_worldWidth;
	float m_worldHeight;
	float m_halfWorldWidth;
	float m_halfWorldHeight;
	float m_quarterWorldWidth;
	float m_eightWorldWidth;

	float m_sixthWorldHeight;
	bool playMusic;
	Vector3 m_Gravity;
	int m_particleCount;
	int MAX_PARTICLE;

	// Minigame stuff
	int m_score;
	int m_multiplier;
	int m_hitCounter;
	int m_stats;
	float m_gameTimer;
	float m_frostTimer;
	bool m_frostOn;   
	bool m_gameOver;
	bool m_instructions;
	char m_grade;

	// Hammer stuff
	MoleObject* m_Hammer;

	//Sound
	CSoundEngine soundSystem;

	// --Textures for the hammer
	unsigned int t_hammerIdle;
	unsigned int t_hammerHit;
	unsigned int t_hammerIdle_frost;
	unsigned int t_hammerHit_frost;

	// --Positions for the hammer
	std::vector<Vector3> m_hammerPosList;
	int m_hammerPosIndex;
	float m_hammerMoveBT;

	// Mole Stuff
	std::vector<MoleObject *> m_moleListTop;
	std::vector<MoleObject *> m_moleListBot;
	std::vector<MoleObject *> m_moleListTotal;
	float m_popUpTimer; // timer for a random mole to pop up
	int moleTypeRNG[100];
	SpriteAnimation* explode;
	SpriteAnimation* explode2;
	SpriteAnimation* explode3;
	SpriteAnimation* explode4;
	SpriteAnimation* explode5;
	SpriteAnimation* explode6;
	SpriteAnimation* explode7;
	SpriteAnimation* explode8;
	vector<SpriteAnimation*> exList;
	// Machine Stuff
	Vector3 m_frontScale;
	Vector3 m_midScale;
	Vector3 m_backScale;
	Color multiplier;

	// Result Screen Stuff
	bool m_setOriginValues;
	bool m_setStatsToDist;
};

#endif 