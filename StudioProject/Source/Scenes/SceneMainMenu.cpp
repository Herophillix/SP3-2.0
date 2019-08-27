#include "SceneMainMenu.h"
#include "GL\glew.h"
#include "../Application.h"
#include <sstream>
#include "../Rendering/LoadTGA.h"
#include "../Rendering/MeshBuilder.h"
#include "../Rendering/Particles.h"
MainMenu::MainMenu()
{
}

MainMenu::~MainMenu()
{
}

void MainMenu::Init()
{
	SceneBase::Init();
	m_worldHeight = 100.f;
	m_worldWidth = m_worldHeight * (float)Application::GetWindowWidth() / Application::GetWindowHeight();
	m_halfWorldHeight = m_worldHeight / 2;
	m_halfWorldWidth = m_worldWidth / 2;
	m_thirdWorldHeight = m_worldHeight / 3;
	m_sixthWorldHeight = m_worldHeight / 6;

	meshList[GEO_QUAD] = MeshBuilder::GenerateQuad("test", Color(1, 1, 1), 1.f);
	meshList[GEO_GAMEFONT] = MeshBuilder::GenerateText("kzone", 16, 16);
	meshList[GEO_GAMEFONT]->textureID = LoadTGA("Image//KidsZone.tga");
	meshList[GEO_CURSOR] = MeshBuilder::GenerateQuad("cursor", Color(1, 1, 1), 10.f);
	meshList[GEO_CURSOR]->textureID = LoadTGA("Image//gameCursor.tga");

	m_NewGameButton = new MainMenuObject(MainMenuObject::GO_NONE);
	m_NewGameButton->type = MainMenuObject::GO_NEWGAME;
	m_NewGameButton->pos.Set(m_halfWorldWidth / 4, m_thirdWorldHeight * 2, 0);
	m_NewGameButton->setText("New Game");
	menuObjList.push_back(m_NewGameButton);
	m_InstructionsButton = new MainMenuObject(MainMenuObject::GO_NONE);
	m_InstructionsButton->type = MainMenuObject::GO_INSTRUCTIONS;
	m_InstructionsButton->pos.Set(m_halfWorldWidth / 4, m_sixthWorldHeight * 3, 0);
	m_InstructionsButton->setText("Instructions");
	menuObjList.push_back(m_InstructionsButton);
	m_CreditsButton = new MainMenuObject(MainMenuObject::GO_NONE);
	m_CreditsButton->type = MainMenuObject::GO_CREDITS;
	m_CreditsButton->pos.Set(m_halfWorldWidth / 4, m_thirdWorldHeight, 0);
	m_CreditsButton->setText("Credits");
	menuObjList.push_back(m_CreditsButton);
	m_ExitButton = new MainMenuObject(MainMenuObject::GO_NONE);
	m_ExitButton->type = MainMenuObject::GO_EXIT;
	m_ExitButton->pos.Set(m_halfWorldWidth / 4, m_sixthWorldHeight, 0);
	m_ExitButton->setText("Exit");
	menuObjList.push_back(m_ExitButton);

	for (unsigned int i = 0; i < menuObjList.size(); i++)
	{
		menuObjList[i]->scale.Set(5, 5, 5);
		menuObjList[i]->setxOffset(55.f);
	}

}

void MainMenu::Update(double dt)
{
	SceneBase::Update(dt);
	m_worldHeight = 100.f;
	m_worldWidth = m_worldHeight * (float)Application::GetWindowWidth() / Application::GetWindowHeight();
	m_halfWorldHeight = m_worldHeight / 2;
	m_halfWorldWidth = m_worldWidth / 2;
	m_thirdWorldHeight = m_worldHeight / 3;
	m_sixthWorldHeight = m_worldHeight / 6;


	UpdateMousePos();

}

