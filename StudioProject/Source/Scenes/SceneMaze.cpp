#include "SceneMaze.h"
#include "GL\glew.h"
#include "../Application.h"
#include <sstream>
#include "../Rendering/LoadTGA.h"
#include "../Rendering/MeshBuilder.h"

SceneMaze::SceneMaze()
{
}


SceneMaze::~SceneMaze()
{
}

void SceneMaze::Init()
{
	SceneBase::Init();

	Results::getInstance()->InitVars();
	//Calculating aspect ratio
	// James 13/8/2019
	m_worldHeight = 200.f;
	// End James 13/8/2019
	m_worldWidth = m_worldHeight * (float)Application::GetWindowWidth() / Application::GetWindowHeight();

	//Physics code here
	m_speed = 1.f;

	Math::InitRNG();

	m_goList = new std::vector<PhysicsObject*>;

	meshList[GEO_MAZE_INSTRUCTIONS] = MeshBuilder::GenerateQuad("Maze_Instructions", Color(1, 1, 1), 1.f);
	meshList[GEO_MAZE_INSTRUCTIONS]->textureID = LoadTGA("Image//Maze_Instructions.tga");
	meshList[GEO_MAZE_PLUS] = MeshBuilder::GenerateQuad("Maze_Plus", Color(1, 1, 1), 1.f);
	meshList[GEO_MAZE_PLUS]->textureID = LoadTGA("Image//Maze_Plus.tga");
	meshList[GEO_MAZE_MINUS] = MeshBuilder::GenerateQuad("Maze_Minus", Color(1, 1, 1), 1.f);
	meshList[GEO_MAZE_MINUS]->textureID = LoadTGA("Image//Maze_Minus.tga");
	meshList[GEO_MAZE_START] = MeshBuilder::GenerateQuad("Maze_Start", Color(1, 1, 1), 1.f);
	meshList[GEO_MAZE_START]->textureID = LoadTGA("Image//Maze_Start.tga");
	meshList[GEO_BORDER] = MeshBuilder::GenerateQuad("Border", Color(1, 1, 1), 1.f);
	meshList[GEO_BORDER]->textureID = LoadTGA("Image//Border.tga");
	meshList[GEO_MAZE_SAMPLE] = MeshBuilder::GenerateQuad("Maze_Sample", Color(1, 1, 1), 1.f);
	meshList[GEO_MAZE_SAMPLE]->textureID = LoadTGA("Image//Maze_Sample.tga");
	meshList[GEO_TANK_CURSOR] = MeshBuilder::GenerateQuad("Cursor", Color(1, 1, 1), 1.f);
	meshList[GEO_TANK_CURSOR]->textureID = LoadTGA("Image//Tank_Cursor.tga");
	meshList[GEO_TANK_CURSOR_ALTERNATE] = MeshBuilder::GenerateQuad("Cursor	Alternate", Color(1, 1, 1), 1.f);
	meshList[GEO_TANK_CURSOR_ALTERNATE]->textureID = LoadTGA("Image//Tank_Cursor_Alternate.tga");
	// James 13/8/2019
	v_mousepos.SetZero();

	// James 14/8/2019
	tempwall = FetchGO();
	tempwall->type = PhysicsObject::GO_WALL;
	tempwall->pos = Vector3(m_worldWidth*0.5, 0, 0);
	tempwall->normal = Vector3(0, 1, 0);
	tempwall->scale.Set(5, m_worldWidth, 1);

	tempwall2 = FetchGO();
	tempwall2->type = PhysicsObject::GO_WALL;
	tempwall2->pos = Vector3(m_worldWidth*0.5, m_worldHeight, 0);
	tempwall2->normal = Vector3(0, 1, 0);
	tempwall2->scale.Set(5, m_worldWidth, 1);

	tempwall3 = FetchGO();
	tempwall3->type = PhysicsObject::GO_WALL;
	tempwall3->pos = Vector3(0, m_worldHeight * 0.5f, 0);
	tempwall3->normal = Vector3(1, 0, 0);
	tempwall3->scale.Set(5, m_worldHeight, 1);

	tempwall4 = FetchGO();
	tempwall4->type = PhysicsObject::GO_WALL;
	tempwall4->pos = Vector3(m_worldWidth, m_worldHeight * 0.5f, 0);
	tempwall4->normal = Vector3(1, 0, 0);
	tempwall4->scale.Set(5, m_worldHeight, 1);

	Maze.SetUp("Source\\Minigames\\Maze\\Map\\Map1.txt",m_goList);

	Ball = FetchGO();
	Ball->type = PhysicsObject::GO_BALL;
	Ball->vel.SetZero();
	Ball->scale.Set(2, 2, 1);
	Ball->pos.Set(m_worldWidth * 0.625f, m_worldHeight * 0.75f, 0);

	for (int i = 0; i < 3; ++i)
	{
		MenuObject* temp = new MenuObject(MenuObject::M_NONE, Vector3(60, 60, 1));
		temp->active = true;
		m_menuList.push_back(temp);
	}

	m_menuList[0]->pos.Set(m_worldWidth * 0.625f, m_worldHeight * 0.25f, 0);
	m_menuList[0]->type = MenuObject::M_STENCIL_MINUS;

	m_menuList[1]->pos.Set(m_worldWidth * 0.875f, m_worldHeight * 0.25f, 0);
	m_menuList[1]->type = MenuObject::M_STENCIL_PLUS;

	m_menuList[2]->pos.Set(m_worldWidth * 0.875f, m_worldHeight * 0.75f, 0);
	m_menuList[2]->type = MenuObject::M_START;
	// End James 14/8/2019
	// End James 13/8/2019

	// James 15/8/2019
	enableStencil = true;
	// End James 15/8/2019

	endGame = false;
	SceneState = S_MENU;
	elapsedTime = 0;
	stencilsize = 1;
	grade = 'S';
	score = 10000;
	mousepressed = false;
	endGametime = 0.0;
}

