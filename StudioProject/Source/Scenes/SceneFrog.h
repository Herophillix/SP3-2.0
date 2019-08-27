#ifndef SCENE_FROG_H
#define SCENE_FROG_H
#include "SceneBase.h"
#include "GameObject.h"
#include "FrogObject.h"
#include "../Scenes/Results.h"
#include "..\SoundEngine.h"
#include <vector>
#include <sstream>


class SceneFrog :public SceneBase
{
public:
	SceneFrog();
	~SceneFrog();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();

	void RenderGO(FrogObject *go);
	Particles* getParticle();

	void UpdateRock(double dt);
	FrogObject* getRock();

	void UpdateParticles(double dt);
	void RenderParticles(Particles *particle);
	void RenderAnimation();
	void RenderRock(FrogObject* rock);
	void RenderCoin(FrogObject* coin);
	void RenderMap();
	void Reset();
	void GameEndCalculations();
	FrogObject* FetchGO();
	CSoundEngine SoundSystem;

	std::vector<FrogObject* >* m_goList;
	std::vector<FrogObject* > rock_List;
	std::vector<Particles* > m_particleList;

	bool CheckCollision(FrogObject* go, FrogObject* go2);

	int hp;

	int coinsLeft;


private:
	float m_speed;
	float m_worldWidth;
	float m_worldHeight;
	float m_halfWorldWidth;
	float m_halfWorldHeight;
	float RockCount;
	float rockSize;
	bool m_ButtonPress;
	bool m_GameOver;
	bool m_instructions;
	float m_rockCount;
	float m_coinCount;
	float max_rock;
	float max_coin;
	float timer;
	char m_grade;
	int score;
	int instructionTimer;
	FrogObject* Frog;
	FrogObject* Platform;

	Vector3 m_grav;

	Vector3 v_mousepos;

	bool m_setOriginValues;
	bool m_setStatsToDist;
};

#endif