void MainMenu::Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	m_worldHeight = 100.f;
	m_worldWidth = m_worldHeight * (float)Application::GetWindowWidth() / Application::GetWindowHeight();
	m_halfWorldHeight = m_worldHeight / 2;
	m_halfWorldWidth = m_worldWidth / 2;
	m_thirdWorldHeight = m_worldHeight / 3;
	m_sixthWorldHeight = m_worldHeight / 6;

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

	modelStack.PushMatrix();
	modelStack.Translate(m_halfWorldWidth, m_halfWorldHeight, 0);
	modelStack.Scale(192, 108, 1);
	RenderMesh(meshList[GEO_QUAD], false);
	modelStack.PopMatrix();

	std::ostringstream ss;
	ss << "Placeholder Title";
	modelStack.PushMatrix();
	modelStack.Translate(m_worldWidth / 4, m_worldHeight - m_sixthWorldHeight, 0);
	modelStack.Scale(5, 5, 5);
	RenderText(meshList[GEO_GAMEFONT], ss.str(), Color(0, 0, 0));
	modelStack.PopMatrix();

	RenderOptions();
	// Render cursor
	modelStack.PushMatrix();
	modelStack.Translate(m_mousePos);
	RenderMesh(meshList[GEO_CURSOR], false);
	modelStack.PopMatrix();
}

void MainMenu::Exit()
{
	SceneBase::Exit();
	//Cleanup GameObjects
	while (menuObjList.size() > 0)
	{
		MainMenuObject *go = menuObjList.back();
		delete go;
		menuObjList.pop_back();
	}
}

void MainMenu::RenderGO(MainMenuObject * go)
{
	switch (go->type)
	{
	case MainMenuObject::GO_NEWGAME:
	case MainMenuObject::GO_INSTRUCTIONS:
	case MainMenuObject::GO_CREDITS:
	case MainMenuObject::GO_EXIT:
		modelStack.PushMatrix();
		modelStack.Translate(go->pos.x, go->pos.y, go->pos.z);
		modelStack.Scale(go->scale.x, go->scale.y, go->scale.z);
		RenderText(meshList[GEO_GAMEFONT], go->getText(), go->getFontColor());
		modelStack.PopMatrix();
	default:
		break;
	}
}

void MainMenu::RenderOptions()
{
	for (unsigned int i = 0; i < menuObjList.size(); i++)
	{
		RenderGO(menuObjList[i]);
	}
}

void MainMenu::UpdateMousePos()
{
	double x, y;
	Application::GetCursorPos(&x, &y);
	int w = Application::GetWindowWidth();
	int h = Application::GetWindowHeight();
	float posX = static_cast<float>(x) / w * m_worldWidth;
	float posY = (h - static_cast<float>(y)) / h * m_worldHeight;

	m_mousePos.Set(posX, posY, 0);

	for (unsigned int i = 0; i < menuObjList.size(); i++)
	{
		if (m_mousePos.x < menuObjList[i]->pos.x + menuObjList[i]->scale.x + menuObjList[i]->getxOffset()
			&& m_mousePos.x > menuObjList[i]->pos.x - menuObjList[i]->scale.x
			&& m_mousePos.y < menuObjList[i]->pos.y + menuObjList[i]->scale.y
			&& m_mousePos.y > menuObjList[i]->pos.y - menuObjList[i]->scale.y)
		{
			menuObjList[i]->setFontColor(Color(0.7f, 0.7f, 0.7f));
			static bool bLButtonState = false;
			if (!bLButtonState && Application::IsMousePressed(0))
			{
				bLButtonState = true;
				std::cout << "LBUTTON DOWN" << std::endl;
				ButtonCollision((MainMenuObject::MAINMENU_OBJECTTYPE)menuObjList[i]->type);
			}
			else if (bLButtonState && !Application::IsMousePressed(0))
			{
				bLButtonState = false;
				std::cout << "LBUTTON UP" << std::endl;
			}
		}
		else
		{
			menuObjList[i]->setFontColor(Color(0.f, 0.f, 0.f));
		}
	}
}

void MainMenu::ButtonCollision(MainMenuObject::MAINMENU_OBJECTTYPE type)
{
	switch (type)
	{
	case MainMenuObject::GO_NEWGAME:
		Application::setScene(2);
		// scene change
		break;
	case MainMenuObject::GO_INSTRUCTIONS:
		// scene change
		break;
	case MainMenuObject::GO_CREDITS:
		// scene change
		break;
	case MainMenuObject::GO_EXIT:
		break;
	default:
		break;
	}
}

