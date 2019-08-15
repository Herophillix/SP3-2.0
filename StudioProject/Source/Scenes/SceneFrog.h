#ifndef SCENE_FROG_H
#define SCENE_FROG_H
#include "SceneBase.h"
#include "GameObject.h"
#include "FrogObject.h"
#include <vector>


class SceneFrog :public SceneBase
{
public:

	SceneFrog();
	~SceneFrog();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();
private:
	std::vector<Particles* > m_particleList;
	float m_speed;
	float m_worldWidth;
	float m_worldHeight;
	float m_halfWorldWidth;
	float m_halfWorldHeight;

};

#endif