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
	Results::getInstance()->InitVars();

	m_halfWorldHeight = m_worldHeight / 2;
	m_halfWorldWidth = m_worldWidth / 2;
	m_goList = new std::vector<FrogObject*>;


	//Calculating aspect ratio
	m_worldHeight = 200.f;
	m_worldWidth = m_worldHeight * (float)Application::GetWindowWidth() / Application::GetWindowHeight();
	m_halfWorldHeight = m_worldHeight / 2;
	m_halfWorldWidth = m_worldWidth / 2;
	//Physics code here
	m_speed = 1.f;

	Math::InitRNG();
	//  ******************************* PROPS HERE  ******************************* //


	meshList[GEO_FROG_LEFT] = MeshBuilder::GenerateSpriteAnimation("frog", 1, 4);
	meshList[GEO_FROG_LEFT]->textureID = LoadTGA("Image//CharacterSprites//Idle//knight_idle_anim_left.tga");
	meshList[GEO_FROG_RIGHT] = MeshBuilder::GenerateSpriteAnimation("frogRight", 1, 4);
	meshList[GEO_FROG_RIGHT]->textureID = LoadTGA("Image//CharacterSprites//Idle//knight_idle_anim_right.tga");

	meshList[GEO_FROG_MAP] = MeshBuilder::GenerateQuad("map", Color(1, 1, 1), 1.f);
	meshList[GEO_FROG_MAP]->textureID = LoadTGA("Image//Frog_Background.tga");
	meshList[GEO_FROG_BORDER] = MeshBuilder::GenerateQuad("border", Color(0, 1, 1), 1.f);
	//meshList[GEO_FROG_PLATFORM]->textureID = LoadTGA("Image//BGTest.tga");
	meshList[GEO_FROG_ROCK] = MeshBuilder::GenerateQuad("rock", Color(1, 1, 1), 2.f);
	meshList[GEO_FROG_ROCK]->textureID = LoadTGA("Image//Frog_Rock.tga");
	meshList[GEO_COIN] = MeshBuilder::GenerateQuad("coin", Color(1, 1, 1), 2.f);
	meshList[GEO_COIN]->textureID = LoadTGA("Image//Frog_Coin.tga");
	meshList[GEO_FROG_INSTRUCTIONS] = MeshBuilder::GenerateQuad("instructions", Color(1, 1, 1), 1.f);
	meshList[GEO_FROG_INSTRUCTIONS]->textureID = LoadTGA("Image//Frog_instructions.tga");
	meshList[GEO_TEXT] = MeshBuilder::GenerateText("text", 16, 16);
	meshList[GEO_TEXT]->textureID = LoadTGA("Image//KidsZone.tga");

	//meshList[GEO_GAMEFONT] = MeshBuilder::GenerateText("kzone", 16, 16);
	//meshList[GEO_GAMEFONT]->textureID = LoadTGA("Image//KidsZone.tga");

	//  ******************************* SPRITE ANIMATIONS HERE  ******************************* //

	SpriteAnimation *walkLeft = dynamic_cast<SpriteAnimation *>(meshList[GEO_FROG_LEFT]);
	if (walkLeft)
	{
		walkLeft->m_anim = new Animation();
		walkLeft->m_anim->Set(0, 4, 0, 1.f, true);
	}
	SpriteAnimation *walkRight = dynamic_cast<SpriteAnimation *>(meshList[GEO_FROG_RIGHT]);
	if (walkRight)
	{
		walkRight->m_anim = new Animation();
		walkRight->m_anim->Set(0, 4, 0, 1.f, true);
	}


	//  ******************************* PARTICLES HERE  ******************************* //



	Mtx44 projection;
	projection.SetToOrtho(0, m_worldWidth, 0, m_worldHeight, -10, 10);
	projectionStack.LoadMatrix(projection);
	cout << "Scene Frog " << endl;


	m_rockCount = 0;
	m_coinCount = 0;
	m_GameOver = false;
	Frog = FetchGO();
	Frog->setActive(true);
	Frog->setType(FrogObject::GO_FROG);
	Frog->setScale(Vector3(20, 20, 1));
	Frog->Frog_pos.Set(200, 10, 0);
	Frog->Frog_vel.Set(0, 0, 0);
	Frog->Frog_jumpVel.Set(0, 20, 0);
	Frog->setCoin(m_coinCount);

	score = 0;
	m_instructions = true;
	instructionTimer = 600.f;



	hp = Frog->getHP();
	cout << m_worldHeight << " , " << m_worldWidth << endl;
	max_rock = 4;
	max_coin = 10;
	timer = 30.f;
	for (int i = 0; i < 10; i++)
	{
		FrogObject* rock = new FrogObject(FrogObject::GO_ROCK);
		rock_List.push_back(rock);
	}
	for (int i = 0; i < 10; i++)
	{
		FrogObject* coin = new FrogObject(FrogObject::GO_COIN);
		rock_List.push_back(coin);
	}


	m_setOriginValues = false;
	m_setStatsToDist = false;

}

