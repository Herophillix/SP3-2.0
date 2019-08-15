#include "SceneFrog.h"
#include "GL\glew.h"
#include "../Application.h"
#include <sstream>
#include "../Rendering/LoadTGA.h"
#include "../Rendering/MeshBuilder.h"
#include "../Rendering/Particles.h"


SceneFrog::SceneFrog()
{
}

SceneFrog::~SceneFrog()
{
}

void SceneFrog::Init()
{
	SceneBase::Init();

	//Calculating aspect ratio
	m_worldHeight = 100.f;
	m_worldWidth = m_worldHeight * (float)Application::GetWindowWidth() / Application::GetWindowHeight();
	m_halfWorldHeight = m_worldHeight / 2;
	m_halfWorldWidth = m_worldWidth / 2;
	//Physics code here
	m_speed = 1.f;

	Math::InitRNG();
	//  ******************************* PROPS HERE  ******************************* //


	meshList[GEO_BACKPANEL] = MeshBuilder::GenerateQuad("back", Color(1, 0, 0), 1.f);
	meshList[GEO_BACKPANEL]->textureID = LoadTGA("Image//backpanel.tga");
	meshList[GEO_MIDPANEL] = MeshBuilder::GenerateQuad("mid", Color(0, 1, 0), 1.f);
	meshList[GEO_MIDPANEL]->textureID = LoadTGA("Image//midpanel.tga");
	meshList[GEO_FRONTPANEL] = MeshBuilder::GenerateQuad("front", Color(0, 0, 1), 1.f);
	meshList[GEO_FRONTPANEL]->textureID = LoadTGA("Image//frontpanel.tga");

	meshList[GEO_TEXT] = MeshBuilder::GenerateText("text", 16, 16);
	meshList[GEO_TEXT]->textureID = LoadTGA("Image//calibri.tga");
	//  ******************************* SPRITE ANIMATIONS HERE  ******************************* //

	//  ******************************* PARTICLES HERE  ******************************* //
	Mtx44 projection;
	projection.SetToOrtho(0, m_worldWidth, 0, m_worldHeight, -10, 10);
	projectionStack.LoadMatrix(projection);
}

void SceneFrog::Update(double dt)
{
	SceneBase::Init();
}

void SceneFrog::Render()
{

}

void SceneFrog::Exit()
{
	
}