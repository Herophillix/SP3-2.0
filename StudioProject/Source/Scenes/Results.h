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
#include "SceneBase.h"
#include "GL\glew.h"
#include "Mtx44.h"

#include "ResultObject.h"

class Results : public SceneBase
{
public:
	static Results* getInstance();


	void InitVars();
	void UpdateVars(double dt);
	void RenderResults(int score);
	void RenderGO(ResultObject* go);

private:
	static Results* r_instance;
	Results();

	float m_worldWidth;
	float m_worldHeight;
	float m_halfWorldWidth;
	float m_halfWorldHeight;

	float m_quarterWorldWidth;
	float m_eightWorldWidth;

	float m_sixthWorldHeight;
	float m_quarterWorldHeight;

	Vector3 r_quad01Pos;
	Vector3 r_quad02Pos;
	Vector3 r_quad03Pos;
	Vector3 r_quad04Pos;

	ResultObject* continueButton;

	ResultObject* c01Plus;
	ResultObject* c01Minus;


	vector<ResultObject*> ButtonList;
};


#endif // !RESULTS_H