void SceneMaze::Update(double dt)
{
	SceneBase::Update(dt);
	//Calculating aspect ratio
	// James 13/8/2019
	m_worldHeight = 200.f;
	// End James 13/8/2019
	m_worldWidth = m_worldHeight * (float)Application::GetWindowWidth() / Application::GetWindowHeight();

	double x, y;
	Application::GetCursorPos(&x, &y);
	int w = Application::GetWindowWidth();
	int h = Application::GetWindowHeight();
	v_mousepos = Vector3(static_cast<float>(x) / (w / m_worldWidth), (h - static_cast<float>(y)) / (h / m_worldHeight), 0.0f);
	static bool bLButtonState = false;
	if (!bLButtonState && Application::IsMousePressed(0))
	{
		bLButtonState = true;
		std::cout << "LBUTTON DOWN" << std::endl;
		mousepressed = true;
	}
	else if (bLButtonState && !Application::IsMousePressed(0))
	{
		bLButtonState = false;
		mousepressed = false;
	}
	switch (SceneState)
	{
	case S_MENU:
	{
		UpdateMenu(dt);
		break;
	}
	case S_GAME:
	{
		UpdateGame(dt);
		break;
	}
	case S_GAMEOVER:
	{
		UpdateGameOver(dt);
		break;
	}
	}
}


