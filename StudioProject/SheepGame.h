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
	float m_Timer;
	Vector3 pos;
	SheepObject* tempwall;
	SheepObject* player;
public:

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();
	SheepGame();
	void renderBG();
	void RenderGO(SheepObject *go);
	bool CollisionCheck(SheepObject *go, SheepObject *go2);
	SheepObject *FetchGO();
	SheepGame();
	~SheepGame();
};
