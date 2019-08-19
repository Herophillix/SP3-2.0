#ifndef SCENETANK_H
#define SCENETANK_H

#include "SceneBase.h"
#include "PhysicsObject.h"
#include "TankObject.h"
#include <vector>

class SceneTank : public SceneBase
{
public:
	SceneTank();
	~SceneTank();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();

	void RenderGO(PhysicsObject *go);
	PhysicsObject* FetchGO();

	// James 13/8/2019
	bool CheckCollision(PhysicsObject* go, PhysicsObject* go2);
	float CheckCollision2(PhysicsObject* go, PhysicsObject* go2);
	// End James 13/8/2019

	// James 15/8/2019
	void ActivateStencil();
	void DeactivateStencil();
	// End James 15/8/2019

private:
	std::vector<PhysicsObject *>* m_goList;
	float m_speed;
	float m_worldWidth;
	float m_worldHeight;
	// James 13/8/2019
	//Mesh* meshList[NUM_GEOMETRY];
	PhysicsObject* Ghost;
	const int TraceSize = 30;
	PhysicsObject* Trace[30];
	Vector3 v_mousepos;
	PhysicsObject *tempwall, *tempwall2, *tempwall3, *tempwall4;
	// End James 13/8/2019

	// James 15/8/2019
	PhysicsObject* Ball;
	bool enableStencil;
	// End James 15/8/2019	

	bool endGame;
	double elapsedTime;

	// James 16/8/2019
	TankObject* Tank[4];
	TankObject* DummyTank;
	Vector3 OldPos;
	// End James 16/8/2019

};

#endif // !STUDIOPROJECT_SCENE_H