void SceneMaze::UpdateGame(double dt)
{
	// James 14/8/2019
	if (endGame)
	{
		if (endGametime < 5.0)
		{
			endGametime += dt;
		}
		else
		{
			SceneState = S_GAMEOVER;
		}
	}
	tempwall->pos = Vector3(m_worldWidth*0.5, 0, 0);
	tempwall->scale.Set(5, m_worldWidth, 1);

	tempwall2->pos = Vector3(m_worldWidth*0.5, m_worldHeight, 0);
	tempwall2->scale.Set(5, m_worldWidth, 1);

	tempwall3->pos = Vector3(0, m_worldHeight * 0.5f, 0);
	tempwall3->scale.Set(5, m_worldHeight, 1);

	tempwall4->pos = Vector3(m_worldWidth, m_worldHeight * 0.5f, 0);
	tempwall4->scale.Set(5, m_worldHeight, 1);

	// End James 14/8/2019
	/*static bool bFState = false;
	if (!bFState && Application::IsKeyPressed('F'))
	{
		bFState = true;
		enableStencil = (enableStencil == true ? enableStencil = false : enableStencil = true);
		cout << "test" << endl;
	}
	else if (bFState && !Application::IsKeyPressed('F'))
	{
		bFState = false;
	}

	if (Ball == nullptr && Application::IsKeyPressed(VK_SPACE))
	{
		Ball = FetchGO();
		Ball->type = PhysicsObject::GO_BALL;
		Ball->pos = Vector3(m_worldWidth * 0.5f, m_worldHeight * 0.5f, 0);
		Ball->vel.SetZero();;
		Ball->scale.Set(2, 2, 1);
		endGame = false;
	}*/

	for (int i = 0; i < (int)m_goList->size(); ++i)
	{
		PhysicsObject *go = (*m_goList)[i];
		if (go->active)
		{
			go->Update(dt, m_worldWidth, m_worldHeight);
			if (go == Ball)
			{
				if ((go->pos - Vector3(m_worldWidth * 0.5f, m_worldHeight * 0.5f, 0)).Length() > Maze.getBiggestLength())
				{
					endGame = true;
				}
			}
			for (int k = i + 1; k < (int)m_goList->size(); ++k)
			{
				PhysicsObject* go2 = (*m_goList)[k];
				if (go2->active)
				{
					if (go->type != PhysicsObject::GO_BALL)
					{
						if (go2->type == PhysicsObject::GO_BALL)
						{
							PhysicsObject* temp = go;
							go = go2;
							go2 = temp;
						}
						else
						{
							continue;
						}
					}
					if (CheckCollision(go, go2))
					{
						go2->CollisionResponse(go, dt);
						//CollisionResponse(go, go2, dt);
					}
					go = (*m_goList)[i];
				}
			}
		}
	}
	// End James 13/8/2019
	elapsedTime += dt;
	if (score > 0)
	{
		score -= dt * 100 / 3.f * (1 + (stencilsize - 1) * 0.125f);
	}
	else
	{
		score = 0;
	}
}

void SceneMaze::UpdateGameOver(double dt)
{
	Results::getInstance()->UpdateVars(dt);
	if (!statgained)
	{
		GameEndCalculations();
		StatManager::GetInstance()->SetCharsOriginalValues();
		statgained = true;
	}
	static bool bLButtonState = false;
	if (!bLButtonState && Application::IsMousePressed(0))
	{
		bLButtonState = true;
		std::cout << "LBUTTON DOWN" << std::endl;
		if (Results::getInstance()->ButtonMouseCollision())
		{
			cout << "hit" << endl;
		}
	}
	else if (bLButtonState && !Application::IsMousePressed(0))
	{
		bLButtonState = false;
		std::cout << "LBUTTON UP" << std::endl;
	}
}

void SceneMaze::UpdateMenu(double dt)
{
	for (int i = 0; i < (int)m_menuList.size(); ++i)
	{
		m_menuList[i]->Update(v_mousepos);
		if (m_menuList[i]->changed)
		{
			m_menuList[i]->changed = false;
			switch (m_menuList[i]->type)
			{
			case MenuObject::M_START:
			{
				SceneState = S_GAME; 
				Ball->pos = Vector3(m_worldWidth * 0.5f, m_worldHeight * 0.5f, 0);
				break;
			}
			case MenuObject::M_STENCIL_PLUS:
			{
				if (stencilsize < 5)
				{
					stencilsize++;
				}
				break;
			}
			case MenuObject::M_STENCIL_MINUS:
			{
				if (stencilsize > 1)
				{
					stencilsize--;
				}
				break;
			}
			}
		}
	}
}

