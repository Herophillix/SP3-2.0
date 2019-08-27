#include "SceneTank.h"
#include "GL\glew.h"
#include "../Application.h"
#include <sstream>
#include "../Rendering/LoadTGA.h"
#include "../Rendering/MeshBuilder.h"

int SceneTank::score = 0;

SceneTank::SceneTank()
{
}

SceneTank::~SceneTank()
{
}

void SceneTank::Init()
{
	SceneBase::Init();

	Results::getInstance()->InitVars();

	//Calculating aspect ratio
	// James 13/8/2019
	m_worldHeight = 200.f;
	// End James 13/8/2019
	m_worldWidth = m_worldHeight * (float)Application::GetWindowWidth() / Application::GetWindowHeight();

	musicplayed = false;
	musicplay = false;

	meshList[GEO_ARROW] = MeshBuilder::GenerateQuad("arrow", Color(1, 1, 1), 1.f);
	meshList[GEO_ARROW]->textureID = LoadTGA("Image//Arrow.tga");
	meshList[GEO_TANK_HEAD_1] = MeshBuilder::GenerateQuad("Head 1", Color(1, 1, 1), 2.5f);
	meshList[GEO_TANK_HEAD_1]->textureID = LoadTGA("Image//Tank_Head1.tga");
	meshList[GEO_TANK_HEAD_2] = MeshBuilder::GenerateQuad("Head 2", Color(1, 1, 1), 3.5f);
	meshList[GEO_TANK_HEAD_2]->textureID = LoadTGA("Image//Tank_Head2.tga");
	meshList[GEO_TANK_HEAD_3] = MeshBuilder::GenerateQuad("Head 3", Color(1, 1, 1), 2.5f);
	meshList[GEO_TANK_HEAD_3]->textureID = LoadTGA("Image//Tank_Head3.tga");
	meshList[GEO_TANK_HEAD_4] = MeshBuilder::GenerateQuad("Head 2", Color(1, 1, 1), 2.5f);
	meshList[GEO_TANK_HEAD_4]->textureID = LoadTGA("Image//Tank_Head4.tga");
	meshList[GEO_BORDER] = MeshBuilder::GenerateQuad("Border", Color(1, 1, 1), 3.5f);
	meshList[GEO_BORDER]->textureID = LoadTGA("Image//Border.tga");
	meshList[GEO_TANK_FORMATION_1] = MeshBuilder::GenerateQuad("Formation 1", Color(1, 1, 1), 1.f);
	meshList[GEO_TANK_FORMATION_1]->textureID = LoadTGA("Image//Tank_Formation_1.tga");
	meshList[GEO_TANK_FORMATION_2] = MeshBuilder::GenerateQuad("Formation 2", Color(1, 1, 1), 1.f);
	meshList[GEO_TANK_FORMATION_2]->textureID = LoadTGA("Image//Tank_Formation_2.tga");
	meshList[GEO_TANK_FORMATION_3] = MeshBuilder::GenerateQuad("Formation 3", Color(1, 1, 1), 1.f);
	meshList[GEO_TANK_FORMATION_3]->textureID = LoadTGA("Image//Tank_Formation_3.tga");
	meshList[GEO_TANK_FORMATION_4] = MeshBuilder::GenerateQuad("Formation 4", Color(1, 1, 1), 1.f);
	meshList[GEO_TANK_FORMATION_4]->textureID = LoadTGA("Image//Tank_Formation_4.tga");
	meshList[GEO_TANK_FORMATION_5] = MeshBuilder::GenerateQuad("Formation 5", Color(1, 1, 1), 1.f);
	meshList[GEO_TANK_FORMATION_5]->textureID = LoadTGA("Image//Tank_Formation_5.tga");
	meshList[GEO_TANK_FORMATION_6] = MeshBuilder::GenerateQuad("Formation 6", Color(1, 1, 1), 1.f);
	meshList[GEO_TANK_FORMATION_6]->textureID = LoadTGA("Image//Tank_Formation_6.tga");
	meshList[GEO_TANK_CURSOR] = MeshBuilder::GenerateQuad("Cursor", Color(1, 1, 1), 1.f);
	meshList[GEO_TANK_CURSOR]->textureID = LoadTGA("Image//Tank_Cursor.tga");
	meshList[GEO_TANK_CURSOR_ALTERNATE] = MeshBuilder::GenerateQuad("Cursor	Alternate", Color(1, 1, 1), 1.f);
	meshList[GEO_TANK_CURSOR_ALTERNATE]->textureID = LoadTGA("Image//Tank_Cursor_Alternate.tga");
	meshList[GEO_TANK_HOW_TO_PLAY] = MeshBuilder::GenerateQuad("Cursor	Alternate", Color(1, 1, 1), 1.f);
	meshList[GEO_TANK_HOW_TO_PLAY]->textureID = LoadTGA("Image//Tank_How_To_Play.tga");
	meshList[GEO_TANK_SELECT_FORMATION] = MeshBuilder::GenerateQuad("Cursor	Alternate", Color(1, 1, 1), 1.f);
	meshList[GEO_TANK_SELECT_FORMATION]->textureID = LoadTGA("Image//Tank_Select_Formation.tga");
	meshList[GEO_TANK_BALL_1] = MeshBuilder::GenerateQuad("Ball 1", Color(1, 1, 1), 2.f);
	meshList[GEO_TANK_BALL_1]->textureID = LoadTGA("Image//Ball.tga");
	meshList[GEO_TANK_BALL_2] = MeshBuilder::GenerateQuad("Ball 2", Color(1, 1, 1), 2.f);
	meshList[GEO_TANK_BALL_2]->textureID = LoadTGA("Image//Ball_2.tga");
	meshList[GEO_TANK_BALL_3] = MeshBuilder::GenerateQuad("Ball 3", Color(1, 1, 1), 2.f);
	meshList[GEO_TANK_BALL_3]->textureID = LoadTGA("Image//Ball_3.tga");
	meshList[GEO_TANK_BALL_4] = MeshBuilder::GenerateQuad("Ball 4", Color(1, 1, 1), 2.f);
	meshList[GEO_TANK_BALL_4]->textureID = LoadTGA("Image//Ball_4.tga");
	meshList[GEO_TANK_BALL_5] = MeshBuilder::GenerateQuad("Ball 5", Color(1, 1, 1), 2.f);
	meshList[GEO_TANK_BALL_5]->textureID = LoadTGA("Image//Ball_5.tga");
	meshList[GEO_TANK_INSTRUCTIONS] = MeshBuilder::GenerateQuad("Instructions", Color(1, 1, 1), 1.f);
	meshList[GEO_TANK_INSTRUCTIONS]->textureID = LoadTGA("Image//Tank_Instructions.tga");
	meshList[GEO_TANK_BACK] = MeshBuilder::GenerateQuad("Back", Color(1, 1, 1), 1.f);
	meshList[GEO_TANK_BACK]->textureID = LoadTGA("Image//Tank_Back.tga");

	//Physics code here
	m_speed = 1.f;

	m_gravity.Set(0, -9.8f, 0);

	Math::InitRNG();

	m_goList = new std::vector<PhysicsObject*>;

	// James 13/8/2019
	v_mousepos.SetZero();
	Ghost = new PhysicsObject(PhysicsObject::GO_BALL);
	Ghost->active = false;
	Ghost->pos.SetZero();
	Ghost->scale.Set(2, 2, 1);

	Ball = nullptr;

	for (int i = 0; i < TraceSize; ++i)
	{
		Trace[i] = new PhysicsObject(PhysicsObject::GO_BALL);
		Trace[i]->scale.Set(1, 1, 1);
	}
	// James 14/8/2019
	tempwall = FetchGO();
	tempwall->type = PhysicsObject::GO_WALL;
	tempwall->pos = Vector3(m_worldWidth*0.5, m_worldHeight * 0.25f, 0);
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

	// End James 14/8/2019
	// End James 13/8/2019

	// James 15/8/2019
	enableStencil = false;
	// End James 15/8/2019

	// James 16/8/2019

	/*Tank[1] = new TankObject(PhysicsObject::GO_WALL);
	Tank[1]->pos.Set(m_worldWidth* 0.5f, m_worldHeight * 0.75f, 0);
	Tank[1]->scale.Set(4, 10, 1);
	Tank[1]->normal.Set(0, 1, 0);
	Tank[1]->active = true;
	m_goList->push_back(Tank[1]);
	Tank[1]->Init(m_goList);*/

	for (int i = 0; i < TankObject::MaxTank; ++i)
	{
		Tank[i] = new TankObject(PhysicsObject::GO_WALL);
		switch (i)
		{
		case 0:
			Tank[i]->pos.Set(m_worldWidth* 0.375f, m_worldHeight* 0.71875f, 0);
			break;
		case 1:
			Tank[i]->pos.Set(m_worldWidth* 0.875f, m_worldHeight* 0.71875f, 0);
			break;
		case 2:
			Tank[i]->pos.Set(m_worldWidth* 0.375f, m_worldHeight* 0.53125f, 0);
			break;
		case 3:
			Tank[i]->pos.Set(m_worldWidth* 0.875f, m_worldHeight* 0.53125f, 0);
			break;
		case 4:
			Tank[i]->pos.Set(m_worldWidth* 0.125f, m_worldHeight* 0.8125f, 0);
			break;
		case 5:
			Tank[i]->pos.Set(m_worldWidth* 0.625f, m_worldHeight* 0.8125f, 0);
			break;
		case 6:
			Tank[i]->pos.Set(m_worldWidth* 0.125f, m_worldHeight* 0.4375f, 0);
			break;
		case 7:
			Tank[i]->pos.Set(m_worldWidth* 0.625f, m_worldHeight* 0.4375f, 0);
			break;
		default:
			Tank[i]->pos.Set(m_worldWidth* 0.9f, m_worldHeight* 0.9f, 0);
			break;
		}
		//Tank[i]->pos.Set(Math::RandFloatMinMax(m_worldWidth * 0.1f, m_worldWidth * 0.9f), Math::RandFloatMinMax(m_worldHeight*0.3, m_worldHeight * 0.9), 0);
		Tank[i]->scale.Set(4, 10, 1);
		Tank[i]->normal.Set(0, 1, 0);
		Tank[i]->active = true;
		m_goList->push_back(Tank[i]);
		Tank[i]->Init(m_goList);
		if (i % 2  == 0)
		{
			Tank[i]->isPlayer = true;
			TankObject::PlayerTankCount++;
		}
		else
		{
			TankObject::EnemyTankCount++;
		}
	}

	Ball = FetchGO();
	Ball->type = PhysicsObject::GO_BALL;
	Ball->scale.Set(2, 2, 1);
	Ball->active = false;

	endGame = true;
	elapsedTime = 0;
	ballthrown = false;
	ballcollisionnum = 0;

	PhysicsObject::WindDirection = Vector3(Math::RandFloatMinMax(-9.8, 9.8), Math::RandFloatMinMax(-9.8, 9.8), 0);
	PhysicsObject::WindDirection = Math::Clamp(PhysicsObject::WindDirection.Length(), 0.f, 9.8f) * PhysicsObject::WindDirection.Normalized();

	TankChange = false;
	delaytime = 0.0;

	for (int i = 0; i < 7; ++i)
	{
		MenuObject* temp = new MenuObject(MenuObject::M_NONE, Vector3(55, 55, 1));
		temp->active = true;
		m_menuList.push_back(temp);
	}
	m_menuList[0]->pos = Vector3(m_worldWidth * 0.375f, m_worldHeight * 0.75f, 0);
	m_menuList[0]->type = MenuObject::M_FORMATION_1;

	m_menuList[1]->pos = Vector3(m_worldWidth * 0.625f, m_worldHeight * 0.75f, 0);
	m_menuList[1]->type = MenuObject::M_FORMATION_2;

	m_menuList[2]->pos = Vector3(m_worldWidth * 0.875f, m_worldHeight * 0.75f, 0);
	m_menuList[2]->type = MenuObject::M_FORMATION_3;

	m_menuList[3]->pos = Vector3(m_worldWidth * 0.375f, m_worldHeight * 0.25f, 0);
	m_menuList[3]->type = MenuObject::M_FORMATION_4;

	m_menuList[4]->pos = Vector3(m_worldWidth * 0.625f, m_worldHeight * 0.25f, 0);
	m_menuList[4]->type = MenuObject::M_FORMATION_5;

	m_menuList[5]->pos = Vector3(m_worldWidth * 0.875f, m_worldHeight * 0.25f, 0);
	m_menuList[5]->type = MenuObject::M_FORMATION_6;

	m_menuList[6]->pos = Vector3(m_worldWidth* 0.125f, m_worldHeight* 0.25f, 0);
	m_menuList[6]->type = MenuObject::M_HOW_TO_PLAY;

	back = new MenuObject(MenuObject::M_BACK, Vector3(55, 55, 1));
	back->active = true;
	back->pos = Vector3(m_worldWidth* 0.125f, m_worldHeight* 0.25f, 0);

	SceneState = S_MENU;
	turn = 0;
	velocity = 0;

	statgained = false;
	grade = 'F';

	mousepressed = false;

	soundSystem.AddSound("Hit", "Sounds//Hammer_Whack.wav");
}

