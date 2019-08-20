#pragma once
#include "Source/Scenes/SceneBase.h"
#include "SheepObject.h"
class SheepGame : public SceneBase
{
private:
	float m_worldWidth;
	std::vector<SheepObject*> m_goList;
	float m_worldHeight;
	Vector3 m_Gravity;
	Vector3 mousePos;
	float m_Timer;
	Vector3 pos;
	SheepObject* tempwall;
	SheepObject* EvilKingSheep;
	SheepObject* player;
	SheepObject* Warning;
	SheepObject* Warning2;
	SheepObject* Warning3;
	int points;
	bool pointGain;
	bool Transition;
	bool EvilKing;
	float transitionY;
	const int TraceSize = 30;
	SheepObject *Trace[30];
public:

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();
	SheepGame();
	void renderBG();
	void renderLives();
	void renderCrossHair();
	void renderEvilSheep();
	void RenderGO(SheepObject *go);
	void UpdateRayTracing(double dt);
	bool CollisionCheck(SheepObject *go, SheepObject *go2);
	SheepObject *FetchGO();
	~SheepGame();
};
