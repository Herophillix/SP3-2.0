#ifndef SCENEMAZE_H
#define SCENEMAZE_H

#include "SceneBase.h"
#include "PhysicsObject.h"
#include "MenuObject.h"
#include "../Minigames/Maze/MazeGenerator.h"
#include "../SoundEngine.h"
#include "Results.h"
#include <vector>

class SceneMaze : public SceneBase
{
public:
	SceneMaze();
	~SceneMaze();

	virtual void Init();
	virtual void Update(double dt);
	void UpdateMenu(double dt);
	void UpdateGame(double dt);
	void UpdateGameOver(double dt);
	virtual void Render();
	void RenderMenu();
	void RenderGame();
	void RenderGameOver();
	void Reset();
	virtual void Exit();
	


	void RenderGO(PhysicsObject *go);
	PhysicsObject* FetchGO();

	// James 13/8/2019
	bool CheckCollision(PhysicsObject* go, PhysicsObject* go2);
	// End James 13/8/2019

	// James 15/8/2019
	void ActivateStencil();
	void DeactivateStencil();
	// End James 15/8/2019

	void GameEndCalculations();

	enum SceneState
	{
		S_MENU,
		S_GAME,
		S_GAMEOVER
	};

private:
	std::vector<PhysicsObject *>* m_goList;
	std::vector<MenuObject *> m_menuList;
	float m_speed;
	float m_worldWidth;
	float m_worldHeight;
	bool musicPlay;
	bool musicPlayed;
	MazeGenerator Maze;
	// James 13/8/2019
	//Mesh* meshList[NUM_GEOMETRY];
	Vector3 v_mousepos;
	PhysicsObject *tempwall, *tempwall2, *tempwall3, *tempwall4;
	// End James 13/8/2019

	// James 15/8/2019
	PhysicsObject* Ball;
	bool enableStencil;
	// End James 15/8/2019	
	float bounceTime;
	int SceneState;
	bool endGame;
	double elapsedTime;
	bool statgained;
	float score;
	char grade;
	float stencilsize;
	bool mousepressed;
	double endGametime;

	CSoundEngine soundSystem;
};

#endif // !STUDIOPROJECT_SCENE_H