void SceneTank::Update(double dt)
{
	if (StatManager::GetInstance()->GetBool_Game(3))
	{
		Reset();
		StatManager::GetInstance()->SetBool_Tank(false);
	}
	SceneBase::Update(dt);
	elapsedTime += dt;
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
	static bool bRButtonState = false;
	if (!bRButtonState && Application::IsMousePressed(1))
	{
		bRButtonState = true;
		std::cout << "LBUTTON DOWN" << std::endl;
		mousepressed = true;
	}
	else if (bRButtonState && !Application::IsMousePressed(1))
	{
		bRButtonState = false;
		SceneState = S_GAMEOVER;
	}
	switch (SceneState)
	{
	case S_MENU:
	{
		UpdateMenu(dt);
		break;
	}
	case S_INSTRUCTIONS:
	{
		UpdateInstructions(dt);
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
	default:
	{
		cout << "No Scene State" << endl;
		break;
	}
	}
}

void SceneTank::UpdateGameOver(double dt)
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

void SceneTank::UpdateGame(double dt)
{
	if (turn == 16 || TankObject::PlayerTankCount == 0 || TankObject::EnemyTankCount == 0)
	{
		SceneState = S_GAMEOVER;
	}
	// James 14/8/2019
	tempwall->pos = Vector3(m_worldWidth*0.5, m_worldHeight * 0.25f, 0);
	tempwall->scale.Set(5, m_worldWidth, 1);

	tempwall2->pos = Vector3(m_worldWidth*0.5, m_worldHeight, 0);
	tempwall2->scale.Set(5, m_worldWidth, 1);

	tempwall3->pos = Vector3(0, m_worldHeight * 0.5f, 0);
	tempwall3->scale.Set(5, m_worldHeight, 1);

	tempwall4->pos = Vector3(m_worldWidth, m_worldHeight * 0.5f, 0);
	tempwall4->scale.Set(5, m_worldHeight, 1);

	// End James 14/8/2019
	// James 13/8/2019
	if (Ghost->active)
	{
		Ghost->vel = Ghost->pos - v_mousepos;
	}
	// End James 13/8/2019

	//if (!TankObject::currentTank->active)
	//{
	//	bool done = false;
	//	while (!done)
	//	{
	//		// James 16/8/2019
	//		TankObject::TankIndex = ++TankObject::TankIndex % TankObject::MaxTank;
	//		TankObject::previousTank = TankObject::currentTank;
	//		TankObject::currentTank = Tank[TankObject::TankIndex];
	//		// End James 16/8/2019
	//		if (TankObject::currentTank->active)
	//		{
	//			done = true;
	//			TankObject::currentTank->fuel = 100;
	//		}
	//	}
	//}

	static bool bLButtonState = false;
	if (!bLButtonState && Application::IsMousePressed(0) && !ballthrown && TankObject::currentTank->isPlayer)
	{
		bLButtonState = true;
		std::cout << "LBUTTON DOWN" << std::endl;
		// James 13/8/2019
		Ghost->active = true;
		Ghost->pos = TankObject::currentTank->Head->pos;
		OldPos = v_mousepos;
		// End James 13/8/2019
	}
	else if (bLButtonState && !Application::IsMousePressed(0) && !ballthrown && TankObject::currentTank->isPlayer)
	{
		bLButtonState = false;
		std::cout << "LBUTTON UP" << std::endl;

		if ((OldPos - v_mousepos).y > 0)
		{
			// James 13/8/2019
			Ball->active = true;
			Ball->pos = Ghost->pos;
			Ball->vel = OldPos - v_mousepos;
			Ball->vel = Math::Clamp(Ball->vel.Length(), 0.f, 50.f) * Ball->vel.Normalized();
			Ball->scale.Set(2, 2, 1);
			TankObject::currentTank->Ball = Ball;
			ballthrown = true;
			TankChange = true;
			ballcollisionnum = 0;
			// End James 13/8/2019
			// James 15/8/2019
			//	Ball = temp;
			// End James 15/8/2019
		}
		Ghost->active = false;
	}
	if (!Ball->active)
	{
		ballthrown = false;
		if (TankObject::PlayerTankCount > 0 && TankChange)
		{
			++turn;
			TankObject::currentTank->Ball = nullptr;
			bool done = false;
			while (!done)
			{
				// James 16/8/2019
				TankObject::TankIndex = ++TankObject::TankIndex % TankObject::MaxTank;
				TankObject::previousTank = TankObject::currentTank;
				TankObject::currentTank = Tank[TankObject::TankIndex];
				// End James 16/8/2019
				if (TankObject::currentTank->active)
				{
					done = true;
					TankObject::currentTank->fuel = 100;
					TankChange = false;
					velocity = 0.f;
				}
			}
			PhysicsObject::WindDirection = Vector3(Math::RandFloatMinMax(-9.8, 9.8), Math::RandFloatMinMax(-9.8, 9.8), 0);
			PhysicsObject::WindDirection = Math::Clamp(PhysicsObject::WindDirection.Length(), 0.f, 9.8f) * PhysicsObject::WindDirection.Normalized();
		}
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

	static bool bFState = false;
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
	}

	UpdateRayTracing(dt);

	for (int i = 0; i < TankObject::MaxTank; ++i)
	{
		if (TankObject::currentTank != Tank[i])
		{
			CheckCollisionTank(TankObject::currentTank, Tank[i]);
		}
		if (Tank[i]->active && !Tank[i]->isPlayer && TankObject::currentTank == Tank[i] && !ballthrown)
		{
			UpdateAI(Tank[i], dt);
		}
	}

	for (int i = 0; i < (int)m_goList->size(); ++i)
	{
		PhysicsObject *go = (*m_goList)[i];
		if (go->active)
		{
			if (!((Ghost->active || ballthrown) && go == TankObject::currentTank))
			{
				go->Update(dt, m_worldWidth, m_worldHeight);
				Constrain(go);
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
						if (go == Ball)
						{
							soundSystem.PlayASound("Hit");
							if (++ballcollisionnum > 4)
							{
								go->active = false;
								ballcollisionnum = 0;
							}
						}
						go2->CollisionResponse(go, dt);
						//CollisionResponse(go, go2, dt);
					}
					go = (*m_goList)[i];
				}
			}
		}
	}
	// End James 13/8/2019

	if (!endGame)
	{
		elapsedTime += dt;
	}
}

