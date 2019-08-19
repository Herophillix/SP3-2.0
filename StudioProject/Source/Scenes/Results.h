#ifndef RESULTS_H
#define RESULTS_H

#include <iostream>
#include <sstream>
#include <vector>
#include "../Rendering/MeshBuilder.h"
#include "../Rendering/Particles.h"
#include "../Rendering/shader.hpp"
#include "../Rendering/LoadTGA.h"
#include "../Rendering/Mesh.h"
#include "../SpriteAnimation.h"
#include "../Application.h"
#include "../Utility.h"
#include "../Light.h"
#include "MatrixStack.h"
#include "StatManager.h"
#include "SceneBase.h"
#include "GL\glew.h"
#include "Mtx44.h"

#include "ResultObject.h"

class Results : public SceneBase
{
public:
	static Results* getInstance();
	~Results();


	void InitVars();
	void InitButtons();
	void InitStatsToDist(int stats);
	void UpdateVars(double dt);
	void RenderStats();
	void RenderButtons();
	void RenderResults(int score);
	void RenderGO(ResultObject* go);
	bool ButtonMouseCollision();

private:
	static Results* r_instance;
	Results();

	float m_worldWidth;
	float m_worldHeight;
	float m_halfWorldWidth;
	float m_halfWorldHeight;

	float m_quarterWorldWidth;
	float m_eightWorldWidth;
	float m_sixteenthWorldWidth;
	float m_thirtytwothWorldWidth;

	float m_sixthWorldHeight;
	float m_quarterWorldHeight;
	float m_twelfthWorldHeight;
	float m_twentyfourthWorldHeight;

	Vector3 r_quad01Pos;
	Vector3 r_quad02Pos;
	Vector3 r_quad03Pos;
	Vector3 r_quad04Pos;

	Vector3 MousePos;

	ResultObject* continueButton;
	ResultObject* resetButton;

	ResultObject* c01PlusM;
	ResultObject* c01MinusM;
	ResultObject* c01PlusF;
	ResultObject* c01MinusF;

	int m_statsToDistribute;
	int m_originStatsToDistribute;
	vector<ResultObject*> ButtonList;
};


#endif // !RESULTS_H

