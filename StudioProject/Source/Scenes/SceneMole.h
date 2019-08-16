#ifndef SCENEMOLE_H
#define SCENEMOLE_H
#include "scenebase.h"
#include "StudioProjectScene.h"
#include "GameObject.h"
#include "MoleObject.h"
#include "ResultObject.h"
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
	MoleObject* FetchGO();


	void UpdateHammerPos(); // update hammer variables
	void UpdateMoles(double dt); // update mole variables
	void RenderMachine(); // the machine and the moles
	void RenderUI();
	//void RenderResults();

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

	Vector3 m_Gravity;
	int m_particleCount;
	int MAX_PARTICLE;

	// Minigame stuff
	int m_score;
	float m_gameTimer;
	bool m_gameOver;

	// Hammer stuff
	MoleObject* m_Hammer;

	unsigned int t_hammerIdle;
	unsigned int t_hammerHit;

	// Mole Stuff
	std::vector<MoleObject *> m_moleListTop;
	std::vector<MoleObject *> m_moleListBot;
	std::vector<MoleObject *> m_moleListTotal;
	float m_popUpTimer; // timer for a random mole to pop up

	// Machine Stuff
	Vector3 m_frontScale;
	Vector3 m_midScale;
	Vector3 m_backScale;

	// Result Screen Stuff
	Vector3 r_quad01Pos;
	Vector3 r_quad02Pos;
	Vector3 r_quad03Pos;
	Vector3 r_quad04Pos;

	ResultObject* continueButton;
};

#endif 