void SceneTank::UpdateMenu(double dt)
{
	for (int i = 0; i < (int)m_menuList.size(); ++i)
	{
		m_menuList[i]->Update(v_mousepos);
		if (m_menuList[i]->changed)
		{
			m_menuList[i]->changed = false;
			SceneState = S_GAME;
			musicplay = true;
			if (musicplay == true && musicplayed == false)
			{
				soundSystem.playSheepMusic();
				musicplayed = true;
			}
			StatManager::GetInstance()->SetPrevGame(3);
			switch (m_menuList[i]->type)
			{
			case MenuObject::M_FORMATION_1:
			{
				for (int k = 0; k < TankObject::MaxTank; k+=2)
				{
					switch (k)
					{
					case 0:
						Tank[k]->pos.Set(m_worldWidth* 0.375f, m_worldHeight* 0.8125f, 0);
						break;
					case 2:
						Tank[k]->pos.Set(m_worldWidth* 0.375f, m_worldHeight* 0.4375f, 0);
						break;
					case 4:
						Tank[k]->pos.Set(m_worldWidth* 0.125f, m_worldHeight* 0.53125f, 0);
						break;
					case 6:
						Tank[k]->pos.Set(m_worldWidth* 0.125f, m_worldHeight* 0.71875f, 0);
						break;
					}
				}
				break;
			}
			case MenuObject::M_FORMATION_2:
			{
				for (int k = 0; k < TankObject::MaxTank; k += 2)
				{
					switch (k)
					{
					case 0:
						Tank[k]->pos.Set(m_worldWidth* 0.375f, m_worldHeight* 0.71875f, 0);
						break;
					case 2:
						Tank[k]->pos.Set(m_worldWidth* 0.375f, m_worldHeight* 0.53125f, 0);
						break;
					case 4:
						Tank[k]->pos.Set(m_worldWidth* 0.125f, m_worldHeight* 0.4375f, 0);
						break;
					case 6:
						Tank[k]->pos.Set(m_worldWidth* 0.125f, m_worldHeight* 0.8125f, 0);
						break;
					}
				}
				break;
			}
			case MenuObject::M_FORMATION_3:
			{
				for (int k = 0; k < TankObject::MaxTank; k += 2)
				{
					switch (k)
					{
					case 0:
						Tank[k]->pos.Set(m_worldWidth* 0.1875f, m_worldHeight* 0.71875f, 0);
						break;
					case 2:
						Tank[k]->pos.Set(m_worldWidth* 0.4375f, m_worldHeight* 0.34375f, 0);
						break;
					case 4:
						Tank[k]->pos.Set(m_worldWidth* 0.3125f, m_worldHeight* 0.53125f, 0);
						break;
					case 6:
						Tank[k]->pos.Set(m_worldWidth* 0.0625f, m_worldHeight* 0.90625f, 0);
						break;
					}
				}
				break;
			}
			case MenuObject::M_FORMATION_4:
			{
				for (int k = 0; k < TankObject::MaxTank; k += 2)
				{
					switch (k)
					{
					case 0:
						Tank[k]->pos.Set(m_worldWidth* 0.4375f, m_worldHeight* 0.625f, 0);
						break;
					case 2:
						Tank[k]->pos.Set(m_worldWidth* 0.0625f, m_worldHeight* 0.625f, 0);
						break;
					case 4:
						Tank[k]->pos.Set(m_worldWidth* 0.25f, m_worldHeight* 0.34375f, 0);
						break;
					case 6:
						Tank[k]->pos.Set(m_worldWidth* 0.25f, m_worldHeight* 0.90625f, 0);
						break;
					}
				}
				break;
			}
			case MenuObject::M_FORMATION_5:
			{
				for (int k = 0; k < TankObject::MaxTank; k += 2)
				{
					switch (k)
					{
					case 0:
						Tank[k]->pos.Set(m_worldWidth* 0.25f, m_worldHeight* 0.90625f, 0);
						break;
					case 2:
						Tank[k]->pos.Set(m_worldWidth* 0.25f, m_worldHeight* 0.34375f, 0);
						break;
					case 4:
						Tank[k]->pos.Set(m_worldWidth* 0.25f, m_worldHeight* 0.53125f, 0);
						break;
					case 6:
						Tank[k]->pos.Set(m_worldWidth* 0.25f, m_worldHeight* 0.71875f, 0);
						break;
					}
				}
				break;
			}
			case MenuObject::M_FORMATION_6:
			{
				for (int k = 0; k < TankObject::MaxTank; k += 2)
				{
					switch (k)
					{
					case 0:
						Tank[k]->pos.Set(m_worldWidth* 0.3125f, m_worldHeight* 0.625f, 0);
						break;
					case 2:
						Tank[k]->pos.Set(m_worldWidth* 0.4375f, m_worldHeight* 0.625f, 0);
						break;
					case 4:
						Tank[k]->pos.Set(m_worldWidth* 0.1875f, m_worldHeight* 0.625f, 0);
						break;
					case 6:
						Tank[k]->pos.Set(m_worldWidth* 0.0625f, m_worldHeight* 0.625f, 0);
						break;
					}
				}
				break;
			}
			case MenuObject::M_HOW_TO_PLAY:
			{
				SceneState = S_INSTRUCTIONS;
			}
			}
			ChangeAIPosition();
			for (int i = 0; i < TankObject::MaxTank; ++i)
			{
				TankObject::currentTank = Tank[i];
				Tank[i]->Update(0);
			}
			TankObject::currentTank = Tank[0];
			TankObject::previousTank = Tank[0];
			return;
		}
	}
}

