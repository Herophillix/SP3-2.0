#pragma once
#include "SceneBase.h"
#include "SheepObject.h"
#include "Results.h"
#include "..\SoundEngine.h"
#include "StatManager.h"

class SheepGame : public SceneBase
{
private:
	float m_worldWidth;
	std::vector<SheepObject*> m_goList;
	char m_Grade;
	float m_worldHeight;
	Vector3 m_Gravity;
	Vector3 mousePos;
	float m_Timer;
	int particleCount;
	Vector3 pos;
	SheepObject* tempwall;
	SheepObject* EvilKingSheep;
	SheepObject* player;
	SheepObject* Warning;
	SheepObject* Warning2;
	SheepObject* Warning3;
	CSoundEngine SoundSystem;
	std::vector<Particles* > m_particleList;
	float points;
	bool isFiring;
	float fireRate;
	bool pointGain;
	bool Transition;
	bool EvilKing;
	bool gameOver;
	bool statsGain;
	int MAX_PARTICLES;
	int m_particleCount;
	bool playMusic;
	float bounceTime;
	bool blKeyboardState;
	float Modifier;
	bool isLeft;
	float timer;
	bool SheepkingHit;
	float BossTimer;
	float ManaRegen;
	float transitionY;
	float Timer1;
	float Timer2;
	float Timer3;

	bool isInstructions;
	bool Timer1Check;
	bool Timer2Check;
	bool Timer3Check;
	bool stop1 = false;
	bool stop2 = false;
	bool stop3 = false;
	bool patternDone;
	bool startPhase;
	int rndNum;

	const int TraceSize = 30;
	SheepObject *Trace[30];
public:

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();
	SheepGame();
	void renderBG();
	void reset();
	void renderLives();
	void renderCrossHair();
	void renderEvilSheep();
	void UpdateParticles(double dt);
	void RenderInstructions();



	Particles* getParticle();
	void RenderParticles(Particles *particle);
	void Pattern1(double dt);
	void Pattern2(double dt);
	void Pattern3(double dt);
	void RenderGO(SheepObject *go);
	void UpdateRayTracing(double dt);
	bool CollisionCheck(SheepObject *go, SheepObject *go2);
	void GameEndCalculations();
	SheepObject *FetchGO();
	~SheepGame();
};