// James 13/8/2019
bool SceneMaze::CheckCollision(PhysicsObject* go, PhysicsObject* go2)
{
	switch (go2->type)
	{
	case PhysicsObject::GO_BALL:
	{
		Vector3 dis = go2->pos - go->pos;
		Vector3 u = go->vel - go2->vel;
		if ((dis).Length() <= go->scale.x + go2->scale.x && u.Dot(dis) > 0)
		{
			return true;
		}
		break;
	}
	case PhysicsObject::GO_WALL:
	{
		Vector3 N = go2->normal;
		Vector3 dist = go2->pos - go->pos;
		if (dist.Dot(N) < 0)
		{
			N = -N;
		}
		if (go->vel.Dot(N) < 0)
		{
			return false;
		}
		Vector3 NP(N.y, -N.x);
		if (dist.Dot(N) < (go->scale.x + go2->scale.x * 0.5f) &&
			abs(dist.Dot(NP)) < (go->scale.y + go2->scale.y * 0.5f))
		{
			return true;
		}
		break;
	}
	case PhysicsObject::GO_PILLAR:
	{
		Vector3 dis = go2->pos - go->pos;
		Vector3 u = go->vel - go2->vel;
		if ((dis).Length() <= go->scale.x + go2->scale.x && u.Dot(dis) > 0)
		{
			return true;
		}
		break;
	}
	default:
	{
		return false;
	}
	}
	return false;
}
// End James 13/8/2019

void SceneMaze::Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Calculating aspect ratio
	// James 13/8/2019
	m_worldHeight = 200.f;
	// End James 13/8/2019
	m_worldWidth = m_worldHeight * (float)Application::GetWindowWidth() / Application::GetWindowHeight();

	// Projection matrix : Orthographic Projection
	Mtx44 projection;
	projection.SetToOrtho(0, m_worldWidth, 0, m_worldHeight, -10, 10);
	projectionStack.LoadMatrix(projection);

	// Camera matrix
	viewStack.LoadIdentity();
	viewStack.LookAt(
		camera.position.x, camera.position.y, camera.position.z,
		camera.target.x, camera.target.y, camera.target.z,
		camera.up.x, camera.up.y, camera.up.z
	);
	// Model matrix : an identity matrix (model will be at the origin)
	modelStack.LoadIdentity();

	//RenderMesh(meshList[GEO_AXES], false);

	switch (SceneState)
	{
	case S_MENU:
	{
		RenderMenu();
		break;
	}
	case S_GAME:
	{
		RenderGame();
		break;
	}
	case S_GAMEOVER:
	{
		RenderGameOver(); 
		break;
	}
	}
	if (SceneState != S_GAMEOVER)
	{
		modelStack.PushMatrix();
		modelStack.Translate(v_mousepos);
		modelStack.Scale(10, 10, 1);
		if (mousepressed)
		{
			RenderMesh(meshList[GEO_TANK_CURSOR], false);
		}
		else
		{
			RenderMesh(meshList[GEO_TANK_CURSOR_ALTERNATE], false);
		}
		modelStack.PopMatrix();
	}
}