FrogObject* SceneFrog::getRock()
{
	for (std::vector<FrogObject *>::iterator it = rock_List.begin(); it != rock_List.end(); ++it)
	{
		FrogObject *Rock = (FrogObject *)*it;
		if (Rock->getType() == FrogObject::GO_COIN)
		{
			if (!Rock->getActive())
			{
				Rock->setActive(true);
				return Rock;
			}
		}
		else if (Rock->getType() == FrogObject::GO_ROCK)
		{
			if (!Rock->getActive())
			{
				Rock->setActive(true);
				return Rock;
			}
		}
	}
	for (unsigned i = 0; i < 10; ++i)
	{
		FrogObject *rock = new FrogObject(FrogObject::GO_ROCK);
		rock_List.push_back(rock);
	}
	for (unsigned i = 0; i < 10; ++i)
	{
		FrogObject *coin = new FrogObject(FrogObject::GO_COIN);
		rock_List.push_back(coin);
	}
	rock_List[rock_List.size() - 1]->setActive(true);
	return rock_List[rock_List.size() - 1];
}

void SceneFrog::UpdateRock(double dt)
{
	float sc;
	sc = Math::RandFloatMinMax(15, 30) / 2;

	if (m_rockCount < max_rock)
	{
		FrogObject* rock = getRock();
		rock->setType(FrogObject::GO_ROCK);
		m_grav.Set(0, -sc * 2, 0);
		rock->setScale(Vector3(sc, sc, 1));
		rock->setPos(Vector3(Math::RandFloatMinMax((m_worldWidth / 2) - 80,(m_worldWidth / 2) + 80), m_worldHeight, 0));
		m_rockCount++;
	}
	if (m_coinCount < max_coin)
	{
		FrogObject* coin = getRock();
		coin->setType(FrogObject::GO_COIN);
		coin->setScale(Vector3(3, 3, 1));
		coin->setPos(Vector3(Math::RandIntMinMax(13 , 24) * 10 , Math::RandIntMinMax(3, 38) * 5, 0));
		m_coinCount++;
		Frog->plusCoin(Frog);
	}
	for (std::vector<FrogObject *>::iterator it = rock_List.begin(); it != rock_List.end(); ++it)
	{
		FrogObject *rock = (FrogObject *)*it;
		if (rock->getActive())
		{
			if (rock->getType() == FrogObject::GO_ROCK)
			{
				rock->Frog_vel += Vector3(0, m_grav.y, 0)* (float)dt;
				rock->setPos(rock->Frog_vel * (float)dt, true);
			}
			if (rock->getPos().y <= 0)
			{
				rock->Frog_vel.SetZero();
				//rock->setPos(Vector3(0, m_worldHeight, 0));
				rock->setPos(Vector3(Math::RandFloatMinMax((m_worldWidth / 2) - 80, (m_worldWidth / 2) + 80), m_worldHeight, 0));
			}
		}
	}
}

