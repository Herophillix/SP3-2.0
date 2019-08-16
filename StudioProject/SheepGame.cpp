#include "SheepGame.h"
#include "GL\glew.h"
#include "Source/Application.h"
#include <sstream>
#include "Source/Rendering/LoadTGA.h"
#include "Source/Rendering/MeshBuilder.h"

SheepGame::SheepGame():
	m_Gravity(-9.8)
{

}

SheepGame::~SheepGame()
{
}

void SheepGame::Init()
{
	SceneBase::Init();

	//Calculating aspect ratio
	m_worldHeight = 100.f;
	m_worldWidth = m_worldHeight * (float)Application::GetWindowWidth() / Application::GetWindowHeight();

	//Variables here
	Math::InitRNG();

;

	Mtx44 projection;
	projection.SetToOrtho(0, m_worldWidth, 0, m_worldHeight, -10, 10);
	projectionStack.LoadMatrix(projection);


}

void SheepGame::Update(double dt)
{
	SceneBase::Update(dt);

	static bool bLButtonState = false;
	if (!bLButtonState && Application::IsMousePressed(0))
	{
		bLButtonState = true;
		std::cout << "LBUTTON DOWN" << std::endl;
	}
	else if (bLButtonState && !Application::IsMousePressed(0))
	{
		bLButtonState = false;
		std::cout << "LBUTTON UP" << std::endl;
	}
	static bool bRButtonState = false;
	if (!bRButtonState && Application::IsMousePressed(1))
	{
		bRButtonState = true;
		std::cout << "RBUTTON DOWN" << std::endl;
	}
	else if (bRButtonState && !Application::IsMousePressed(1))
	{
		bRButtonState = false;
		std::cout << "RBUTTON UP" << std::endl;
	}

}

void SheepGame::Render()
{

		glViewport(0, 0, 1980, 1080);
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//Calculating aspect ratio
		m_worldHeight = 100.f;
		m_worldWidth = m_worldHeight * (float)Application::GetWindowWidth() / Application::GetWindowHeight();

		// Projection matrix : Orthographic Projection
		Mtx44 projection;
		projection.SetToOrtho(0, m_worldWidth, 0, m_worldHeight, -10, 10);
		projectionStack.LoadMatrix(projection);

		// viewTest1 matrix
		viewStack.LoadIdentity();
		viewStack.LookAt(
			camera.position.x, camera.position.y, camera.position.z,
			camera.target.x, camera.target.y, camera.target.z,
			camera.up.x, camera.up.y, camera.up.z
		);
		// Model matrix : an identity matrix (model will be at the origin)
		modelStack.LoadIdentity();
}

void SheepGame::RenderGO(SheepObject * go)
{
	switch (go->type)
	{
	case SheepObject::E_SHEEP:
	{

		break;
	}
	case SheepObject::E_TURRET:
	{

		break;
	}
	default:
		break;
	}
}

SheepObject* SheepGame::FetchGO()
{
	for (int i = 0; i < m_goList.size(); i++)
	{
		if (!m_goList[i]->active)
		{
			m_goList[i]->active = true;
			return m_goList[i];
		}
	}

	for (int i = 0; i < 20; ++i)
	{
		m_goList.push_back(new SheepObject(SheepObject::E_NONE));
	}
	m_goList[m_goList.size() - 1]->active = true;
	return m_goList[m_goList.size() - 1];
}

void SheepGame::Exit()
{
	SceneBase::Exit();
	//Cleanup GameObjects
	while (m_goList.size() > 0)
	{
		GameObject *go = m_goList.back();
		delete go;
		m_goList.pop_back();
	}
}