void SceneTank::UpdateInstructions(double dt)
{
	back->Update(v_mousepos);
	if (back->changed)
	{
		SceneState = S_MENU;
		back->changed = false;
	}
}

void SceneTank::ChangeAIPosition()
{
	switch (Math::RandIntMinMax(1, 6))
	{
	case 1:
	{
		for (int k = 1; k < TankObject::MaxTank; k += 2)
		{
			switch (k)
			{
			case 1:
				Tank[k]->pos.Set(m_worldWidth* 0.625f, m_worldHeight* 0.71875f, 0);
				break;
			case 3:
				Tank[k]->pos.Set(m_worldWidth* 0.625f, m_worldHeight* 0.53125f, 0);
				break;
			case 5:
				Tank[k]->pos.Set(m_worldWidth* 0.875f, m_worldHeight* 0.8125f, 0);
				break;
			case 7:
				Tank[k]->pos.Set(m_worldWidth* 0.875f, m_worldHeight* 0.4375f, 0);
				break;
			}
		}
		break;
		break;
	}
	case 2:
	{
		for (int k = 1; k < TankObject::MaxTank; k += 2)
		{
			switch (k)
			{
			case 1:
				Tank[k]->pos.Set(m_worldWidth* 0.875f, m_worldHeight* 0.71875f, 0);
				break;
			case 3:
				Tank[k]->pos.Set(m_worldWidth* 0.875f, m_worldHeight* 0.53125f, 0);
				break;
			case 5:
				Tank[k]->pos.Set(m_worldWidth* 0.625f, m_worldHeight* 0.8125f, 0);
				break;
			case 7:
				Tank[k]->pos.Set(m_worldWidth* 0.625f, m_worldHeight* 0.4375f, 0);
				break;
			}
		}
		break;
	}
	case 3:
	{
		for (int k = 1; k < TankObject::MaxTank; k += 2)
		{
			switch (k)
			{
			case 1:
				Tank[k]->pos.Set(m_worldWidth* 0.5625f, m_worldHeight* 0.90625f, 0);
				break;
			case 3:
				Tank[k]->pos.Set(m_worldWidth* 0.6875f, m_worldHeight* 0.71875f, 0);
				break;
			case 5:
				Tank[k]->pos.Set(m_worldWidth* 0.8125f, m_worldHeight* 0.53125f, 0);
				break;
			case 7:
				Tank[k]->pos.Set(m_worldWidth* 0.9375f, m_worldHeight* 0.34375f, 0);
				break;
			}
		}
		break;
	}
	case 4:
	{
		for (int k = 1; k < TankObject::MaxTank; k += 2)
		{
			switch (k)
			{
			case 1:
				Tank[k]->pos.Set(m_worldWidth* 0.9375f, m_worldHeight* 0.625f, 0);
				break;
			case 3:
				Tank[k]->pos.Set(m_worldWidth* 0.5625f, m_worldHeight* 0.625f, 0);
				break;
			case 5:
				Tank[k]->pos.Set(m_worldWidth* 0.525f, m_worldHeight* 0.34375f, 0);
				break;
			case 7:
				Tank[k]->pos.Set(m_worldWidth* 0.525f, m_worldHeight* 0.90625f, 0);
				break;
			}
		}
		break;
	}
	case 5:
	{
		for (int k = 1; k < TankObject::MaxTank; k += 2)
		{
			switch (k)
			{
			case 1:
				Tank[k]->pos.Set(m_worldWidth* 0.75f, m_worldHeight* 0.90625f, 0);
				break;
			case 3:
				Tank[k]->pos.Set(m_worldWidth* 0.75f, m_worldHeight* 0.34375f, 0);
				break;
			case 5:
				Tank[k]->pos.Set(m_worldWidth* 0.75f, m_worldHeight* 0.53125f, 0);
				break;
			case 7:
				Tank[k]->pos.Set(m_worldWidth* 0.75f, m_worldHeight* 0.71875f, 0);
				break;
			}
		}
		break;
	}
	case 6:
	{
		for (int k = 1; k < TankObject::MaxTank; k += 2)
		{
			switch (k)
			{
			case 1:
				Tank[k]->pos.Set(m_worldWidth* 0.5625f, m_worldHeight* 0.625f, 0);
				break;
			case 3:
				Tank[k]->pos.Set(m_worldWidth* 0.6875f, m_worldHeight* 0.625f, 0);
				break;
			case 5:
				Tank[k]->pos.Set(m_worldWidth* 0.8125f, m_worldHeight* 0.625f, 0);
				break;
			case 7:
				Tank[k]->pos.Set(m_worldWidth* 0.9375f, m_worldHeight* 0.625f, 0);
				break;
			}
		}
		break;
	}
	}
}