bool SceneFrog::CheckCollision(FrogObject* go, FrogObject* go2)
{
	switch (go2->getType())
	{
	case FrogObject::GO_ROCK:
	{
		Vector3 dis = go2->getPos() - go->Frog_pos;
		Vector3 u = go->Frog_vel - go2->Frog_vel;
		if ((dis).Length() <= go2->getScale().x && u.Dot(dis) > 0)
		{
			return true;
		}
		break;
	}
	case FrogObject::GO_COIN:
	{
		Vector3 dis = go2->getPos() - go->Frog_pos;
		Vector3 u = go->Frog_vel - go2->Frog_vel;
		if ((dis).Length() <= go2->getScale().x)
		{
			return true;
		}
		break;
	}
	case FrogObject::GO_PLATFORM:
	{
		Vector3 N = go2->getNormal();
		Vector3 dist = go2->getPos() - go->getPos();
		if (dist.Dot(N) < 0)
		{
			N = -N;
		}

		Vector3 NP(N.y, -N.x);
		if (dist.Dot(N) < (go->getScale().x + go2->getScale().x * 0.5f) &&
			abs(dist.Dot(NP)) < (go->getScale().y + go2->getScale().y * 0.5f))
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

void SceneFrog::Update(double dt)
{
	//CHEAT CODES BY SEAN
//Transition to maze
	if (Application::IsKeyPressed(VK_NUMPAD1))
	{
		Application::setScene(1);
	}
	//Transition to Mole
	if (Application::IsKeyPressed(VK_NUMPAD2))
	{
		Application::setScene(2);
	}
	//Transition to Tank Scene
	if (Application::IsKeyPressed(VK_NUMPAD3))
	{
		Application::setScene(3);
	}
	//Transition to Main Scene
	if (Application::IsKeyPressed(VK_NUMPAD4))
	{
		Application::setScene(0);
	}
	//Transition to Sheep Game
	if (Application::IsKeyPressed(VK_NUMPAD5))
	{
		Application::setScene(5);
	}
	//CHEAT CODES BY SEAN
	if (StatManager::GetInstance()->GetBool_Game(4))
	{
		Reset();
		StatManager::GetInstance()->SetBool_Frogger(false);
	}
	SceneBase::Update(dt);
	if (m_instructions)
	{
		instructionTimer -= dt;
		if (instructionTimer <= 0)
		{
			StatManager::GetInstance()->SetPrevGame(4);
			m_instructions = false;
		}
	}
	else if (!m_instructions)
	{
		if (Frog->getHP() == 0)
		{
			m_GameOver = true;
		}
		if (m_GameOver)
		{
			Results::getInstance()->UpdateVars(dt);

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
			if (!m_setOriginValues && !m_setStatsToDist)
			{
				score = Frog->getScore();

				GameEndCalculations();
				StatManager::GetInstance()->SetCharsOriginalValues();
				m_setStatsToDist = true;
				m_setOriginValues = true;
				Reset();
				
			}
			//if (!statgained)
			//{
			//	GameEndCalculations();
			//	StatManager::GetInstance()->SetCharsOriginalValues();
			//	statgained = true;
			//}
			
		}
		if (timer <= 0)
		{
			m_GameOver = true;
		}
		//if (Application::IsKeyPressed('L'))
		//{
		//	Reset();
		//}
		double x, y;
		Frog->setTimerInvicibility(dt, true);
		Application::GetCursorPos(&x, &y);
		int w = Application::GetWindowWidth();
		int h = Application::GetWindowHeight();
		v_mousepos = Vector3(static_cast<float>(x) / (w / m_worldWidth), (h - static_cast<float>(y)) / (h / m_worldHeight), 0.0f);
		timer -= dt;

		SpriteAnimation *walkRight = dynamic_cast<SpriteAnimation*>(meshList[GEO_FROG_RIGHT]);
		if (walkRight)
		{
			walkRight->Update(dt);
			walkRight->m_anim->animActive = true;

		}
		SpriteAnimation *walkLeft = dynamic_cast<SpriteAnimation*>(meshList[GEO_FROG_LEFT]);
		if (walkLeft)
		{
			walkLeft->Update(dt);
			walkLeft->m_anim->animActive = true;

		}

		static bool bMovingLeft = false;
		if (Frog->Frog_pos.x >= (m_worldWidth / 2) - 80)
		{
			if (Application::IsKeyPressed('A') && !bMovingLeft)
			{
				Frog->Frog_pos.x -= 10.f;
				Frog->setSide(true);
				bMovingLeft = true;
			}

			else if (!Application::IsKeyPressed('A') && bMovingLeft)
			{
				bMovingLeft = false;
			}
		}
		static bool bMovingRight = false;
		if (Frog->Frog_pos.x <= (m_worldWidth / 2) + 80)
		{
			if (Application::IsKeyPressed('D') && !bMovingRight)
			{
				Frog->Frog_pos.x += 10.f;
				Frog->setSide(false);
				bMovingRight = true;
			}
			else if (!Application::IsKeyPressed('D') && bMovingRight)
			{
				bMovingRight = false;
			}
		}
		static bool bMovingUp = false;
		if (Frog->Frog_pos.y < m_worldHeight - 10)
		{
			if (Application::IsKeyPressed('W') && !bMovingUp)
			{
				Frog->Frog_pos.y += 5.f;
				bMovingUp = true;
			}
			else if (!Application::IsKeyPressed('W') && bMovingUp)
			{
				bMovingUp = false;
			}
		}
		static bool bMovingDown = false;
		if (Frog->Frog_pos.y > 10)
		{
			if (Application::IsKeyPressed('S') && !bMovingDown)
			{
				Frog->Frog_pos.y -= 5.f;
				bMovingDown = true;
			}
			else if (!Application::IsKeyPressed('S') && bMovingDown)
			{
				bMovingDown = false;
			}
		}

		static bool bLButtonState = false;
		if (!bLButtonState && Application::IsMousePressed(0))
		{
			bLButtonState = true;
			std::cout << "LBUTTON DOWN" << std::endl;
			if (m_GameOver)
			{
				if (Results::getInstance()->ButtonMouseCollision())
				{
					cout << "hit" << endl;
				}
			}
		}
		else if (!Application::IsMousePressed(0) && bLButtonState)
		{
			bLButtonState = false;
			std::cout << "LBUTTON UP" << std::endl;

		}
		UpdateRock(dt);

		for (int i = 0; i < (int)m_goList->size(); ++i)
		{

			FrogObject *go = (*m_goList)[i];

			if (go->getActive())
			{
				switch (go->getType())
				{
				case FrogObject::GO_FROG:
				{
					go->Frog_pos += go->Frog_vel * (float)dt;

					break;
				}
				}
				for (int k = i + 1; k < (int)rock_List.size(); ++k)
				{
					FrogObject* go2 = (rock_List)[k];
					if (go2->getActive())
					{
						go = (*m_goList)[i];
						if (CheckCollision(go, go2))
						{
							go->CollisionResponse(go, go2, dt);

							if (Frog->getCoin() == 0)
							{
								m_coinCount = 0;
							}
						}
					}
				}
			}
		}
	}
}

FrogObject * SceneFrog::FetchGO()
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
		m_goList->push_back(new	FrogObject(FrogObject::GO_NONE));
	}

	(*m_goList)[m_goList->size() - 20]->setActive(true);
	return (*m_goList)[m_goList->size() - 20];
}


void SceneFrog::RenderRock(FrogObject* rock)
{
	switch (rock->getType())
	{
	case FrogObject::GO_ROCK:
		modelStack.PushMatrix();
		modelStack.Translate(rock->getPos());
		modelStack.Scale(rock->getScale());
		RenderMesh(meshList[GEO_FROG_ROCK], false);
		modelStack.PopMatrix();
		break;
	case FrogObject::GO_COIN:
		modelStack.PushMatrix();
		modelStack.Translate(rock->getPos());
		modelStack.Scale(rock->getScale());
		RenderMesh(meshList[GEO_COIN], false);
		modelStack.PopMatrix();
		break;
	}
}

void SceneFrog::RenderCoin(FrogObject* coin)
{
	modelStack.PushMatrix();
	modelStack.Translate(coin->getPos());
	modelStack.Scale(coin->getScale());
	RenderMesh(meshList[GEO_COIN], false);
	modelStack.PopMatrix();
}

void SceneFrog::RenderGO(FrogObject* go)
{
	switch (go->getType())
	{
	case FrogObject::GO_FROG:
	{
		if (Frog->getSide())
		{
			modelStack.PushMatrix();
			modelStack.Translate(go->Frog_pos);
			modelStack.Scale(go->getScale() * 2);
			RenderMesh(meshList[GEO_FROG_LEFT], false);
			modelStack.PopMatrix();
			break;
		}
		else
		{
			modelStack.PushMatrix();
			modelStack.Translate(go->Frog_pos);
			modelStack.Scale(go->getScale() * 2);
			RenderMesh(meshList[GEO_FROG_RIGHT], false);
			modelStack.PopMatrix();
			break;
		}
	}
	case FrogObject::GO_PLATFORM:
	{
		modelStack.PushMatrix();
		modelStack.Translate(go->getPos());
		modelStack.Scale(go->getScale());
		RenderMesh(meshList[GEO_FROG_PLATFORM], false);
		modelStack.PopMatrix();
		break;
	}
	case FrogObject::GO_ROCK:
	{
		modelStack.PushMatrix();
		modelStack.Translate(go->getPos());
		modelStack.Scale(go->getScale());
		RenderMesh(meshList[GEO_FROG_ROCK], false);
		modelStack.PopMatrix();
		break;
	}
	default:
	{
		break;
	}
	}
}

void SceneFrog::RenderMap()
{
	for (int i = 1; i < 20; i++)
	{
		for (int k = 0; k < 10; k++)
		{
			modelStack.PushMatrix();
			modelStack.Translate(20 * i, 20 * k, 0);
			modelStack.Rotate(Math::RadianToDegree(atan2(camera.position.x - 0, camera.position.z - 0)), 0, 1, 0);
			modelStack.Scale(50, 50, 50);
			RenderMesh(meshList[GEO_FROG_MAP], false);
			modelStack.PopMatrix();
		}
	}
	modelStack.PushMatrix();
	modelStack.Translate((m_worldWidth / 2) - 80, m_worldHeight / 2, 0);
	modelStack.Rotate(Math::RadianToDegree(atan2(camera.position.x - 0, camera.position.z - 0)), 0, 1, 0);
	modelStack.Scale(5, m_worldHeight, 1);
	RenderMesh(meshList[GEO_FROG_BORDER], false);
	modelStack.PopMatrix();
	modelStack.PushMatrix();
	modelStack.Translate((m_worldWidth / 2) + 80, m_worldHeight / 2, 0);
	modelStack.Rotate(Math::RadianToDegree(atan2(camera.position.x - 0, camera.position.z - 0)), 0, 1, 0);
	modelStack.Scale(5, m_worldHeight, 1);
	RenderMesh(meshList[GEO_FROG_BORDER], false);
	modelStack.PopMatrix();
}

void SceneFrog::Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//	Calculating aspect ratio
	//	 James 13/8/2019
	m_worldHeight = 200.f;
	//	 End James 13/8/2019
	m_worldWidth = m_worldHeight * (float)Application::GetWindowWidth() / Application::GetWindowHeight();

	//	 Projection matrix : Orthographic Projection
	Mtx44 projection;
	projection.SetToOrtho(0, m_worldWidth, 0, m_worldHeight, -10, 10);
	projectionStack.LoadMatrix(projection);

	//	 Camera matrix
	viewStack.LoadIdentity();
	viewStack.LookAt(
		camera.position.x, camera.position.y, camera.position.z,
		camera.target.x, camera.target.y, camera.target.z,
		camera.up.x, camera.up.y, camera.up.z
	);
	//	 Model matrix : an identity matrix (model will be at the origin)
	modelStack.LoadIdentity();

	if (m_instructions)
	{
		modelStack.PushMatrix();
		modelStack.Translate(m_worldWidth / 2, m_worldHeight / 2, 0);
		modelStack.Scale(m_worldHeight / 2, m_worldHeight / 2, 0);
		RenderMesh(meshList[GEO_FROG_INSTRUCTIONS], false);
		modelStack.PopMatrix();
	}


	if (!m_instructions)
	{
		RenderMap();

		for (std::vector<FrogObject *>::iterator it = m_goList->begin(); it != m_goList->end(); ++it)
		{
			FrogObject *go = (FrogObject *)*it;
			if (go->getActive())
			{
				RenderGO(go);
			}
		}

		for (std::vector<FrogObject *>::iterator it = rock_List.begin(); it != rock_List.end(); ++it)
		{
			FrogObject *rock = (FrogObject*)*it;
			if (rock->getActive())
			{
				RenderRock(rock);
			}
		}
	
	
		std::ostringstream ss2;
		ss2.precision(2);
		ss2 << "HP: " << Frog->getHP();
		RenderTextOnScreen(meshList[GEO_TEXT], ss2.str(), Color(0, 1, 0), 3, 0, 3);
		std::ostringstream ss4;
		ss4.precision(6);
		ss4 << "Score: " << Frog->getScore();
		RenderTextOnScreen(meshList[GEO_TEXT], ss4.str(), Color(0, 1, 0), 3, 0, 9);
		std::ostringstream ss5;
		ss5.precision(2);
		ss5 << "Time left: " << timer;
		RenderTextOnScreen(meshList[GEO_TEXT], ss5.str(), Color(0, 1, 0), 3, 0, 12);

		std::ostringstream ss6;
		ss6.precision(2);
		ss6 << "Coins left: " << Frog->getCoin();
		RenderTextOnScreen(meshList[GEO_TEXT], ss6.str(), Color(0, 1, 0), 3, 0, 15);
	}
	if (m_GameOver)
	{
		Results::getInstance()->RenderResults(score, m_grade);
	}

}

