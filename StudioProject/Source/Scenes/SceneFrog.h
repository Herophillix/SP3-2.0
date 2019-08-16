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

	void RenderGO(FrogObject *go);
	Particles* getParticle();

	void UpdateParticles(double dt);
	void RenderParticles(Particles *particle);
	void RenderAnimation();
	void RenderMap();
	FrogObject* FetchGO();

	std::vector<FrogObject* >* m_goList;
	std::vector<Particles* > m_particleList;

private:
	float m_speed;
	float m_worldWidth;
	float m_worldHeight;
	float m_halfWorldWidth;
	float m_halfWorldHeight;
	float RockCount;
	float rockSize;
	FrogObject* Frog;

	Vector3 m_grav;


};

#endif