void SceneTank::UpdateRayTracing(double dt)
{// James 13/8/2019
	for (int i = 0; i < TraceSize; ++i)
	{
		Trace[i]->active = false;
	}
	if (Ghost->active && !(OldPos - v_mousepos).IsZero())
	{
		PhysicsObject temp;
		temp = *Ghost;
		temp.vel = OldPos - v_mousepos;
		if (temp.vel.y < 0)
		{
			velocity = 0.f;
			return;
		}
		temp.vel = Math::Clamp(temp.vel.Length(), 0.f, 50.f) * temp.vel.Normalized();
		velocity = temp.vel.Length();
		temp.type = PhysicsObject::GO_TRACE;
		TankObject::currentTank->Ball = &temp;
		float time = 0.f;
		int index = 0;
		float accumulatedtime = 0.f;
		//Vector3 prevpos = Ghost->pos + m_gravity * dt;
		for (float time = 0; time < 5.f; time += dt)
		{
			if (!temp.active)
			{
				break;
			}
			temp.vel += Vector3(0, -9.8, 0) * dt;
			temp.pos += temp.vel * dt;
			accumulatedtime += temp.vel.Length() * dt;
			for (int k = 0; k < (int)m_goList->size(); ++k)
			{
				PhysicsObject* go2 = (*m_goList)[k];
				if (go2->active)
				{
					if (CheckCollision(&temp, go2))
					{
						go2->CollisionResponse(&temp, dt);
						break;
						//CollisionResponse(&temp, go2, dt);
					}
				}
			}
			if (accumulatedtime > 10 && index < TraceSize)
			{
				accumulatedtime = 0.f;
				Trace[index]->active = true;
				Trace[index]->pos = temp.pos;
				index++;
			}
		}
		//std::cout << time << std::endl;
		//for (int i = 0; i < TraceSize; ++i)
		//{
		//	Trace[i]->active = true;
		//	//Vector3 AddValue;
		//	/*while (prevpos != Ghost->pos && abs(temppos.Length() - prevpos.Length()) < 2)
		//	{
		//	}*/
		//	//tempvel += m_gravity * dt;
		//	temppos += tempvel.Normalized() * dt * 750;
		//	Trace[i]->pos = temppos;
		//	//prevpos = temppos;
		//}
	}
	else
	{
		for (int i = 0; i < TraceSize; ++i)
		{
			Trace[i]->active = false;
		}
	}
}