void SceneMaze::RenderMenu()
{
	ActivateStencil();

	modelStack.PushMatrix();
	modelStack.Translate(Ball->pos);
	modelStack.Scale(100,100,1);
	RenderMesh(meshList[GEO_MAZE_SAMPLE], false);
	modelStack.PopMatrix();

	DeactivateStencil();

	for (int i = 0; i < (int)m_menuList.size(); ++i)
	{
		MenuObject* go = m_menuList[i];
		modelStack.PushMatrix();
		modelStack.Translate(go->pos);
		modelStack.Scale(go->scale);
		switch (go->type)
		{
		case MenuObject::M_START:
		{
			RenderMesh(meshList[GEO_MAZE_START], false);
			break;
		}
		case MenuObject::M_STENCIL_MINUS:
		{
			RenderMesh(meshList[GEO_MAZE_MINUS], false);
			break;
		}
		case MenuObject::M_STENCIL_PLUS:
		{
			RenderMesh(meshList[GEO_MAZE_PLUS], false);
			break;
		}
		default:
		{
			RenderMesh(meshList[GEO_BORDER], false);
			break;
		}
		}
		modelStack.PopMatrix();
	}
	modelStack.PushMatrix();
	modelStack.Translate(Ball->pos);
	modelStack.Scale(Ball->scale);
	RenderMesh(meshList[GEO_BALL], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(m_worldWidth * 0.25f, m_worldHeight * 0.5f, 0);
	modelStack.Scale(160, 160, 1);
	RenderMesh(meshList[GEO_MAZE_INSTRUCTIONS], false);
	modelStack.PopMatrix();
}

void SceneMaze::RenderGame()
{
	// James 15/8/2019

	if (enableStencil)
	{
		ActivateStencil();
	}

	for (std::vector<PhysicsObject *>::iterator it = m_goList->begin(); it != m_goList->end(); ++it)
	{
		PhysicsObject *go = (PhysicsObject *)*it;
		if (go->active)
		{
			RenderGO(go);
		}
	}

	if (enableStencil)
	{
		DeactivateStencil();
	}
	// End James 15/8/2019

	// James 14/8/2019

	//On screen text
	std::ostringstream ss;
	ss.precision(3);
	ss << "T:" << elapsedTime;
	RenderTextOnScreen(meshList[GEO_TEXT], ss.str(), Color(0, 1, 0), 3, 0, 1);

	ss.str("");
	ss << "S:" << score;
	RenderTextOnScreen(meshList[GEO_TEXT], ss.str(), Color(0, 1, 0), 3, 0, 4);
	// End James 14/8/2019
}

void SceneMaze::RenderGameOver()
{
	Results::getInstance()->RenderResults(0, 'A');
}

void SceneMaze::Exit()
{
	SceneBase::Exit();
	//Cleanup PhysicsObjects
	while (m_goList->size() > 0)
	{
		PhysicsObject *go = m_goList->back();
		delete go;
		m_goList->pop_back();
	}
	delete m_goList;
}

void SceneMaze::RenderGO(PhysicsObject * go)
{
	switch (go->type)
	{
		// James 13/8/2019
	case PhysicsObject::GO_BALL:
	{
		modelStack.PushMatrix();
		modelStack.Translate(go->pos);
		modelStack.Scale(go->scale);
		RenderMesh(meshList[GEO_BALL], false);
		modelStack.PopMatrix();
		break;
	}
	case PhysicsObject::GO_WALL:
	{
		modelStack.PushMatrix();
		modelStack.Translate(go->pos);
		modelStack.Rotate(Math::RadianToDegree(atan2(go->normal.y, go->normal.x)), 0, 0, 1);
		modelStack.Scale(go->scale);
		RenderMesh(meshList[GEO_WALL], false);
		modelStack.PopMatrix();
		break;
	}
	case PhysicsObject::GO_TRACE:
	{
		modelStack.PushMatrix();
		modelStack.Translate(go->pos);
		modelStack.Scale(go->scale);
		RenderMesh(meshList[GEO_BALL], false);
		modelStack.PopMatrix();
		break;
	}
	case PhysicsObject::GO_PILLAR:
	{
		modelStack.PushMatrix();
		modelStack.Translate(go->pos);
		modelStack.Scale(go->scale);
		RenderMesh(meshList[GEO_BALL], false);
		modelStack.PopMatrix();
		break;
	}
	// End James 13/8/2019
	default:
		break;
	}
}

PhysicsObject * SceneMaze::FetchGO()
{
	for (int i = 0; i < (int)m_goList->size(); i++)
	{
		if (!(*m_goList)[i]->active)
		{
			(*m_goList)[i]->active = true;
			return (*m_goList)[i];
		}
	}

	for (int i = 0; i < 20; ++i)
	{
		m_goList->push_back(new PhysicsObject(PhysicsObject::GO_NONE));
	}

	(*m_goList)[m_goList->size() - 20]->active = true;
	return (*m_goList)[m_goList->size() - 20];
}

// James 15/8/2019
void SceneMaze::ActivateStencil()
{
	// Enable stencil mode
	glEnable(GL_STENCIL_TEST);
	// Switch on alpha test
	glEnable(GL_ALPHA_TEST);

	// Configure stencil mode
	glStencilFunc(GL_ALWAYS, 1, 0xFF); // Set any stencil to 1
	glAlphaFunc(GL_GREATER, 0x0A);
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
	glStencilMask(0xFF); // Write to stencil buffer
	glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE); // Don't write to colour buffer
	glDepthMask(GL_FALSE); // Don't write to depth buffer
	glClear(GL_STENCIL_BUFFER_BIT); // Clear stencil buffer (0 by default)

	if (Ball != nullptr)
	{
		modelStack.PushMatrix();
		modelStack.Translate(Ball->pos);
		modelStack.Scale((10 + stencilsize * 2) * 2, (10 + stencilsize * 2) * 2, 1);
		RenderMesh(meshList[GEO_BALL], false);
		modelStack.PopMatrix();
	}

	// Switch off stencil function
	glStencilFunc(GL_EQUAL, 1, 0xFF); // Pass test if stencil value is 1
	glAlphaFunc(GL_LEQUAL, 0x0A);
	glStencilMask(0x00); // Don't write anything to stencil buffer
	glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE); // Write to colour buffer
	glDepthMask(GL_TRUE); // Write to depth buffer
}

