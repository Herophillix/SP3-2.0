#ifndef STUDIOPROJECT_SCENE_H
#define STUDIOPROJECT_SCENE_H

#include "SceneBase.h"
#include "CharacterObject.h"
#include "StatManager.h"
#include "ItemObject.h"
#include "MenuObject.h"
#include "Screen.h"
#include <vector>
#include "../SoundEngine.h"

class StudioProjectScene : public SceneBase
{
public:
	enum SCENESTATE
	{
		S_GAME,
		S_LEVELTRANSITION,
		S_GAMEOVER,
	};


	StudioProjectScene();
	~StudioProjectScene();

	virtual void Init();
	virtual void Update(double dt);
	void UpdateGame(double dt);
	void UpdateLevelTransition(double dt);
	void UpdateLoseScreen(double dt);
	virtual void Render();
	void RenderGame();
	void RenderLevelTransition();
	void RenderLoseScreen();
	void reset();
	virtual void Exit();

	void RenderCharObj(CharacterObject *go);
	void RenderItemObj(ItemObject * go);
	Particles* getParticle();
	void UpdateParticles(double dt);
	void RenderParticles(Particles *particle);
	void RenderAnimation();
	GameObject* FetchGO();

	void RenderBG();
	void RenderArrow();
	void RenderScreen(Screen* ScreenSplit);
	void RenderStats(CharacterObject* Character);
	void RenderMenu(Screen* ScreenSplit);

	Vector3 vel;
	Vector3 pos;
private:
	CSoundEngine soundSystem;
	std::vector<GameObject *> m_goList;
	std::vector<Particles* > m_particleList;
	float m_speed;
	float m_worldWidth;
	bool playMusic;
	float mTimer;
	float m_worldHeight;
	int m_Count;
	float m_eventTimer;
	float color;
	bool b_transitioning;
	CharacterObject *prevChar;
	CharacterObject *currentChar;
	//Particles Variable
	int m_particleCount;
	int MAX_PARTICLE;
	Vector3 m_Gravity;

	float m_worldWidthDiv8;

	Vector3 v_mousepos;
	Vector3 rel_mousepos;
	bool mousepressed = false;

	Vector3 GameArea;
	Vector3 StatsArea;

	Screen* ScreenSplit[4];

	int phase;
	int prevlevel;
	int currentlevel;
	int SceneState;
	MenuObject* Continue;
};

#endif // !STUDIOPROJECT_SCENE_H
