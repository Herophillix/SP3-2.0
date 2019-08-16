#pragma once
#include "Source/Scenes/SceneBase.h"
#include "SheepObject.h"
class SheepGame : public SceneBase
{
private:
	float m_worldWidth;
	std::vector<SheepObject*> m_goList;
	float m_worldHeight;
	float m_Gravity;
public:

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();


	void RenderGO(SheepObject *go);
	SheepObject *FetchGO();
	~SheepGame();
};