void SceneMaze::DeactivateStencil()
{
	// Switch off alpha test
	glDisable(GL_ALPHA_TEST);
	// Disable stencil test
	glDisable(GL_STENCIL_TEST);
}
// End James 15/8/2019

void SceneMaze::GameEndCalculations() // Setting the stats and other stuff
{
	if (score >= 6000)
	{
		grade = 'S';
		StatManager::GetInstance()->UpdateChar01F(-20);
		StatManager::GetInstance()->UpdateChar01M(20);
		StatManager::GetInstance()->UpdateChar02F(-20);
		StatManager::GetInstance()->UpdateChar02M(20);
		StatManager::GetInstance()->UpdateChar03F(-20);
		StatManager::GetInstance()->UpdateChar03M(20);
		StatManager::GetInstance()->UpdateChar04F(-20);
		StatManager::GetInstance()->UpdateChar04M(20);
		Results::getInstance()->InitStatsToDist(35);
	}
	else if (score >= 5000 && score < 6000)
	{
		grade = 'A';
		Results::getInstance()->InitStatsToDist(25);

	}
	else if (score >= 4000 && score < 5000)
	{
		grade = 'B';
		Results::getInstance()->InitStatsToDist(20);
	}
	else if (score >= 3000 && score < 4000)
	{
		grade = 'C';
		Results::getInstance()->InitStatsToDist(15);
	}
	else if (score >= 2000 && score < 3000)
	{
		grade = 'D';
		Results::getInstance()->InitStatsToDist(10);
	}
	else
	{
		grade = 'F';
		StatManager::GetInstance()->UpdateChar01F(10);
		StatManager::GetInstance()->UpdateChar01M(-10);
		StatManager::GetInstance()->UpdateChar02F(10);
		StatManager::GetInstance()->UpdateChar02M(-10);
		StatManager::GetInstance()->UpdateChar03F(10);
		StatManager::GetInstance()->UpdateChar03M(-10);
		StatManager::GetInstance()->UpdateChar04F(10);
		StatManager::GetInstance()->UpdateChar04M(-10);
	}

}