void SceneTank::UpdateAI(TankObject* com, double dt)
{
	if (delaytime < 3.0)
	{
		delaytime += dt;
		return;
	}
	delaytime = 0.0;
	bool found = false;
	Vector3 straightLine;
	for (int i = 0; i < TankObject::MaxTank; ++i)
	{
		if (Tank[i]->active && Tank[i]->isPlayer)
		{
			if (!found)
			{
				straightLine = Tank[i]->Head->pos - com->Head->pos;
				found = true;
			}
			else if (Math::RandIntMinMax(0, 10) > 5)
			{
				straightLine = Tank[i]->Head->pos - com->Head->pos;
			}
		}
	}
	if (!found)
	{
		cout << "Random Ball" << endl;
		Ball->active = true;
		Ball->pos = com->Head->pos;
		Ball->vel.x = cosf(Math::RandFloatMinMax(0.f, Math::PI));
		Ball->vel.y = sinf(Math::RandFloatMinMax(0.f, Math::PI));
		Ball->vel = Ball->vel * Math::RandFloatMinMax(1, 50);
		Ball->scale.Set(2, 2, 1);
		TankObject::currentTank->Ball = Ball;
		ballthrown = true;
		TankChange = true;
		ballcollisionnum = 0;
	}
	else
	{
		//float angle = Math::RadianToDegree(atan2(straightLine.y, straightLine.x));
		//if (angle >= 90 && angle <= 270)
		//{
		//	angle = Math::Clamp(angle - 60.f, 100.f, 270.f);
		//}
		//else if (angle < 90)
		//{
		//	angle = Math::Clamp(angle - 60.f, 0.f, 80.f);
		//}
		//else if (angle > 270)
		//{
		//	angle = Math::Clamp(angle + 60.f, 270.f, 360.f);
		//}
		//// s = ut + 0.5at^2
		//// 0.5at^2 + ut - s = 0
		//// ax^2 + bx + c = 0
		//// a = 0.5a 
		//// b = u
		//// c = -s
		//Vector3 c = -(com->Head->pos + straightLine);
		//Vector3 a = 0.5 * m_gravity;
		//Vector3 b;
		//for (int i = 1; i < 50; ++i)
		//{
		//	b = i * angle;
		//	Vector3 time;
		//	Vector3 discriminant = Vector3(b.x * b.x - 4 * a.x * c.x, b.y * b.y - 4 * a.y * c.y, 0);
		//	if (discriminant.x <= 0 || discriminant.y <= 0)
		//	{
		//		continue;
		//	}
		//	time.x = -b.x - sqrt(discriminant.x) * (0.5 * a.x);
		//	if (time.x <= 0)
		//	{
		//		time.x = -b.x + sqrt(discriminant.x) * (0.5 * a.x);
		//		if (time.x <= 0)
		//		{
		//			continue;
		//		}
		//	}
		//	else
		//	{
		//		if (time.x > -b.x + sqrt(discriminant.x) * (0.5 * a.x) && -b.x + sqrt(discriminant.x) * (0.5 * a.x) > 0)
		//		{
		//			time.x = -b.x + sqrt(discriminant.x) * (0.5 * a.x);
		//		}
		//	}
		//	time.y = -b.y - sqrt(discriminant.y) * (0.5 * a.y);
		//	if (time.y <= 0)
		//	{
		//		time.y = -b.y + sqrt(discriminant.y) * (0.5 * a.y);
		//		if (time.y <= 0)
		//		{
		//			continue;
		//		}
		//	}
		//	else
		//	{
		//		if (time.y > -b.y + sqrt(discriminant.y) * (0.5 * a.y) && -b.y + sqrt(discriminant.y) * (0.5 * a.y) > 0)
		//		{
		//			time.y = -b.y + sqrt(discriminant.y) * (0.5 * a.y);
		//		}
		//	}
		//	if (fabs(time.x - time.y) <= Math::EPSILON)
		//	{
		//		Ball->active = true;
		//		Ball->pos =	com->Head->pos;
		//		Ball->vel = b;
		//		Ball->scale.Set(2, 2, 1);
		//		TankObject::currentTank->Ball = Ball;
		//		ballthrown = true;
		//		if (TankObject::TankCount > 0)
		//		{
		//			bool done = false;
		//			while (!done)
		//			{
		//				// James 16/8/2019
		//				TankObject::TankIndex = ++TankObject::TankIndex % TankObject::MaxTank;
		//				TankObject::previousTank = TankObject::currentTank;
		//				TankObject::currentTank = Tank[TankObject::TankIndex];
		//				// End James 16/8/2019
		//				if (TankObject::currentTank->active)
		//				{
		//					done = true;
		//				}
		//			}
		//		}
		//		ballcollisionnum = 0;
		//		return;
		//	}
		//}
		Ball->active = true;
		Ball->pos = com->Head->pos;
		float angle = atan2(straightLine.y, straightLine.x);
		Vector3 direction = Vector3(cosf(angle + Math::DegreeToRadian(Math::RandFloatMinMax(-5, 5))), sinf(angle + Math::DegreeToRadian(Math::RandFloatMinMax(-5, 5))), 0);
		Ball->vel = Math::Clamp(straightLine.Length(), 1.f, 50.f) * direction;
		Ball->scale.Set(2, 2, 1);
		TankObject::currentTank->Ball = Ball;
		ballthrown = true;
		TankChange = true;
		ballcollisionnum = 0;
	}
}

bool SceneTank::Constrain(PhysicsObject* go)
{
	if (go->pos.y < go->scale.x /2 + tempwall->scale.x / 2 + tempwall->pos.y)
	{
		go->DownBound = true;
	}
	else
	{
		go->DownBound = false;
	}
	if (go->pos.y > tempwall2->pos.y - (go->scale.x + tempwall2->scale.x / 2))
	{
		go->UpBound = true;
	}
	else
	{
		go->UpBound = false;
	}
	if (go->pos.x < go->scale.x + tempwall3->scale.x / 2 + tempwall3->pos.x)
	{
		go->LeftBound = true;
	}
	else
	{
		go->LeftBound = false;
	}
	if (go->pos.x > tempwall4->pos.x - (go->scale.x + tempwall4->scale.x / 2))
	{
		go->RightBound = true;
	}
	else
	{
		go->RightBound = false;
	}
	if (go->UpBound || go->DownBound || go->LeftBound || go->RightBound)
	{
		return true;
	}
	else
	{
		return false;
	}
}

