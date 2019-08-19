#include "SceneMole.h"
#include "GL\glew.h"
#include "../Application.h"
#include <sstream>
#include "../Rendering/LoadTGA.h"
#include "../Rendering/MeshBuilder.h"
#include "../Rendering/Particles.h"


SceneMole::SceneMole()
{
}

SceneMole::~SceneMole()
{
}

void SceneMole::Init()
{
	SceneBase::Init();
	Results::getInstance()->InitVars();
	//Calculating aspect ratio
	m_worldHeight = 100.f;
	m_worldWidth = m_worldHeight * (float)Application::GetWindowWidth() / Application::GetWindowHeight();
	m_halfWorldHeight = m_worldHeight / 2;
	m_halfWorldWidth = m_worldWidth / 2;

	m_quarterWorldWidth = m_worldWidth / 4;
	m_eightWorldWidth = m_worldWidth / 8;

	m_sixthWorldHeight = m_worldHeight / 6;

	//Physics code here
	m_speed = 1.f;

	Math::InitRNG();
	//  ******************************* PROPS HERE  ******************************* //
	t_hammerIdle = LoadTGA("Image//Hammer.tga");
	t_hammerHit = LoadTGA("Image//BGTest.tga");

	meshList[GEO_HAMMER] = MeshBuilder::GenerateQuad("hammer", Color(1, 1, 1), 1.f);
	meshList[GEO_HAMMER]->textureID = t_hammerIdle;

	meshList[GEO_BACKPANEL] = MeshBuilder::GenerateQuad("back", Color(1, 0, 0), 1.f);
	meshList[GEO_BACKPANEL]->textureID = LoadTGA("Image//backpanel.tga");
	meshList[GEO_MIDPANEL] = MeshBuilder::GenerateQuad("mid", Color(0, 1, 0), 1.f);
	meshList[GEO_MIDPANEL]->textureID = LoadTGA("Image//midpanel.tga");
	meshList[GEO_FRONTPANEL] = MeshBuilder::GenerateQuad("front", Color(0, 0, 1), 1.f);
	meshList[GEO_FRONTPANEL]->textureID = LoadTGA("Image//frontpanel.tga");

	meshList[GEO_MOLETEST] = MeshBuilder::GenerateQuad("testmole", Color(1, 1, 1), 1.f);
	meshList[GEO_TEXT] = MeshBuilder::GenerateText("text", 16, 16);
	meshList[GEO_TEXT]->textureID = LoadTGA("Image//calibri.tga");

	meshList[GEO_MOLESTATS] = MeshBuilder::GenerateQuad("ui", Color(0, 0, 0), 1.f);

	meshList[GEO_MOLERESULTS] = MeshBuilder::GenerateQuad("results", Color(0, 0, 0), 1.f);

	meshList[GEO_C01_RESULT_QUAD] = MeshBuilder::GenerateQuad("c01result", Color(1, 1, 1), 1.f);
	meshList[GEO_C01_RESULT_QUAD]->textureID = LoadTGA("Image//resultTest.tga");
	meshList[GEO_C02_RESULT_QUAD] = MeshBuilder::GenerateQuad("c01result", Color(1, 1, 1), 1.f);
	meshList[GEO_C03_RESULT_QUAD] = MeshBuilder::GenerateQuad("c01result", Color(1, 1, 1), 1.f);
	meshList[GEO_C04_RESULT_QUAD] = MeshBuilder::GenerateQuad("c01result", Color(1, 1, 1), 1.f);


	meshList[GEO_MOLEFONT] = MeshBuilder::GenerateText("teko", 16, 16);
	meshList[GEO_MOLEFONT]->textureID = LoadTGA("Image//KidsZone.tga");

	//  ******************************* SPRITE ANIMATIONS HERE  ******************************* //

	//  ******************************* PARTICLES HERE  ******************************* //
	Mtx44 projection;
	projection.SetToOrtho(0, m_worldWidth, 0, m_worldHeight, -10, 10);
	projectionStack.LoadMatrix(projection);
	
	// ******************************* INIT GAME THINGS HERE ******************************* //

	// Top row of moles for rendering
	for (unsigned int i = 0 ; i < 4 ; i++)
	{
		MoleObject* temp = new MoleObject(MoleObject::GO_MOLE);
		temp->pos.Set(m_eightWorldWidth + (i * m_quarterWorldWidth) , (m_worldHeight - m_sixthWorldHeight) - 35, -4);
		temp->scale.Set(20, 20, 20);
		temp->active = false;

		m_moleListTop.push_back(temp);
	}

	// Bottom row of moles for rendering
	for (unsigned int i = 0; i < 4; i++)
	{
		MoleObject* temp = new MoleObject(MoleObject::GO_MOLE);
		temp->pos.Set(m_eightWorldWidth + (i * m_quarterWorldWidth),(m_worldHeight - 3 * m_sixthWorldHeight) - 35, -4);
		temp->scale.Set(20, 20, 20);
		temp->active = false;

		m_moleListBot.push_back(temp);
	}

	// Colate all moles int a single vector for collision checking
	for (unsigned int i = 0; i < m_moleListBot.size() + m_moleListTop.size(); i++)
	{
		for (unsigned int k = 0; k < m_moleListBot.size(); k++)
		{
			m_moleListTotal.push_back(m_moleListBot[k]);
		}
		for (unsigned int j = 0; j < m_moleListTop.size(); j++)
		{
			m_moleListTotal.push_back(m_moleListTop[j]);
		}
	}

	m_Hammer = FetchGO();
	m_Hammer->type = MoleObject::GO_HAMMER;
	m_Hammer->pos.Set(m_halfWorldWidth, m_halfWorldHeight, 5);
	m_Hammer->scale.Set(20, 20, 20);

	m_frontScale.Set(198, 36, 1);
	m_midScale.Set(198, 36, 1);
	m_backScale.Set(198, 36, 1);

	m_popUpTimer = Math::RandFloatMinMax(0.5f, 1.5f);
	m_score = 0;
	m_gameTimer = 2.f;
	m_gameOver = false;

	// // ******************************* INIT RESULT THINGS HERE ******************************* //

	r_quad01Pos.Set(m_quarterWorldWidth, m_sixthWorldHeight * 3, 6);
	r_quad02Pos.Set(m_quarterWorldWidth * 3, m_sixthWorldHeight * 3, 6);
	r_quad03Pos.Set(m_quarterWorldWidth, m_sixthWorldHeight, 6);
	r_quad04Pos.Set(m_quarterWorldWidth * 3, m_sixthWorldHeight, 6);
	m_setOriginValues = false;
	m_setStatsToDist = false;

}