void SceneFrog::Exit()
{
	SceneBase::Exit();
	//Cleanup FrogObjects;
	while (m_goList->size() > 0)
	{
		FrogObject *go = m_goList->back();
		delete go;
		m_goList->pop_back();
	}
	while (rock_List.size() > 0)
	{
		FrogObject *go = rock_List.back();
		delete go;
		rock_List.pop_back();
	}

	delete m_goList;
}

void SceneFrog::Reset()
{
	m_rockCount = 0;
	m_coinCount = 0;
	m_GameOver = false;
	m_instructions = true;
	instructionTimer = 600.f;
	timer = 30.f;
	Frog->Frog_pos.Set(200, 10, 0);
	Frog->setScore(0);
	Frog->setCoin(m_coinCount);
}
void SceneFrog::GameEndCalculations()
{
	if (Frog->getScore() >= 2000)
	{
		m_grade = 'S';
		StatManager::GetInstance()->UpdateChar01F(StatManager::GetInstance()->GetChar01().m_frustration -20);
		StatManager::GetInstance()->UpdateChar01M(StatManager::GetInstance()->GetChar01().m_motivation + 20);
		StatManager::GetInstance()->UpdateChar02F(StatManager::GetInstance()->GetChar02().m_frustration -20);
		StatManager::GetInstance()->UpdateChar02M(StatManager::GetInstance()->GetChar02().m_motivation + 20);
		StatManager::GetInstance()->UpdateChar03F(StatManager::GetInstance()->GetChar03().m_frustration -20);
		StatManager::GetInstance()->UpdateChar03M(StatManager::GetInstance()->GetChar03().m_motivation+ 20);
		StatManager::GetInstance()->UpdateChar04F(StatManager::GetInstance()->GetChar04().m_frustration -20);
		StatManager::GetInstance()->UpdateChar04M(StatManager::GetInstance()->GetChar04().m_motivation +20);
		Results::getInstance()->InitStatsToDist(35);
	}
	else if (Frog->getScore() >= 1500 && Frog->getScore() < 2000)
	{
		m_grade = 'A';
		Results::getInstance()->InitStatsToDist(25);

	}
	else if (Frog->getScore() >= 1000 && Frog->getScore() < 1500)
	{
		m_grade = 'B';
		Results::getInstance()->InitStatsToDist(20);
	}
	else if (Frog->getScore() >= 500 && Frog->getScore() < 1000)
	{
		m_grade = 'C';
		Results::getInstance()->InitStatsToDist(15);
	}
	else if (Frog->getScore() >= 100 && Frog->getScore() < 500)
	{
		m_grade = 'D';
		Results::getInstance()->InitStatsToDist(10);
	}
	else
	{
		m_grade = 'F';
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
