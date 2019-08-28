#include "SceneTank.h"
#include "GL\glew.h"
#include "../Application.h"
#include <sstream>
#include "../Rendering/LoadTGA.h"
#include "../Rendering/MeshBuilder.h"

float SceneTank::score = 0;

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

	cout << "Scene Tank" << endl;

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
	meshList[GEO_TANK_RAIN] = MeshBuilder::GenerateQuad("Back", Color(1, 1, 1), 1.f);
	meshList[GEO_TANK_RAIN]->textureID = LoadTGA("Image//Smoke.tga");

	//Physics code here
	m_speed = 1.f;

	m_gravity.Set(0, -9.8f, 0);

	Math::InitRNG();

	m_goList = new std::vector<PhysicsObject*>;

	// James 13/8/2019
	v_mousepos.SetZero();
	Ghost = new PhysicsObject(PhysicsObject::GO_BALL);
	Ghost->setActive(false);
	Ghost->setScale(Vector3(2, 2, 1));

	Ball = nullptr;

	for (int i = 0; i < TraceSize; ++i)
	{
		Trace[i] = new PhysicsObject(PhysicsObject::GO_BALL);
		Trace[i]->setScale(Vector3(1, 1, 1));
	}
	// James 14/8/2019
	tempwall = FetchGO();
	tempwall->setType(PhysicsObject::GO_WALL);
	tempwall->setPos(Vector3(m_worldWidth*0.5f, m_worldHeight * 0.25f, 0));
	tempwall->normal = Vector3(0, 1, 0);
	tempwall->setScale(Vector3(5, m_worldWidth, 1));

	tempwall2 = FetchGO();
	tempwall2->setType(PhysicsObject::GO_WALL);
	tempwall2->setPos(Vector3(m_worldWidth*0.5f, m_worldHeight, 0));
	tempwall2->normal = Vector3(0, 1, 0);
	tempwall2->setScale(Vector3(5, m_worldWidth, 1));

	tempwall3 = FetchGO();
	tempwall3->setType(PhysicsObject::GO_WALL);
	tempwall3->setPos(Vector3(0, m_worldHeight * 0.5f, 0));
	tempwall3->normal = Vector3(1, 0, 0);
	tempwall3->setScale(Vector3(5, m_worldHeight, 1));

	tempwall4 = FetchGO();
	tempwall4->setType(PhysicsObject::GO_WALL);
	tempwall4->setPos(Vector3(m_worldWidth, m_worldHeight * 0.5f, 0));
	tempwall4->normal = Vector3(1, 0, 0);
	tempwall4->setScale(Vector3(5, m_worldHeight, 1));

	// End James 14/8/2019
	// End James 13/8/2019

	// James 15/8/2019
	enableStencil = false;
	// End James 15/8/2019

	// James 16/8/2019

	/*Tank[1] = new TankObject(PhysicsObject::GO_WALL);
	Tank[1]->setPos(Vector3(m_worldWidth* 0.5f, m_worldHeight * 0.75f, 0);
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
			Tank[i]->setPos(Vector3(m_worldWidth* 0.375f, m_worldHeight* 0.71875f, 0));
			break;
		case 1:
			Tank[i]->setPos(Vector3(m_worldWidth* 0.875f, m_worldHeight* 0.71875f, 0));
			break;
		case 2:
			Tank[i]->setPos(Vector3(m_worldWidth* 0.375f, m_worldHeight* 0.53125f, 0));
			break;
		case 3:
			Tank[i]->setPos(Vector3(m_worldWidth* 0.875f, m_worldHeight* 0.53125f, 0));
			break;
		case 4:
			Tank[i]->setPos(Vector3(m_worldWidth* 0.125f, m_worldHeight* 0.8125f, 0));
			break;
		case 5:
			Tank[i]->setPos(Vector3(m_worldWidth* 0.625f, m_worldHeight* 0.8125f, 0));
			break;
		case 6:
			Tank[i]->setPos(Vector3(m_worldWidth* 0.125f, m_worldHeight* 0.4375f, 0));
			break;
		case 7:
			Tank[i]->setPos(Vector3(m_worldWidth* 0.625f, m_worldHeight* 0.4375f, 0));
			break;
		default:
			Tank[i]->setPos(Vector3(m_worldWidth* 0.9f, m_worldHeight* 0.9f, 0));
			break;
		}
		//Tank[i]->setPos(Vector3(Math::RandFloatMinMax(m_worldWidth * 0.1f, m_worldWidth * 0.9f), Math::RandFloatMinMax(m_worldHeight*0.3, m_worldHeight * 0.9), 0);
		Tank[i]->setScale(Vector3(4, 10, 1));
		Tank[i]->normal.Set(0, 1, 0);
		Tank[i]->setActive(true);
		m_goList->push_back(Tank[i]);
		Tank[i]->Init(m_goList);
		if (i % 2  == 0)
		{
			Tank[i]->setIsPlayer(true);
			TankObject::PlayerTankCount++;
		}
		else
		{
			TankObject::EnemyTankCount++;
		}
	}

	Ball = FetchGO();
	Ball->setType(PhysicsObject::GO_BALL);
	Ball->setScale(Vector3(2, 2, 1));
	Ball->setActive(false);

	endGame = true;
	elapsedTime = 0;
	ballthrown = false;
	ballcollisionnum = 0;

	PhysicsObject::WindDirection = Vector3(Math::RandFloatMinMax(-9.8f, 9.8f), Math::RandFloatMinMax(-9.8f, 9.8f), 0);
	PhysicsObject::WindDirection = Math::Clamp(PhysicsObject::WindDirection.Length(), 0.f, 9.8f) * PhysicsObject::WindDirection.Normalized();

	TankChange = false;
	delaytime = 0.0;

	for (int i = 0; i < 7; ++i)
	{
		MenuObject* temp = new MenuObject(MenuObject::M_NONE, Vector3(55, 55, 1));
		temp->setActive(true);
		m_menuList.push_back(temp);
	}
	m_menuList[0]->setPos(Vector3(m_worldWidth * 0.375f, m_worldHeight * 0.75f, 0));
	m_menuList[0]->setType(MenuObject::M_FORMATION_1);

	m_menuList[1]->setPos(Vector3(m_worldWidth * 0.625f, m_worldHeight * 0.75f, 0));
	m_menuList[1]->setType(MenuObject::M_FORMATION_2);

	m_menuList[2]->setPos(Vector3(m_worldWidth * 0.875f, m_worldHeight * 0.75f, 0));
	m_menuList[2]->setType(MenuObject::M_FORMATION_3);

	m_menuList[3]->setPos(Vector3(m_worldWidth * 0.375f, m_worldHeight * 0.25f, 0));
	m_menuList[3]->setType(MenuObject::M_FORMATION_4);

	m_menuList[4]->setPos(Vector3(m_worldWidth * 0.625f, m_worldHeight * 0.25f, 0));
	m_menuList[4]->setType(MenuObject::M_FORMATION_5);

	m_menuList[5]->setPos(Vector3(m_worldWidth * 0.875f, m_worldHeight * 0.25f, 0));
	m_menuList[5]->setType(MenuObject::M_FORMATION_6);

	m_menuList[6]->setPos(Vector3(m_worldWidth* 0.125f, m_worldHeight* 0.25f, 0));
	m_menuList[6]->setType(MenuObject::M_HOW_TO_PLAY);

	back = new MenuObject(MenuObject::M_BACK, Vector3(55, 55, 1));
	back->setActive(true);
	back->setPos(Vector3(m_worldWidth* 0.125f, m_worldHeight* 0.25f, 0));

	SceneState = S_MENU;
	turn = 0;
	velocity = 0;

	statgained = false;
	grade = 'F';
	bounceTime = 0.5f;
	mousepressed = false;

	soundSystem.AddSound("Tank_Shoot", "Sounds//Tank_Shoot.wav");
	soundSystem.AddSound("Tank_Bounce", "Sounds//Tank_Bounce.wav");

	m_particleCount = 0;
	Particlebuffertime = 0.0;
}

void SceneTank::Update(double dt)
{
	bounceTime -= (float)dt;
	//CHEAT CODES BY SEAN
//Transition to maze
	if (Application::IsKeyPressed(VK_NUMPAD1) && bounceTime < 0)
	{
		Application::setScene(1);
		soundSystem.stopAllMusic();
		Reset();
		bounceTime = 0.5f;
	}
	//Transition to Mole
	if (Application::IsKeyPressed(VK_NUMPAD2) && bounceTime < 0)
	{
		Application::setScene(2);
		soundSystem.stopAllMusic();
		Reset();
		bounceTime = 0.5f;
	}
	//Transition to Main Scene
	if (Application::IsKeyPressed(VK_NUMPAD3) && bounceTime < 0)
	{
		Application::setScene(0);
		soundSystem.stopAllMusic();
		Reset();
		bounceTime = 0.5f;
	}
	//Transition to Frog Scene
	if (Application::IsKeyPressed(VK_NUMPAD4) && bounceTime < 0)
	{
		Application::setScene(4);
		soundSystem.stopAllMusic();
		Reset();
		bounceTime = 0.5f;
	}
	//Transition to Sheep Game
	if (Application::IsKeyPressed(VK_NUMPAD5) && bounceTime < 0)
	{
		Application::setScene(5);
		soundSystem.stopAllMusic();
		Reset();
		bounceTime = 0.5f;
	}
	//CHEAT CODES BY SEAN
	SceneBase::Update(dt);
	elapsedTime += dt;
	if (StatManager::GetInstance()->GetBool_Game(3))
	{
		Reset();
		StatManager::GetInstance()->SetBool_Tank(false);
	}
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
	if (StatManager::GetInstance()->GetBool_Game(3))
	{
		Reset();
		StatManager::GetInstance()->SetBool_Tank(false);
	}
	if (turn == 16 || TankObject::PlayerTankCount == 0 || TankObject::EnemyTankCount == 0)
	{
		SceneState = S_GAMEOVER;
	}

	UpdateParticle(dt);

	// James 14/8/2019
	tempwall->setPos(Vector3(m_worldWidth*0.5f,m_worldHeight * 0.25f, 0));
	tempwall->setScale(Vector3(5, m_worldWidth, 1));

	tempwall2->setPos(Vector3(m_worldWidth*0.5f, m_worldHeight, 0));
	tempwall2->setScale(Vector3(5, m_worldWidth, 1));

	tempwall3->setPos(Vector3(0, m_worldHeight * 0.5f, 0));
	tempwall3->setScale(Vector3(5, m_worldHeight, 1));

	tempwall4->setPos(Vector3(m_worldWidth, m_worldHeight * 0.5f, 0));
	tempwall4->setScale(Vector3(5, m_worldHeight, 1));

	// End James 14/8/2019
	// James 13/8/2019
	if (Ghost->getActive())
	{
		Ghost->vel = Ghost->getPos() - v_mousepos;
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
	if (!bLButtonState && Application::IsMousePressed(0) && !ballthrown && TankObject::currentTank->getIsPlayer())
	{
		bLButtonState = true;
		std::cout << "LBUTTON DOWN" << std::endl;
		// James 13/8/2019
		Ghost->setActive(true);
		Ghost->setPos(TankObject::currentTank->getHead()->getPos());
		OldPos = v_mousepos;
		// End James 13/8/2019
	}
	else if (bLButtonState && !Application::IsMousePressed(0) && !ballthrown && TankObject::currentTank->getIsPlayer())
	{
		bLButtonState = false;
		std::cout << "LBUTTON UP" << std::endl;

		if ((OldPos - v_mousepos).y > 0)
		{
			// James 13/8/2019
			Ball->setActive(true);
			Ball->setPos(Ghost->getPos());
			Ball->vel = OldPos - v_mousepos;
			Ball->vel = Math::Clamp(Ball->vel.Length(), 0.f, 50.f) * Ball->vel.Normalized();
			Ball->setScale(Vector3(2, 2, 1));
			TankObject::currentTank->setBall(Ball);
			ballthrown = true;
			TankChange = true;
			ballcollisionnum = 0;
			soundSystem.PlayASound("Tank_Shoot");
			// End James 13/8/2019
			// James 15/8/2019
			//	Ball = temp;
			// End James 15/8/2019
		}
		Ghost->setActive(false);
	}
	if (!Ball->getActive())
	{
		ballthrown = false;
		if (TankObject::PlayerTankCount > 0 && TankChange)
		{
			++turn;
			TankObject::currentTank->setBall(nullptr);
			bool done = false;
			while (!done)
			{
				// James 16/8/2019
				TankObject::TankIndex = ++TankObject::TankIndex % TankObject::MaxTank;
				TankObject::previousTank = TankObject::currentTank;
				TankObject::currentTank = Tank[TankObject::TankIndex];
				// End James 16/8/2019
				if (TankObject::currentTank->getActive())
				{
					done = true;
					TankObject::currentTank->setFuel(100);
					TankChange = false;
					velocity = 0.f;
				}
			}
			PhysicsObject::WindDirection = Vector3(Math::RandFloatMinMax(-9.8f, 9.8f), Math::RandFloatMinMax(-9.8f, 9.8f), 0);
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

	UpdateRayTracing(dt);

	for (int i = 0; i < TankObject::MaxTank; ++i)
	{
		if (TankObject::currentTank != Tank[i])
		{
			CheckCollisionTank(TankObject::currentTank, Tank[i]);
		}
		if (Tank[i]->getActive() && !Tank[i]->getIsPlayer() && TankObject::currentTank == Tank[i] && !ballthrown)
		{
			UpdateAI(Tank[i], dt);
		}
	}

	for (int i = 0; i < (int)m_goList->size(); ++i)
	{
		PhysicsObject *go = (*m_goList)[i];
		if (go->getActive())
		{
			if (!((Ghost->getActive() || ballthrown) && go == TankObject::currentTank))
			{
				go->Update(dt, m_worldWidth, m_worldHeight);
				Constrain(go);
			}
			for (int k = i + 1; k < (int)m_goList->size(); ++k)
			{
				PhysicsObject* go2 = (*m_goList)[k];
				if (go2->getActive())
				{
					if (go->getType() != PhysicsObject::GO_BALL)
					{
						if (go2->getType() == PhysicsObject::GO_BALL)
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
							soundSystem.PlayASound("Tank_Bounce");
							if (++ballcollisionnum > 4)
							{
								go->setActive(false);
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
		if (m_menuList[i]->getChanged())
		{
			m_menuList[i]->setChanged(false);
			SceneState = S_GAME;
			musicplay = true;
			if (musicplay == true && musicplayed == false)
			{
				soundSystem.playSheepMusic();
				musicplayed = true;
			}
			StatManager::GetInstance()->SetPrevGame(3);
			switch (m_menuList[i]->getType())
			{
			case MenuObject::M_FORMATION_1:
			{
				for (int k = 0; k < TankObject::MaxTank; k+=2)
				{
					switch (k)
					{
					case 0:
						Tank[k]->setPos(Vector3(m_worldWidth* 0.375f, m_worldHeight* 0.8125f, 0));
						break;
					case 2:
						Tank[k]->setPos(Vector3(m_worldWidth* 0.375f, m_worldHeight* 0.4375f, 0));
						break;
					case 4:
						Tank[k]->setPos(Vector3(m_worldWidth* 0.125f, m_worldHeight* 0.53125f, 0));
						break;
					case 6:
						Tank[k]->setPos(Vector3(m_worldWidth* 0.125f, m_worldHeight* 0.71875f, 0));
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
						Tank[k]->setPos(Vector3(m_worldWidth* 0.375f, m_worldHeight* 0.71875f, 0));
						break;
					case 2:
						Tank[k]->setPos(Vector3(m_worldWidth* 0.375f, m_worldHeight* 0.53125f, 0));
						break;
					case 4:
						Tank[k]->setPos(Vector3(m_worldWidth* 0.125f, m_worldHeight* 0.4375f, 0));
						break;
					case 6:
						Tank[k]->setPos(Vector3(m_worldWidth* 0.125f, m_worldHeight* 0.8125f, 0));
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
						Tank[k]->setPos(Vector3(m_worldWidth* 0.1875f, m_worldHeight* 0.71875f, 0));
						break;
					case 2:
						Tank[k]->setPos(Vector3(m_worldWidth* 0.4375f, m_worldHeight* 0.34375f, 0));
						break;
					case 4:
						Tank[k]->setPos(Vector3(m_worldWidth* 0.3125f, m_worldHeight* 0.53125f, 0));
						break;
					case 6:
						Tank[k]->setPos(Vector3(m_worldWidth* 0.0625f, m_worldHeight* 0.90625f, 0));
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
						Tank[k]->setPos(Vector3(m_worldWidth* 0.4375f, m_worldHeight* 0.625f, 0));
						break;
					case 2:
						Tank[k]->setPos(Vector3(m_worldWidth* 0.0625f, m_worldHeight* 0.625f, 0));
						break;
					case 4:
						Tank[k]->setPos(Vector3(m_worldWidth* 0.25f, m_worldHeight* 0.34375f, 0));
						break;
					case 6:
						Tank[k]->setPos(Vector3(m_worldWidth* 0.25f, m_worldHeight* 0.90625f, 0));
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
						Tank[k]->setPos(Vector3(m_worldWidth* 0.25f, m_worldHeight* 0.90625f, 0));
						break;
					case 2:
						Tank[k]->setPos(Vector3(m_worldWidth* 0.25f, m_worldHeight* 0.34375f, 0));
						break;
					case 4:
						Tank[k]->setPos(Vector3(m_worldWidth* 0.25f, m_worldHeight* 0.53125f, 0));
						break;
					case 6:
						Tank[k]->setPos(Vector3(m_worldWidth* 0.25f, m_worldHeight* 0.71875f, 0));
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
						Tank[k]->setPos(Vector3(m_worldWidth* 0.3125f, m_worldHeight* 0.625f, 0));
						break;
					case 2:
						Tank[k]->setPos(Vector3(m_worldWidth* 0.4375f, m_worldHeight* 0.625f, 0));
						break;
					case 4:
						Tank[k]->setPos(Vector3(m_worldWidth* 0.1875f, m_worldHeight* 0.625f, 0));
						break;
					case 6:
						Tank[k]->setPos(Vector3(m_worldWidth* 0.0625f, m_worldHeight* 0.625f, 0));
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
	if (back->getChanged())
	{
		SceneState = S_MENU;
		back->setChanged(false);
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
				Tank[k]->setPos(Vector3(m_worldWidth* 0.625f, m_worldHeight* 0.71875f, 0));
				break;
			case 3:
				Tank[k]->setPos(Vector3(m_worldWidth* 0.625f, m_worldHeight* 0.53125f, 0));
				break;
			case 5:
				Tank[k]->setPos(Vector3(m_worldWidth* 0.875f, m_worldHeight* 0.8125f, 0));
				break;
			case 7:
				Tank[k]->setPos(Vector3(m_worldWidth* 0.875f, m_worldHeight* 0.4375f, 0));
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
				Tank[k]->setPos(Vector3(m_worldWidth* 0.875f, m_worldHeight* 0.71875f, 0));
				break;
			case 3:
				Tank[k]->setPos(Vector3(m_worldWidth* 0.875f, m_worldHeight* 0.53125f, 0));
				break;
			case 5:
				Tank[k]->setPos(Vector3(m_worldWidth* 0.625f, m_worldHeight* 0.8125f, 0));
				break;
			case 7:
				Tank[k]->setPos(Vector3(m_worldWidth* 0.625f, m_worldHeight* 0.4375f, 0));
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
				Tank[k]->setPos(Vector3(m_worldWidth* 0.5625f, m_worldHeight* 0.90625f, 0));
				break;
			case 3:
				Tank[k]->setPos(Vector3(m_worldWidth* 0.6875f, m_worldHeight* 0.71875f, 0));
				break;
			case 5:
				Tank[k]->setPos(Vector3(m_worldWidth* 0.8125f, m_worldHeight* 0.53125f, 0));
				break;
			case 7:
				Tank[k]->setPos(Vector3(m_worldWidth* 0.9375f, m_worldHeight* 0.34375f, 0));
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
				Tank[k]->setPos(Vector3(m_worldWidth* 0.9375f, m_worldHeight* 0.625f, 0));
				break;
			case 3:
				Tank[k]->setPos(Vector3(m_worldWidth* 0.5625f, m_worldHeight* 0.625f, 0));
				break;
			case 5:
				Tank[k]->setPos(Vector3(m_worldWidth* 0.525f, m_worldHeight* 0.34375f, 0));
				break;
			case 7:
				Tank[k]->setPos(Vector3(m_worldWidth* 0.525f, m_worldHeight* 0.90625f, 0));
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
				Tank[k]->setPos(Vector3(m_worldWidth* 0.75f, m_worldHeight* 0.90625f, 0));
				break;
			case 3:
				Tank[k]->setPos(Vector3(m_worldWidth* 0.75f, m_worldHeight* 0.34375f, 0));
				break;
			case 5:
				Tank[k]->setPos(Vector3(m_worldWidth* 0.75f, m_worldHeight* 0.53125f, 0));
				break;
			case 7:
				Tank[k]->setPos(Vector3(m_worldWidth* 0.75f, m_worldHeight* 0.71875f, 0));
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
				Tank[k]->setPos(Vector3(m_worldWidth* 0.5625f, m_worldHeight* 0.625f, 0));
				break;
			case 3:
				Tank[k]->setPos(Vector3(m_worldWidth* 0.6875f, m_worldHeight* 0.625f, 0));
				break;
			case 5:
				Tank[k]->setPos(Vector3(m_worldWidth* 0.8125f, m_worldHeight* 0.625f, 0));
				break;
			case 7:
				Tank[k]->setPos(Vector3(m_worldWidth* 0.9375f, m_worldHeight* 0.625f, 0));
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
		Trace[i]->setActive(false);
	}
	if (Ghost->getActive() && !(OldPos - v_mousepos).IsZero())
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
		temp.setType(PhysicsObject::GO_TRACE);
		TankObject::currentTank->setBall(&temp);
		float time = 0.f;
		int index = 0;
		float accumulatedtime = 0.f;
		//Vector3 prevpos = Ghost->pos + m_gravity * dt;
		for (float time = 0; time < 5.f; time += (float)dt)
		{
			if (!temp.getActive())
			{
				break;
			}
			temp.vel += Vector3(0, -9.8f, 0) * (float)dt;
			temp.setPos(temp.vel * (float)dt, true);
			accumulatedtime += temp.vel.Length() * (float)dt;
			for (int k = 0; k < (int)m_goList->size(); ++k)
			{
				PhysicsObject* go2 = (*m_goList)[k];
				if (go2->getActive())
				{
					if (CheckCollision(&temp, go2))
					{
						go2->CollisionResponse(&temp, (float)dt);
						break;
						//CollisionResponse(&temp, go2, dt);
					}
				}
			}
			if (accumulatedtime > 10 && index < TraceSize)
			{
				accumulatedtime = 0.f;
				Trace[index]->setActive(true);
				Trace[index]->setPos(temp.getPos());
				index++;
			}
		}
	}
	else
	{
		for (int i = 0; i < TraceSize; ++i)
		{
			Trace[i]->setActive(false);
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
		if (Tank[i]->getActive() && Tank[i]->getIsPlayer())
		{
			if (!found)
			{
				straightLine = Tank[i]->getHead()->getPos() - com->getHead()->getPos();
				found = true;
			}
			else if (Math::RandIntMinMax(0, 10) > 5)
			{
				straightLine = Tank[i]->getHead()->getPos() - com->getHead()->getPos();
			}
		}
	}
	if (!found)
	{
		cout << "Random Ball" << endl;
		Ball->setActive(true);
		Ball->setPos(com->getHead()->getPos());
		Ball->vel.x = cosf(Math::RandFloatMinMax(0.f, Math::PI));
		Ball->vel.y = sinf(Math::RandFloatMinMax(0.f, Math::PI));
		Ball->vel = Ball->vel * Math::RandFloatMinMax(1, 50);
		Ball->setScale(Vector3(2, 2, 1));
		TankObject::currentTank->setBall(Ball);
		ballthrown = true;
		TankChange = true;
		ballcollisionnum = 0;
		soundSystem.PlayASound("Tank_Shoot");
	}
	else
	{
		Ball->setActive(true);
		Ball->setPos(com->getHead()->getPos());
		float angle = atan2(straightLine.y, straightLine.x);
		Vector3 direction = Vector3(cosf(angle + Math::DegreeToRadian(Math::RandFloatMinMax(-5, 5))), sinf(angle + Math::DegreeToRadian(Math::RandFloatMinMax(-5, 5))), 0);
		Ball->vel = Math::Clamp(straightLine.Length(), 1.f, 50.f) * direction;
		Ball->setScale(Vector3(2, 2, 1));
		TankObject::currentTank->setBall(Ball);
		ballthrown = true;
		TankChange = true;
		ballcollisionnum = 0;
		soundSystem.PlayASound("Tank_Shoot");
	}
}

void SceneTank::UpdateParticle(double dt)
{
	if (m_particleCount < 100 && Particlebuffertime > 0.1)
	{
		Particlebuffertime = 0.0;
		Particles* go = GetParticle();
		go->type = ParticleObject_TYPE::P_RAIN;
		go->pos = Vector3(Math::RandFloatMinMax(0, m_worldWidth), Math::RandFloatMinMax(m_worldHeight * 0.95f, m_worldHeight * 0.98f), 0);
		go->scale.Set(3, 3, 1);
		go->vel.SetZero();
		go->lifeTime = 10.0;
	}
	else
	{
		Particlebuffertime += (float)dt;
	}
	for (int i = 0; i < (int)m_ParticleList.size(); ++i)
	{
		Particles* go = m_ParticleList[i];
		if (go->active)
		{
			Vector3 m_gravity(0, -9.8f, 0);
			go->vel += m_gravity * (float)dt;
			go->vel += TankObject::WindDirection * (float)dt;
			go->pos += go->vel * (float)dt;
			go->lifeTime -= (float)dt;
			if (go->lifeTime < 0 ||
				go->pos.x > m_worldWidth ||
				go->pos.x < 0 ||
				go->pos.y > m_worldHeight ||
				go->pos.y < m_worldHeight * 0.4f)
			{
				go->active = false;
				m_particleCount--;
			}
		}
	}
}

bool SceneTank::Constrain(PhysicsObject* go)
{
	if (go->getPos().y < go->getScale().x /2 + tempwall->getScale().x / 2 + tempwall->getPos().y)
	{
		go->DownBound = true;
	}
	else
	{
		go->DownBound = false;
	}
	if (go->getPos().y > tempwall2->getPos().y - (go->getScale().x + tempwall2->getScale().x / 2))
	{
		go->UpBound = true;
	}
	else
	{
		go->UpBound = false;
	}
	if (go->getPos().x < go->getScale().x + tempwall3->getScale().x / 2 + tempwall3->getPos().x)
	{
		go->LeftBound = true;
	}
	else
	{
		go->LeftBound = false;
	}
	if (go->getPos().x > tempwall4->getPos().x - (go->getScale().x + tempwall4->getScale().x / 2))
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
	if (go2 == TankObject::currentTank->getHead())
	{
		return false;
	}
	switch (go2->getType())
	{
	case PhysicsObject::GO_BALL:
	{
		Vector3 dis = go2->getPos() - go->getPos();
		Vector3 u = go->vel - go2->vel;
		if ((dis).Length() <= go->getScale().x + go2->getScale().x && u.Dot(dis) > 0)
		{
			return true;
		}
		break;
	}
	case PhysicsObject::GO_WALL:
	{
		Vector3 N = go2->normal;
		Vector3 dist = go2->getPos() - go->getPos();
		if (dist.Dot(N) < 0)
		{
			N = -N;
		}
		if (go->vel.Dot(N) < 0)
		{
			return false;
		}
		Vector3 NP(N.y, -N.x);
		if (dist.Dot(N) < (go->getScale().x + go2->getScale().x * 0.5f) &&
			abs(dist.Dot(NP)) < (go->getScale().y + go2->getScale().y * 0.5f))
		{
			return true;
		}
		break;
	}
	case PhysicsObject::GO_PILLAR:
	{
		Vector3 dis = go2->getPos() - go->getPos();
		Vector3 u = go->vel - go2->vel;
		if ((dis).Length() <= go->getScale().x + go2->getScale().x && u.Dot(dis) > 0)
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
	switch (go2->getType())
	{
	case PhysicsObject::GO_BALL:
	{
		float time;
		Vector3 vMu = go->vel - go2->vel;
		Vector3 pMu = go->getPos() - go2->getPos();
		float radius = go->getScale().x + go2->getScale().x;
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
		if (abs((go2->getPos() - go->getPos()).Dot(go2->normal)) < 0)
		{
			go2->normal *= -1.f;
		}
		if (go->vel.Dot(go2->normal) < 0)
		{
			return -1;
		}
		Vector3 w0 = go2->getPos() - (go->getScale().x + go2->getScale().x * 0.5f)*go2->normal;
		float time = abs((go->getPos() - w0).Dot(go2->normal)) / go->vel.Dot(go2->normal);
		Vector3 w1 = w0 + go2->getScale().y * 0.5f * go2->normal.Cross(Vector3(0, 0, 1));
		Vector3 w2 = w0 - go2->getScale().y * 0.5f * go2->normal.Cross(Vector3(0, 0, 1));
		Vector3 bh = go->getPos() + time * go2->normal;
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
	float radius1 = go->getRadius();
	float radius2 = go2->getRadius();
	if ((go->getPos() - go2->getPos()).Length() < radius1 + radius2)
	{
		cout << "Collide" << endl;
		Constrain(go);
		if (go->UpBound || go->DownBound || go->LeftBound || go->RightBound)
		{
			if (go->UpBound || go->DownBound)
			{
				go->setPos(Vector3(radius1 + radius2 - (go->getPos() - go2->getPos()).Length() * 1.01f * (go->getPos() - go2->getPos()).Normalized().x, 0,0) , true);
			}
			if (go->LeftBound || go->RightBound)
			{
				go->setPos(Vector3(0, radius1 + radius2 - (go->getPos() - go2->getPos()).Length() * 1.01f * (go->getPos() - go2->getPos()).Normalized().y, 0), true);
			}
		}
		else
		{
			go->setPos((radius1 + radius2 - (go->getPos() - go2->getPos()).Length()) * 1.01f * (go->getPos() - go2->getPos()).Normalized(), true);
		}
		/*if (go->LeftBound || go->RightBound)
		{
		}
		else
		{
			go->pos += (radius1 + radius2 - (go->pos - go2->pos).Length()) * 1.01 * (go->pos - go2->pos).Normalized();
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

	RenderParticle();

	if (Ghost->getActive())
	{
		modelStack.PushMatrix();
		modelStack.Translate(Ghost->getPos());
		modelStack.Scale(Ghost->getScale());
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
		if (go->getActive())
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
		if (Trace[i]->getActive())
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
	for (int i = 0; i < TankObject::currentTank->getFuel(); i += 10)
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
	ss.precision(4);
	ss << "Score:" << score;
	RenderTextOnScreen(meshList[GEO_TEXT], ss.str(), Color(0, 0, 1), 3, 1, 7);
	// End James 14/8/2019
}

void SceneTank::RenderParticle()
{
	for (int i = 0; i < (int)m_ParticleList.size(); ++i)
	{
		Particles* go = m_ParticleList[i];
		if (go->active)
		{
			modelStack.PushMatrix();
			modelStack.Translate(go->pos);
			modelStack.Rotate(Math::RadianToDegree(atan2(go->vel.y, go->vel.x)), 0, 0, 1);
			modelStack.Scale(go->scale);
			RenderMesh(meshList[GEO_TANK_RAIN], false);
			modelStack.PopMatrix();
		}
	}
}

void SceneTank::RenderMenu()
{
	for (int i = 0; i < (int)m_menuList.size(); ++i)
	{
		MenuObject* go = m_menuList[i];
		modelStack.PushMatrix();
		modelStack.Translate(go->getPos());
		modelStack.Scale(go->getScale());
		switch (go->getType())
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
	modelStack.Translate(back->getPos());
	modelStack.Scale(back->getScale());
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
			for (int k = 0; k < Tank[i]->getHealth(); ++k)
			{
				ss << "@";
			}
			RenderTextOnScreen(meshList[GEO_TEXT], ss.str(), Color(1, 0, 0), 1, go->getPos().x / m_worldWidth * 80 - 0.75f, (go->getPos().y + (go->getScale().x + Tank[i]->getHead()->getScale().x) * 1.5f) / m_worldHeight * 60);
			break;
		}
	}
	switch (go->getType())
	{
		// James 13/8/2019
	case PhysicsObject::GO_BALL:
	{
		modelStack.PushMatrix();
		modelStack.Translate(go->getPos());
		modelStack.Scale(go->getScale());
		if (go == Ball)
		{
			modelStack.Rotate((float)elapsedTime * 90.f, 0, 0, 1);
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
		modelStack.Translate(go->getPos());
		modelStack.Rotate(Math::RadianToDegree(atan2(go->normal.y, go->normal.x)), 0, 0, 1);
		modelStack.Scale(go->getScale());
		RenderMesh(meshList[GEO_WALL], false);
		modelStack.PopMatrix();
		break;
	}
	case PhysicsObject::GO_TRACE:
	{
		modelStack.PushMatrix();
		modelStack.Translate(go->getPos());
		modelStack.Scale(go->getScale());
		RenderMesh(meshList[GEO_BALL], false);
		modelStack.PopMatrix();
		break;
	}
	case PhysicsObject::GO_PILLAR:
	{
		modelStack.PushMatrix();
		modelStack.Translate(go->getPos());
		modelStack.Scale(go->getScale());
		if (go == Tank[0]->getHead())
		{
			RenderMesh(meshList[GEO_TANK_HEAD_1], false);
		}
		else if (go == Tank[2]->getHead())
		{
			RenderMesh(meshList[GEO_TANK_HEAD_2], false);
		}
		else if (go == Tank[4]->getHead())
		{
			RenderMesh(meshList[GEO_TANK_HEAD_3], false);
		}
		else if (go == Tank[6]->getHead())
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
		if (!(*m_goList)[i]->getActive())
		{
			(*m_goList)[i]->setActive(true);
			return (*m_goList)[i];
		}
	}

	for (int i = 0; i < 20; ++i)
	{
		m_goList->push_back(new PhysicsObject(PhysicsObject::GO_NONE));
	}

	(*m_goList)[m_goList->size() - 20]->setActive(true);
	return (*m_goList)[m_goList->size() - 20];
}

Particles* SceneTank::GetParticle()
{
	for (int i = 0; i < (int)m_ParticleList.size(); ++i)
	{
		if (!m_ParticleList[i]->active)
		{
			m_ParticleList[i]->active = true;
			return m_ParticleList[i];
		}
	}

	for (int i = 0; i < 20; ++i)
	{
		m_ParticleList.push_back(new Particles(ParticleObject_TYPE::P_RAIN));
	}

	m_ParticleList[m_ParticleList.size() - 20]->active = true;
	return m_ParticleList[m_ParticleList.size() - 20];
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
		modelStack.Translate(Ball->getPos());
		modelStack.Scale(Ball->getScale() * 15);
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
		soundSystem.stopAllMusic();
		musicplayed = false;
		musicplay = false;
		Tank[i]->setBall(nullptr);
		switch (i)
		{
		case 0:
			Tank[i]->setPos(Vector3(m_worldWidth* 0.375f, m_worldHeight* 0.71875f, 0));
			break;
		case 1:
			Tank[i]->setPos(Vector3(m_worldWidth* 0.875f, m_worldHeight* 0.71875f, 0));
			break;
		case 2:
			Tank[i]->setPos(Vector3(m_worldWidth* 0.375f, m_worldHeight* 0.53125f, 0));
			break;
		case 3:
			Tank[i]->setPos(Vector3(m_worldWidth* 0.875f, m_worldHeight* 0.53125f, 0));
			break;
		case 4:
			Tank[i]->setPos(Vector3(m_worldWidth* 0.125f, m_worldHeight* 0.8125f, 0));
			break;
		case 5:
			Tank[i]->setPos(Vector3(m_worldWidth* 0.625f, m_worldHeight* 0.8125f, 0));
			break;
		case 6:
			Tank[i]->setPos(Vector3(m_worldWidth* 0.125f, m_worldHeight* 0.4375f, 0));
			break;
		case 7:
			Tank[i]->setPos(Vector3(m_worldWidth* 0.625f, m_worldHeight* 0.4375f, 0));
			break;
		default:
			Tank[i]->setPos(Vector3(m_worldWidth* 0.9f, m_worldHeight* 0.9f, 0));
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