void SceneMole::Update(double dt)
{
	SceneBase::Update(dt);
	if (m_gameOver)
	{
		Results::getInstance()->UpdateVars(dt);
	}
	if (m_gameOver && !m_setStatsToDist)
	{
		Results::getInstance()->InitStatsToDist(10);
		m_setStatsToDist = true;
	}
	if (m_gameTimer <= 0)
	{
		m_gameTimer = 0.f;
		m_gameOver = true;
	}
	if (m_gameOver && !m_setOriginValues)
	{
		StatManager::GetInstance()->SetCharsOriginalValues();
		m_setOriginValues = true;

	}
	if (!m_gameOver)
		m_gameTimer -= dt;

	if (m_gameTimer < 0)
	{
		m_gameOver = true;
	} 
	static bool bLButtonState = false;
	if (!bLButtonState && Application::IsMousePressed(0))
	{
		bLButtonState = true;
		std::cout << "LBUTTON DOWN" << std::endl;
		meshList[GEO_HAMMER]->textureID = t_hammerHit;
		if (!m_gameOver)
		{
			if (HammerCollisionCheck())
			{
				// Play SFX
			}

		}
		else
		{
			if (Results::getInstance()->ButtonMouseCollision())
			{
				cout << "hit" << endl;
			}
		}
	}
	else if (bLButtonState && !Application::IsMousePressed(0))
	{
		bLButtonState = false;
		std::cout << "LBUTTON UP" << std::endl;
		meshList[GEO_HAMMER]->textureID = t_hammerIdle;
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
	UpdateHammerPos();

	UpdateMoles(dt);


	UpdateParticles(dt);
}


Particles* SceneMole::getParticle()
{
	for (std::vector<Particles *>::iterator it = m_particleList.begin(); it != m_particleList.end(); ++it)
	{
		Particles *particle = (Particles *)*it;

		if (!particle->active)
		{
			particle->active = true;
			m_particleCount++;
			return particle;
		}
	}
	for (unsigned i = 0; i < 2; ++i)
	{
		Particles *particle = new Particles(ParticleObject_TYPE::P_ParticleTest);
		m_particleList.push_back(particle);
	}
	m_particleCount++;
	m_particleList[m_particleList.size() - 1]->active = true;
	return m_particleList[m_particleList.size() - 1];
}

void SceneMole::UpdateParticles(double dt)
{
	if (m_particleCount < MAX_PARTICLE)
	{
		Particles* particle = getParticle();
		particle->type = ParticleObject_TYPE::P_ParticleTest;
		particle->scale.Set(2, 2, 2);
		particle->vel.Set(Math::RandFloatMinMax(0, 0.2f), Math::RandFloatMinMax(0, 0.2f), 0.0f);
		//particle->rotationSpeed = Math::RandFloatMinMax(20.f, 40.f);
		particle->pos.Set(Math::RandFloatMinMax(0, m_worldWidth), 0, 0);
		particle->lifeTime = 4.4f;
	}
	for (std::vector<Particles *>::iterator it = m_particleList.begin(); it != m_particleList.end(); ++it)
	{
		Particles *particle = (Particles *)*it;
		if (particle->active)
		{
			if (particle->type == ParticleObject_TYPE::P_ParticleTest)
			{
				particle->vel += Vector3(0, -m_Gravity.y, 0)* (float)dt;
				particle->pos += particle->vel * (float)dt;
				particle->rotation += particle->rotationSpeed * (float)dt;
				particle->lifeTime -= dt;
			}
			if (particle->lifeTime < 0)
			{
				particle->active = false;
				m_particleCount--;
			}
			if (particle->pos.y > m_worldHeight)
			{
				particle->active = false;
				m_particleCount--;
			}
		}
	}
}
void SceneMole::RenderParticles(Particles *particle)
{
	switch (particle->type)
	{
	case ParticleObject_TYPE::P_ParticleTest:
		modelStack.PushMatrix();
		modelStack.Translate(particle->pos.x, particle->pos.y, particle->pos.z);
		//modelStack.Rotate(Math::RadianToDegree(atan2(camera.position.x - particle->pos.x, camera.position.z - particle->pos.z)), 0, 1, 0);
		modelStack.Rotate(particle->rotation, 0, 0, 1);
		modelStack.Scale(particle->scale.x, particle->scale.y, particle->scale.z);
		RenderMesh(meshList[GEO_PARTICLE_TEST], false);
		modelStack.PopMatrix();
		break;
	default:
		cout << "Found NULL Particle" << endl;
		break;
	}

}

void SceneMole::RenderAnimation()
{
	modelStack.PushMatrix();
	modelStack.Translate(20, 50, 0);
	modelStack.Rotate(Math::RadianToDegree(atan2(camera.position.x - 0, camera.position.z - 0)), 0, 1, 0);

	modelStack.Scale(10, 10, 10);

	RenderMesh(meshList[GEO_SPRITE_ANIMATION], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(100, 50, 0);
	modelStack.Rotate(Math::RadianToDegree(atan2(camera.position.x - 0, camera.position.z - 0)), 0, 1, 0);

	modelStack.Scale(10, 10, 10);

	RenderMesh(meshList[GEO_HAMMER_SPRITE], false);
	modelStack.PopMatrix();
	//std::cout << "WOKRING" << std::endl;
}

void SceneMole::Render()
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//Calculating aspect ratio
	m_worldHeight = 100.f;
	m_worldWidth = m_worldHeight * (float)Application::GetWindowWidth() / Application::GetWindowHeight();
	m_halfWorldHeight = m_worldHeight / 2;
	m_halfWorldWidth = m_worldWidth / 2;
	
	m_quarterWorldWidth = m_worldWidth / 4;
	m_eightWorldWidth = m_worldWidth / 8;

	r_quad01Pos.Set(m_quarterWorldWidth, m_sixthWorldHeight * 3, 6);
	r_quad02Pos.Set(m_quarterWorldWidth * 3, m_sixthWorldHeight * 3, 6);
	r_quad03Pos.Set(m_quarterWorldWidth, m_sixthWorldHeight, 6);
	r_quad04Pos.Set(m_quarterWorldWidth * 3, m_sixthWorldHeight, 6);

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

	if (!m_gameOver)
	{
		RenderMachine();
		RenderGO(m_Hammer);
		RenderUI();
	}
	if (m_gameOver)
	{
		Results::getInstance()->RenderResults(m_score);
		//RenderResults();
	}

}

void SceneMole::RenderGO(MoleObject * go)
{
	switch (go->type)
	{
	case MoleObject::GO_HAMMER:
		modelStack.PushMatrix();
		modelStack.Translate(go->pos.x, go->pos.y, go->pos.z);
		modelStack.Scale(go->scale.x, go->scale.y, go->scale.z);
		RenderMesh(meshList[GEO_HAMMER], false);
		modelStack.PopMatrix();
		break;
	case MoleObject::GO_MOLE:
		modelStack.PushMatrix();
		modelStack.Translate(go->pos.x, go->pos.y + go->mole_yOffset, go->pos.z);
		modelStack.Scale(go->scale.x, go->scale.y, go->scale.z);
		RenderMesh(meshList[GEO_MOLETEST], false);
		modelStack.PopMatrix();
	default:
		break;
	}
}

MoleObject * SceneMole::FetchGO()
{
	for (int i = 0; i < m_goList.size(); i++)
	{
		if (!m_goList[i]->active)
		{
			return m_goList[i];
		}
	}

	for (int i = 0; i < 20; ++i)
	{
		m_goList.push_back(new MoleObject(MoleObject::GO_NONE));
	}
	return m_goList[m_goList.size() - 1];
}

void SceneMole::UpdateHammerPos()
{
	double x, y;
	Application::GetCursorPos(&x, &y);
	int w = Application::GetWindowWidth();
	int h = Application::GetWindowHeight();
	float posX = static_cast<float>(x) / w * m_worldWidth;
	float posY = (h - static_cast<float>(y)) / h * m_worldHeight;

	m_Hammer->pos.Set(posX, posY, 5);
}

void SceneMole::UpdateMoles(double dt)
{
	m_popUpTimer -= dt;

	if (m_popUpTimer <= 0)
	{
		bool allActive = false;
		int activeCounter = 0;
		for (unsigned int i = 0; i < m_moleListTotal.size(); i++)
		{
			if (m_moleListTotal[i]->active)
			{
				activeCounter++;
			}
			if (activeCounter == m_moleListTotal.size())
			{
				allActive = true;
			}
		}
		// Random selection of mole to pop up
		while (!allActive)
		{
			int randMole = Math::RandIntMinMax(0, 7);
			if (!m_moleListTotal[randMole]->active)
			{
				m_moleListTotal[randMole]->active = true;
				m_moleListTotal[randMole]->mole_goUp = true;
				m_moleListTotal[randMole]->mole_lifeTime = 10.5f;
				break;
			}
		}

		m_popUpTimer = Math::RandFloatMinMax(0.5f, 1.5f);
	}

	// Check their lifetime
	for (unsigned int i = 0; i < m_moleListTotal.size(); i++)
	{
		if (m_moleListTotal[i]->active)
		{
			m_moleListTotal[i]->mole_lifeTime -= dt;
			if (m_moleListTotal[i]->mole_lifeTime <= 0.f)
			{
				m_moleListTotal[i]->active = false;
				m_moleListTotal[i]->mole_hit = true;
				m_moleListTotal[i]->mole_lifeTime = 0.f;

			}
			// 'Animation' for going up
			if (m_moleListTotal[i]->mole_goUp)
			{
				m_moleListTotal[i]->mole_yOffset += 0.5f;
				if (m_moleListTotal[i]->mole_yOffset >= 25.f)
				{
					m_moleListTotal[i]->mole_yOffset = 25.f;
					m_moleListTotal[i]->mole_goUp = false;
				}
			}
		}
		// 'Animation' for going down
		if (m_moleListTotal[i]->mole_hit)
		{
			m_moleListTotal[i]->mole_yOffset -= 0.5f;
			if (m_moleListTotal[i]->mole_yOffset <= 0.f)
			{
				m_moleListTotal[i]->mole_yOffset = 0.f;
				m_moleListTotal[i]->mole_hit = false;
			}
		}
	}
}

void SceneMole::RenderMachine()
{
	// Back Panel
	modelStack.PushMatrix();
	modelStack.Translate(m_halfWorldWidth,  5 * (m_worldHeight / 6), -5);
	modelStack.Scale(m_backScale.x, m_backScale.y, 1);
	RenderMesh(meshList[GEO_BACKPANEL], false);
	modelStack.PopMatrix();

	// Row of moles Top

	for (unsigned int i = 0 ; i != m_moleListTop.size(); ++i)
	{
		RenderGO(m_moleListTop[i]);
	}

	// Mid Panel
	modelStack.PushMatrix();
	modelStack.Translate(m_halfWorldWidth, 3 * (m_worldHeight / 6), -3);
	modelStack.Scale(m_backScale.x, m_backScale.y, 1);
	RenderMesh(meshList[GEO_MIDPANEL], false);
	modelStack.PopMatrix();

	// Row of moles Bot

	for (unsigned int i = 0; i != m_moleListTop.size(); ++i)
	{
		RenderGO(m_moleListBot[i]);
	}

	// Front Panel
	modelStack.PushMatrix();
	modelStack.Translate(m_halfWorldWidth, m_worldHeight / 6, -1);
	modelStack.Scale(m_backScale.x, m_backScale.y, 1);
	RenderMesh(meshList[GEO_FRONTPANEL], false);
	modelStack.PopMatrix();

}

void SceneMole::RenderUI()
{
	modelStack.PushMatrix();
	modelStack.Translate(m_halfWorldWidth, 10, 0);
	modelStack.Scale(120, 20, 1);
	RenderMesh(meshList[GEO_MOLESTATS], false);
	modelStack.PopMatrix();

	std::ostringstream ss;
	ss << "Score: " << m_score;
	RenderTextOnScreen(meshList[GEO_MOLEFONT], ss.str(), Color(1, 1, 1), 3, 30, 6);

	ss.clear();
	ss.str("");
	ss.precision(3);
	ss << "Time Left: " << m_gameTimer;
	RenderTextOnScreen(meshList[GEO_MOLEFONT], ss.str(), Color(1, 1, 1), 3, 18, 2);
}

//void SceneMole::RenderResults()
//{
//	// the black bg the player sees
//	modelStack.PushMatrix();
//	modelStack.Translate(m_halfWorldWidth, m_halfWorldHeight, 5);
//	modelStack.Scale(198, 108, 1);
//	RenderMesh(meshList[GEO_MOLERESULTS], false);
//	modelStack.PopMatrix();
//
//	std::ostringstream ss;
//	ss << "MINIGAME OVER";
//	RenderTextOnScreen(meshList[GEO_MOLEFONT], ss.str(), Color(1, 1, 1), 5, 10, 50);
//
//	ss.clear();
//	ss.str("");
//	ss << "Score: " << m_score;
//	RenderTextOnScreen(meshList[GEO_MOLEFONT], ss.str(), Color(1, 1, 1), 2, 30, 45);
//	// get instance of player stats
//
//	// Render Character Quad -> stats
//	// C01 Quad
//	modelStack.PushMatrix();
//	modelStack.Translate(r_quad01Pos);
//	modelStack.Scale(90, 30, 1);
//	RenderMesh(meshList[GEO_C01_RESULT_QUAD], false);
//	modelStack.PopMatrix();
//
//	// C01 Stats
//
//	// C02 Quad
//	modelStack.PushMatrix();
//	modelStack.Translate(r_quad02Pos);
//	modelStack.Scale(90, 30, 1);
//	RenderMesh(meshList[GEO_C02_RESULT_QUAD], false);
//	modelStack.PopMatrix();
//
//	// C01 Stats
//
//	// C03 Quad
//	modelStack.PushMatrix();
//	modelStack.Translate(r_quad03Pos);
//	modelStack.Scale(90, 30, 1);
//	RenderMesh(meshList[GEO_C03_RESULT_QUAD], false);
//	modelStack.PopMatrix();
//
//	// C01 Stats
//
//	// C04 Quad
//	modelStack.PushMatrix();
//	modelStack.Translate(r_quad04Pos);
//	modelStack.Scale(90, 30, 1);
//	RenderMesh(meshList[GEO_C04_RESULT_QUAD], false);
//	modelStack.PopMatrix();
//
//	// C04 Stats
//
//
//	// Collision check for mouse position and quad for rObjects
//
//
//
//	// Render Reset and Continue
//	modelStack.PushMatrix();
//	modelStack.PopMatrix();
//
//	modelStack.PushMatrix();
//	modelStack.PopMatrix();
//}

bool SceneMole::HammerCollisionCheck()
{
	for (unsigned int i = 0; i < m_moleListTotal.size(); i++)
	{
		if (m_Hammer->pos.x > m_moleListTotal[i]->pos.x - (m_moleListTotal[i]->scale.x / 2) && 
			m_Hammer->pos.x < m_moleListTotal[i]->pos.x + (m_moleListTotal[i]->scale.x / 2))
		{
			if (m_Hammer->pos.y < m_moleListTotal[i]->pos.y + (m_moleListTotal[i]->scale.y / 2) + m_moleListTotal[i]->mole_yOffset &&
				m_Hammer->pos.y > m_moleListTotal[i]->pos.y - (m_moleListTotal[i]->scale.y / 2) + m_moleListTotal[i]->mole_yOffset)
			{
				if (m_moleListTotal[i]->active)
				{
					std::cout << "Hit Mole No: " << i << std::endl;
					m_score += m_moleListTotal[i]->mole_lifeTime * 100;
					m_moleListTotal[i]->mole_lifeTime = 0.f;
					m_moleListTotal[i]->mole_hit = true;
					m_moleListTotal[i]->active = false;
					return true;
				}
			}
		}

	}
	return false;
}

void SceneMole::Exit()
{
	SceneBase::Exit();
	//Cleanup GameObjects
	while (m_goList.size() > 0)
	{
		GameObject *go = m_goList.back();
		delete go;
		m_goList.pop_back();
	}
	while (m_particleList.size() > 0)
	{
		Particles *particle = m_particleList.back();
		delete particle;
		m_particleList.pop_back();
	}
}