// James 13/8/2019
bool SceneTank::CheckCollision(PhysicsObject* go, PhysicsObject* go2)
{
	if (go2 == TankObject::currentTank->Head)
	{
		return false;
	}
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

float SceneTank::CheckCollision2(PhysicsObject* go, PhysicsObject* go2)
{
	switch (go2->type)
	{
	case PhysicsObject::GO_BALL:
	{
		float time;
		Vector3 vMu = go->vel - go2->vel;
		Vector3 pMu = go->pos - go2->pos;
		float radius = go->scale.x + go2->scale.x;
		float a = vMu.LengthSquared();
		float b = 2 * pMu.Dot(vMu);
		float c = pMu.LengthSquared() - radius * radius;
		float discriminant = b * b - 4 * a * c;
		if (discriminant < 0)
		{
			return -1;
		}
		else
		{
			time = (-b + sqrtf(discriminant)) / (2 * a);
			if (time > (-b - sqrtf(discriminant)) / (2 * a) && (-b - sqrtf(discriminant)) / (2 * a) >= 0)
			{
				return (-b - sqrtf(discriminant)) / (2 * a);
			}
			else
			{
				return time;
			}
		}
		break;
	}
	case PhysicsObject::GO_WALL:
	{
		if (abs((go2->pos - go->pos).Dot(go2->normal)) < 0)
		{
			go2->normal *= -1.f;
		}
		if (go->vel.Dot(go2->normal) < 0)
		{
			return -1;
		}
		Vector3 w0 = go2->pos - (go->scale.x + go2->scale.x * 0.5f)*go2->normal;
		float time = abs((go->pos - w0).Dot(go2->normal)) / go->vel.Dot(go2->normal);
		Vector3 w1 = w0 + go2->scale.y * 0.5f * go2->normal.Cross(Vector3(0, 0, 1));
		Vector3 w2 = w0 - go2->scale.y * 0.5f * go2->normal.Cross(Vector3(0, 0, 1));
		Vector3 bh = go->pos + time * go2->normal;
		if ((w1 - bh).Dot(w2 - bh) < 0)
		{
			return time;
		}
		else
		{
			return -1;
		}
		break;
	}
	default:
	{
		break;
	}
	}
	return -1;
}
// End James 13/8/2019

void SceneTank::CheckCollisionTank(TankObject* go, TankObject* go2)
{
	if ((go->pos - go2->pos).Length() < go->radius + go2->radius)
	{
		cout << "Collide" << endl;
		Constrain(go);
		if (go->UpBound || go->DownBound || go->LeftBound || go->RightBound)
		{
			if (go->UpBound || go->DownBound)
			{
				go->pos.x += (go->radius + go2->radius - (go->pos - go2->pos).Length()) * 1.01 * (go->pos - go2->pos).Normalized().x;
			}
			if (go->LeftBound || go->RightBound)
			{
				go->pos.y += (go->radius + go2->radius - (go->pos - go2->pos).Length()) * 1.01 * (go->pos - go2->pos).Normalized().y;
			}
		}
		else
		{
			go->pos += (go->radius + go2->radius - (go->pos - go2->pos).Length()) * 1.01 * (go->pos - go2->pos).Normalized();
		}
		/*if (go->LeftBound || go->RightBound)
		{
		}
		else
		{
			go->pos += (go->radius + go2->radius - (go->pos - go2->pos).Length()) * 1.01 * (go->pos - go2->pos).Normalized();
		}*/
	}
}

void SceneTank::Render()
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
	case S_INSTRUCTIONS:
	{
		RenderInstructions();
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
	default:
	{
		std::ostringstream ss;
		ss << "No Scene State";
		RenderTextOnScreen(meshList[GEO_TEXT], ss.str(), Color(0, 1, 0), 3, 1, 1);
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

void SceneTank::RenderGameOver()
{
	Results::getInstance()->RenderResults(score, grade);
}

void SceneTank::RenderGame()
{
	// James 13/8/2019

	if (Ghost->active)
	{
		modelStack.PushMatrix();
		modelStack.Translate(Ghost->pos);
		modelStack.Scale(Ghost->scale);
		RenderMesh(meshList[GEO_BALL], false);
		modelStack.PopMatrix();
	}

	// End James 13/8/2019

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

	modelStack.PushMatrix();
	modelStack.Translate(m_worldWidth* 0.5f, 0, 0);
	modelStack.Rotate(90, 0, 0, 1);
	modelStack.Scale(5, m_worldWidth, 1);
	RenderMesh(meshList[GEO_WALL], false);
	modelStack.PopMatrix();
	for (int i = 0; i < TraceSize; ++i)
	{
		if (Trace[i]->active)
		{
			RenderGO(Trace[i]);
		}
	}

	if (enableStencil)
	{
		DeactivateStencil();
	}
	// End James 15/8/2019

	// James 14/8/2019

	modelStack.PushMatrix();
	modelStack.Translate(m_worldWidth * 0.6f, m_worldHeight * 0.125f, 0);
	modelStack.Scale(10, 10, 1);
	RenderMesh(meshList[GEO_BORDER], false);
	if (TankObject::currentTank == Tank[0])
	{
		RenderMesh(meshList[GEO_TANK_HEAD_1], false);
	}
	else if (TankObject::currentTank == Tank[2])
	{
		RenderMesh(meshList[GEO_TANK_HEAD_2], false);
	}
	else if (TankObject::currentTank == Tank[4])
	{
		RenderMesh(meshList[GEO_TANK_HEAD_3], false);
	}
	else if (TankObject::currentTank == Tank[6])
	{
		RenderMesh(meshList[GEO_TANK_HEAD_4], false);
	}
	else
	{
		RenderMesh(meshList[GEO_BALL], false);
	}
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(m_worldWidth * 0.8f, m_worldHeight * 0.125f, 0);
	modelStack.PushMatrix();
	modelStack.Rotate(Math::RadianToDegree(atan2(TankObject::WindDirection.y, TankObject::WindDirection.x)) + 90, 0, 0, 1);
	modelStack.Scale(2, 2, 1);
	modelStack.Scale(fabs(TankObject::WindDirection.Length()) * 2, fabs(TankObject::WindDirection.Length()) * 2, 1);
	RenderMesh(meshList[GEO_ARROW], false);
	modelStack.PopMatrix();
	modelStack.Scale(10, 10, 1);
	RenderMesh(meshList[GEO_BORDER], false);
	modelStack.PopMatrix();

	//On screen text
	std::ostringstream ss;
	ss.precision(3);
	ss << "F:";
	for (int i = 0; i < TankObject::currentTank->fuel; i += 10)
	{
		ss << "@";
	}
	RenderTextOnScreen(meshList[GEO_TEXT], ss.str(), Color(0, 1, 0), 3, 1, 1);
	ss.str("");
	ss << "P:";
	for (int i = 0; i < velocity; i+= 10)
	{
		ss << "@";
	}
	RenderTextOnScreen(meshList[GEO_TEXT], ss.str(), Color(1, 1, 0), 3, 1, 4);

	ss.str("");
	ss << "Score:" << score;
	RenderTextOnScreen(meshList[GEO_TEXT], ss.str(), Color(0, 0, 1), 3, 1, 7);
	// End James 14/8/2019
}

void SceneTank::RenderMenu()
{
	for (int i = 0; i < (int)m_menuList.size(); ++i)
	{
		MenuObject* go = m_menuList[i];
		modelStack.PushMatrix();
		modelStack.Translate(go->pos);
		modelStack.Scale(go->scale);
		switch (go->type)
		{
		case MenuObject::M_FORMATION_1:
		{
			RenderMesh(meshList[GEO_TANK_FORMATION_1], false);
			break;
		}
		case MenuObject::M_FORMATION_2:
		{
			RenderMesh(meshList[GEO_TANK_FORMATION_2], false);
			break;
		}
		case MenuObject::M_FORMATION_3:
		{
			RenderMesh(meshList[GEO_TANK_FORMATION_3], false);
			break;
		}
		case MenuObject::M_FORMATION_4:
		{
			RenderMesh(meshList[GEO_TANK_FORMATION_4], false);
			break;
		}
		case MenuObject::M_FORMATION_5:
		{
			RenderMesh(meshList[GEO_TANK_FORMATION_5], false);
			break;
		}
		case MenuObject::M_FORMATION_6:
		{
			RenderMesh(meshList[GEO_TANK_FORMATION_6], false);
			break;
		}
		case MenuObject::M_HOW_TO_PLAY:
		{
			RenderMesh(meshList[GEO_TANK_HOW_TO_PLAY], false);
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
	modelStack.Translate(m_worldWidth*0.125f, m_worldHeight*0.75f,0);
	modelStack.Scale(80,40,1);
	RenderMesh(meshList[GEO_TANK_SELECT_FORMATION], false);
	modelStack.PopMatrix();
}

void SceneTank::RenderInstructions()
{
	modelStack.PushMatrix();
	modelStack.Translate(m_worldWidth * 0.625f, m_worldHeight * 0.5f, 0);
	modelStack.Scale(180, 180, 1);
	RenderMesh(meshList[GEO_TANK_INSTRUCTIONS], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(back->pos);
	modelStack.Scale(back->scale);
	RenderMesh(meshList[GEO_TANK_BACK], false);
	modelStack.PopMatrix();
}

void SceneTank::Exit()
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

void SceneTank::RenderGO(PhysicsObject * go)
{
	for (int i = 0; i < TankObject::MaxTank; ++i)
	{
		if (go == Tank[i])
		{
			std::ostringstream ss;
			for (int k = 0; k < Tank[i]->health; ++k)
			{
				ss << "@";
			}
			RenderTextOnScreen(meshList[GEO_TEXT], ss.str(), Color(1, 0, 0), 1, go->pos.x / m_worldWidth * 80 - 0.75, (go->pos.y + (go->scale.x + Tank[i]->Head->scale.x) * 1.5f) / m_worldHeight * 60);
			break;
		}
	}
	switch (go->type)
	{
		// James 13/8/2019
	case PhysicsObject::GO_BALL:
	{
		modelStack.PushMatrix();
		modelStack.Translate(go->pos);
		modelStack.Scale(go->scale);
		if (go == Ball)
		{
			modelStack.Rotate(elapsedTime * 90, 0, 0, 1);
			RenderMesh(meshList[GEO_TANK_BALL_1 + ballcollisionnum], false);
		}
		else
		{
			RenderMesh(meshList[GEO_BALL], false);
		}
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
		if (go == Tank[0]->Head)
		{
			RenderMesh(meshList[GEO_TANK_HEAD_1], false);
		}
		else if (go == Tank[2]->Head)
		{
			RenderMesh(meshList[GEO_TANK_HEAD_2], false);
		}
		else if (go == Tank[4]->Head)
		{
			RenderMesh(meshList[GEO_TANK_HEAD_3], false);
		}
		else if (go == Tank[6]->Head)
		{
			RenderMesh(meshList[GEO_TANK_HEAD_4], false);
		}
		else
		{
			RenderMesh(meshList[GEO_BALL], false);
		}
		modelStack.PopMatrix();
		break;
	}
	// End James 13/8/2019
	default:
		break;
	}
}

PhysicsObject * SceneTank::FetchGO()
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
void SceneTank::ActivateStencil()
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
		modelStack.Scale(Ball->scale * 15);
		RenderMesh(meshList[GEO_LIGHT], false);
		modelStack.PopMatrix();
	}

	// Switch off stencil function
	glStencilFunc(GL_EQUAL, 1, 0xFF); // Pass test if stencil value is 1
	glAlphaFunc(GL_LEQUAL, 0x0A);
	glStencilMask(0x00); // Don't write anything to stencil buffer
	glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE); // Write to colour buffer
	glDepthMask(GL_TRUE); // Write to depth buffer
}

void SceneTank::DeactivateStencil()
{
	// Switch off alpha test
	glDisable(GL_ALPHA_TEST);
	// Disable stencil test
	glDisable(GL_STENCIL_TEST);
}
// End James 15/8/2019

void SceneTank::Reset()
{
	for (int i = 0; i < TankObject::MaxTank; ++i)
	{
		Tank[i]->ActivateTank();
		Tank[i]->Ball = nullptr;
		soundSystem.stopAllMusic();
		musicplayed = false;
		musicplay = false;
		switch (i)
		{
		case 0:
			Tank[i]->pos.Set(m_worldWidth* 0.375f, m_worldHeight* 0.71875f, 0);
			break;
		case 1:
			Tank[i]->pos.Set(m_worldWidth* 0.875f, m_worldHeight* 0.71875f, 0);
			break;
		case 2:
			Tank[i]->pos.Set(m_worldWidth* 0.375f, m_worldHeight* 0.53125f, 0);
			break;
		case 3:
			Tank[i]->pos.Set(m_worldWidth* 0.875f, m_worldHeight* 0.53125f, 0);
			break;
		case 4:
			Tank[i]->pos.Set(m_worldWidth* 0.125f, m_worldHeight* 0.8125f, 0);
			break;
		case 5:
			Tank[i]->pos.Set(m_worldWidth* 0.625f, m_worldHeight* 0.8125f, 0);
			break;
		case 6:
			Tank[i]->pos.Set(m_worldWidth* 0.125f, m_worldHeight* 0.4375f, 0);
			break;
		case 7:
			Tank[i]->pos.Set(m_worldWidth* 0.625f, m_worldHeight* 0.4375f, 0);
			break;
		default:
			Tank[i]->pos.Set(m_worldWidth* 0.9f, m_worldHeight* 0.9f, 0);
			break;
		}
	}
	TankObject::currentTank = Tank[0];
	TankObject::previousTank = Tank[0];
	score = 0;
	SceneState = S_MENU;
	elapsedTime = 0.0;
	turn = 1;
}

void SceneTank::GameEndCalculations() // Setting the stats and other stuff
{
	score += 500 * (16 - turn);
	if (score >= 6000)
	{
		grade = 'S';
		StatManager::GetInstance()->UpdateChar01F(StatManager::GetInstance()->GetChar01().m_frustration -20);
		StatManager::GetInstance()->UpdateChar01M(StatManager::GetInstance()->GetChar01().m_motivation +20);
		StatManager::GetInstance()->UpdateChar02F(StatManager::GetInstance()->GetChar02().m_frustration -20);
		StatManager::GetInstance()->UpdateChar02M(StatManager::GetInstance()->GetChar02().m_motivation + 20);
		StatManager::GetInstance()->UpdateChar03F(StatManager::GetInstance()->GetChar03().m_frustration -20);
		StatManager::GetInstance()->UpdateChar03M(StatManager::GetInstance()->GetChar03().m_motivation + 20);
		StatManager::GetInstance()->UpdateChar04F(StatManager::GetInstance()->GetChar04().m_frustration -20);
		StatManager::GetInstance()->UpdateChar04M(StatManager::GetInstance()->GetChar04().m_motivation + 20);
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
		StatManager::GetInstance()->UpdateChar01F(StatManager::GetInstance()->GetChar01().m_frustration + 10);
		StatManager::GetInstance()->UpdateChar01M(StatManager::GetInstance()->GetChar01().m_motivation -10);
		StatManager::GetInstance()->UpdateChar02F(StatManager::GetInstance()->GetChar02().m_frustration + 10);
		StatManager::GetInstance()->UpdateChar02M(StatManager::GetInstance()->GetChar02().m_motivation -10);
		StatManager::GetInstance()->UpdateChar03F(StatManager::GetInstance()->GetChar03().m_frustration + 10);
		StatManager::GetInstance()->UpdateChar03M(StatManager::GetInstance()->GetChar03().m_motivation -10);
		StatManager::GetInstance()->UpdateChar04F(StatManager::GetInstance()->GetChar04().m_frustration + 10);
		StatManager::GetInstance()->UpdateChar04M(StatManager::GetInstance()->GetChar04().m_motivation -10);
	}

}