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
	t_hammerHit = LoadTGA("Image//Hammer_hit.tga");
	t_hammerIdle_frost = LoadTGA("Image//Hammer_Frost.tga");
	t_hammerHit_frost = LoadTGA("Image//Hammer_hit_frost.tga");

	meshList[GEO_HAMMER] = MeshBuilder::GenerateQuad("hammer", Color(1, 1, 1), 1.f);
	meshList[GEO_HAMMER]->textureID = t_hammerIdle;

	meshList[GEO_BACKPANEL] = MeshBuilder::GenerateQuad("back", Color(1, 0, 0), 1.f);
	meshList[GEO_BACKPANEL]->textureID = LoadTGA("Image//backpanel.tga");
	meshList[GEO_MIDPANEL] = MeshBuilder::GenerateQuad("mid", Color(0, 1, 0), 1.f);
	meshList[GEO_MIDPANEL]->textureID = LoadTGA("Image//midpanel.tga");
	meshList[GEO_FRONTPANEL] = MeshBuilder::GenerateQuad("front", Color(0, 0, 1), 1.f);
	meshList[GEO_FRONTPANEL]->textureID = LoadTGA("Image//frontpanel.tga");

	meshList[GEO_TEXT] = MeshBuilder::GenerateText("text", 16, 16);
	meshList[GEO_TEXT]->textureID = LoadTGA("Image//calibri.tga");

	meshList[GEO_MOLESTATS] = MeshBuilder::GenerateQuad("ui", Color(0, 0, 0), 1.f);


	//meshList[GEO_MOLERESULTS] = MeshBuilder::GenerateQuad("results", Color(0, 0, 0), 1.f);

	//meshList[GEO_C01_RESULT_QUAD] = MeshBuilder::GenerateQuad("c01result", Color(1, 1, 1), 1.f);
	//meshList[GEO_C01_RESULT_QUAD]->textureID = LoadTGA("Image//resultTest.tga");
	//meshList[GEO_C02_RESULT_QUAD] = MeshBuilder::GenerateQuad("c01result", Color(1, 1, 1), 1.f);
	//meshList[GEO_C03_RESULT_QUAD] = MeshBuilder::GenerateQuad("c01result", Color(1, 1, 1), 1.f);
	//meshList[GEO_C04_RESULT_QUAD] = MeshBuilder::GenerateQuad("c01result", Color(1, 1, 1), 1.f);

	meshList[GEO_MOLE] = MeshBuilder::GenerateQuad("testmole", Color(1, 1, 1), 1.f);
	meshList[GEO_MOLE]->textureID = LoadTGA("Image//MOLE.tga");
	meshList[GEO_MOLE_BRONZE] = MeshBuilder::GenerateQuad("bronzeMole", Color(0.2f, 0, 0), 1.f);
	meshList[GEO_MOLE_BRONZE]->textureID = LoadTGA("Image//MOLE_BRONZE.tga");
	meshList[GEO_MOLE_SILVER] = MeshBuilder::GenerateQuad("silverMole", Color(0, 0.9f, 0), 1.f);
	meshList[GEO_MOLE_SILVER]->textureID = LoadTGA("Image//MOLE_SILVER.tga");
	meshList[GEO_MOLE_GOLD] = MeshBuilder::GenerateQuad("goldMole", Color(1, 0.5f, 0), 1.f);
	meshList[GEO_MOLE_GOLD]->textureID = LoadTGA("Image//MOLE_GOLD.tga");
	meshList[GEO_MOLE_BOMB] = MeshBuilder::GenerateQuad("bombMole", Color(0, 0, 0), 1.f);
	meshList[GEO_MOLE_BOMB]->textureID = LoadTGA("Image//MOLE_BOMB.tga");
	meshList[GEO_MOLE_FROST] = MeshBuilder::GenerateQuad("frostMole", Color(0, 0, 1), 1.f);
	meshList[GEO_MOLE_FROST]->textureID = LoadTGA("Image//MOLE_FROST.tga");

	meshList[GEO_GAMEFONT] = MeshBuilder::GenerateText("kzone", 16, 16);
	meshList[GEO_GAMEFONT]->textureID = LoadTGA("Image//KidsZone.tga");

	meshList[GEO_MOLE_INSTRUCT] = MeshBuilder::GenerateQuad("instructions_mole", Color(1, 1, 1), 1.f);
	meshList[GEO_MOLE_INSTRUCT]->textureID = LoadTGA("Image//Mole_Instructions.tga");

	//  ******************************* SPRITE ANIMATIONS HERE  ******************************* //

	meshList[GEO_MOLE_EXPLOSION] = MeshBuilder::GenerateSpriteAnimation("epxlode", 8, 10);
	meshList[GEO_MOLE_EXPLOSION]->textureID = LoadTGA("Image//Mole_explode.tga");
	meshList[GEO_MOLE_EXPLOSION2] = MeshBuilder::GenerateSpriteAnimation("epxlode2", 8, 10);
	meshList[GEO_MOLE_EXPLOSION2]->textureID = LoadTGA("Image//Mole_explode.tga");
	meshList[GEO_MOLE_EXPLOSION3] = MeshBuilder::GenerateSpriteAnimation("epxlode3", 8, 10);
	meshList[GEO_MOLE_EXPLOSION3]->textureID = LoadTGA("Image//Mole_explode.tga");
	meshList[GEO_MOLE_EXPLOSION4] = MeshBuilder::GenerateSpriteAnimation("epxlode4", 8, 10);
	meshList[GEO_MOLE_EXPLOSION4]->textureID = LoadTGA("Image//Mole_explode.tga");
	meshList[GEO_MOLE_EXPLOSION5] = MeshBuilder::GenerateSpriteAnimation("epxlode5", 8, 10);
	meshList[GEO_MOLE_EXPLOSION5]->textureID = LoadTGA("Image//Mole_explode.tga");
	meshList[GEO_MOLE_EXPLOSION6] = MeshBuilder::GenerateSpriteAnimation("epxlode6", 8, 10);
	meshList[GEO_MOLE_EXPLOSION6]->textureID = LoadTGA("Image//Mole_explode.tga");
	meshList[GEO_MOLE_EXPLOSION7] = MeshBuilder::GenerateSpriteAnimation("epxlode7", 8, 10);
	meshList[GEO_MOLE_EXPLOSION7]->textureID = LoadTGA("Image//Mole_explode.tga");
	meshList[GEO_MOLE_EXPLOSION8] = MeshBuilder::GenerateSpriteAnimation("epxlode8", 8, 10);
	meshList[GEO_MOLE_EXPLOSION8]->textureID = LoadTGA("Image//Mole_explode.tga");

	//Sounds
	soundSystem.AddSound("whack", "Sounds//Hammer_Whack.wav");


	explode = dynamic_cast<SpriteAnimation *> (meshList[GEO_MOLE_EXPLOSION]);
	if (explode)
	{
		explode->m_anim = new Animation();
		explode->m_anim->Set(0, 80, 0, 1.f, false);
	}
	explode2 = dynamic_cast<SpriteAnimation *> (meshList[GEO_MOLE_EXPLOSION2]);
	if (explode2)
	{
		explode2->m_anim = new Animation();
		explode2->m_anim->Set(0, 80, 0, 1.f, false);
	}
	explode3 = dynamic_cast<SpriteAnimation *> (meshList[GEO_MOLE_EXPLOSION3]);
	if (explode3)
	{
		explode3->m_anim = new Animation();
		explode3->m_anim->Set(0, 80, 0, 1.f, false);
	}
	explode4 = dynamic_cast<SpriteAnimation *> (meshList[GEO_MOLE_EXPLOSION4]);
	if (explode4)
	{
		explode4->m_anim = new Animation();
		explode4->m_anim->Set(0, 80, 0, 1.f, false);
	}
	explode5 = dynamic_cast<SpriteAnimation *> (meshList[GEO_MOLE_EXPLOSION5]);
	if (explode5)
	{
		explode5->m_anim = new Animation();
		explode5->m_anim->Set(0, 80, 0, 1.f, false);
	}
	explode6 = dynamic_cast<SpriteAnimation *> (meshList[GEO_MOLE_EXPLOSION6]);
	if (explode6)
	{
		explode6->m_anim = new Animation();
		explode6->m_anim->Set(0, 80, 0, 1.f, false);
	}
	explode7 = dynamic_cast<SpriteAnimation *> (meshList[GEO_MOLE_EXPLOSION7]);
	if (explode7)
	{
		explode7->m_anim = new Animation();
		explode7->m_anim->Set(0, 80, 0, 1.f, false);
	}
	explode8 = dynamic_cast<SpriteAnimation *> (meshList[GEO_MOLE_EXPLOSION8]);
	if (explode8)
	{
		explode8->m_anim = new Animation();
		explode8->m_anim->Set(0, 80, 0, 1.f, false);
	}
	exList.push_back(explode);
	exList.push_back(explode2);
	exList.push_back(explode3);
	exList.push_back(explode4);
	exList.push_back(explode5);
	exList.push_back(explode6);
	exList.push_back(explode7);
	exList.push_back(explode8);

	//  ******************************* PARTICLES HERE  ******************************* //
	meshList[GEO_MOLE_SMOKE_PARTICLE] = MeshBuilder::GenerateQuad("smoke", Color(1,1,1), 1.f);
	meshList[GEO_MOLE_SMOKE_PARTICLE]->textureID = LoadTGA("Image//Mole_smoke.tga");

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
	for (int i = 0; i < 100; i++)
	{
		moleTypeRNG[i] = 0;
	}

	// 2 == normal mole // 3 == bronze mole // 4 == silver mole // 5 == gold mole // 6 == bomb mole // 7 == frost mole
	int randIndex = 0; 
	for (int i = 0; i < 60;)
	{
		randIndex = Math::RandIntMinMax(0, 99);
		if (moleTypeRNG[randIndex] == 0)
		{
			moleTypeRNG[randIndex] = 2;
			i++;
		}
	}
	for (int i = 0; i < 20;)
	{
		randIndex = Math::RandIntMinMax(0, 99);
		if (moleTypeRNG[randIndex] == 0)
		{
			moleTypeRNG[randIndex] = 3;
			i++;
		}
	}
	for (int i = 0; i < 10;)
	{
		randIndex = Math::RandIntMinMax(0, 99);
		if (moleTypeRNG[randIndex] == 0)
		{
			moleTypeRNG[randIndex] = 4;
			i++;
		}
	}
	for (int i = 0; i < 2;)
	{
		randIndex = Math::RandIntMinMax(0, 99);
		if (moleTypeRNG[randIndex] == 0)
		{
			moleTypeRNG[randIndex] = 5;
			i++;
		}
	}
	for (int i = 0; i < 4;)
	{
		randIndex = Math::RandIntMinMax(0, 99);
		if (moleTypeRNG[randIndex] == 0)
		{
			moleTypeRNG[randIndex] = 6;
			i++;
		}
	}
	for (int i = 0; i < 4;)
	{
		randIndex = Math::RandIntMinMax(0, 99);
		if (moleTypeRNG[randIndex] == 0)
		{
			moleTypeRNG[randIndex] = 7;
			i++;
		}
	}
	m_frontScale.Set(198, 36, 1);
	m_midScale.Set(198, 36, 1);
	m_backScale.Set(198, 36, 1);
	playMusic = false;
	m_popUpTimer = Math::RandFloatMinMax(0.5f, 1.5f);
	m_multiplier = 1;
	m_score = 0;
	m_hitCounter = 0;
	m_frostTimer = 10.f;
	m_gameTimer = 30.f;
	m_gameOver = false;
	m_frostOn = false;
	m_instructions = true;

	multiplier.Set(1, 1, 1);

	m_particleCount = 0;
	MAX_PARTICLE = 1000;

	// ******************************* INIT HAMMER THINGS HERE ******************************* //
	m_Hammer = FetchGO();
	m_Hammer->type = MoleObject::GO_HAMMER;
	m_Hammer->pos.Set(m_halfWorldWidth, m_halfWorldHeight, 5);
	m_Hammer->scale.Set(20, 20, 20);

	m_hammerMoveBT = 0.1f;

	m_hammerPosIndex = 0;
	InitHammerPosList();

	// ******************************* INIT RESULT THINGS HERE ******************************* //

	m_setOriginValues = false;
	m_setStatsToDist = false;

}

void SceneMole::Update(double dt)
{
	if (StatManager::GetInstance()->GetBool_Game(2))
	{
		ResetVars();
		StatManager::GetInstance()->SetBool_Mole(false);
	}
	SceneBase::Update(dt);
	// RESULT SCREEN STUFF
	if (m_gameOver)
	{
		Results::getInstance()->UpdateVars(dt);

		if (!m_setOriginValues && !m_setStatsToDist)
		{
			GameEndCalculations();
			StatManager::GetInstance()->SetCharsOriginalValues();
			m_setStatsToDist = true;
			m_setOriginValues = true;
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

	// GAME TIMER
	if (!m_gameOver && !m_instructions)
		m_gameTimer -= dt;
	if (m_gameTimer <= 0)
	{
		m_gameTimer = 0.f;
		m_gameOver = true;
	}
	if (m_gameTimer < 0)
	{
		m_gameOver = true;
	} 
	// FROST DEBUFF
	if (m_frostOn)
	{
		m_frostTimer -= dt;
	}
	if (m_frostTimer <= 0.f)
	{
		m_frostTimer = 10.f;
		m_frostOn = false;
	}

	// ****************************** MOVEMENT CONTROLS ****************************** //
	if (!m_instructions & !m_gameOver)
	{
		m_hammerMoveBT -= dt;
		if (Application::IsKeyPressed('W') && m_hammerMoveBT <= 0.f)
		{
			UpdateHammerPos('W');
			m_hammerMoveBT = 0.15f;
		}
		if (Application::IsKeyPressed('S') && m_hammerMoveBT <= 0.f)
		{
			UpdateHammerPos('S');
			m_hammerMoveBT = 0.15f;
		}
		if (Application::IsKeyPressed('A') && m_hammerMoveBT <= 0.f)
		{
			UpdateHammerPos('A');
			m_hammerMoveBT = 0.15f;
		}
		if (Application::IsKeyPressed('D') && m_hammerMoveBT <= 0.f)
		{
			UpdateHammerPos('D');
			m_hammerMoveBT = 0.15f;
		}
		static bool bSpaceButtonState = false;
		if (!bSpaceButtonState && Application::IsKeyPressed(VK_SPACE))
		{
			bSpaceButtonState = true;
			std::cout << "SPACE DOWN" << endl;
			if (m_frostOn)
			{
				meshList[GEO_HAMMER]->textureID = t_hammerHit_frost;
			}
			else
			{
				meshList[GEO_HAMMER]->textureID = t_hammerHit;
			}
			if (HammerCollisionCheck())
			{
				// sfx
				soundSystem.PlayASound("whack");
				cout << "hit" << endl;
				m_hitCounter++;
			}
			else
			{
				// sfx
				cout << "miss" << endl;
				m_hitCounter = 0;
			}
		}
		else if (bSpaceButtonState && !Application::IsKeyPressed(VK_SPACE))
		{
			bSpaceButtonState = false;
			std::cout << "SPACE UP" << endl;
			if (m_frostOn)
			{
				meshList[GEO_HAMMER]->textureID = t_hammerIdle_frost;
			}
			else
			{
				meshList[GEO_HAMMER]->textureID = t_hammerIdle;
			}
		}

		if (m_hitCounter >= 10 && m_hitCounter <= 19)
		{
			m_multiplier = 2;
		}
		else if (m_hitCounter >= 20 && m_hitCounter <= 29)
		{
			m_multiplier = 4;
		}
		else if (m_hitCounter >= 30)
		{
			m_multiplier = 8;
		}
		else
		{
			m_multiplier = 1;
		}

		UpdateMoles(dt);
		UpdateParticles(dt);
		UpdateAnimations(dt);

		if (m_multiplier == 2)
		{
			multiplier.Set(0.941f, 0.969f, 0.157f);
		}
		else if (m_multiplier == 4)
		{
			multiplier.Set(0.969f, 0.604f, 0.157f);
		}
		else if (m_multiplier == 8)
		{
			multiplier.Set(1, 0.141f, 0.141f);
		}
		else
		{
			multiplier.Set(1, 1, 1);
		}
	}
	else
	{
		static bool bSpaceButtonState = false;
		if (!bSpaceButtonState && Application::IsKeyPressed(VK_SPACE))
		{
			bSpaceButtonState = true;
			std::cout << "SPACE DOWN" << endl;
			StatManager::GetInstance()->SetPrevGame(2);
		}
		else if (bSpaceButtonState && !Application::IsKeyPressed(VK_SPACE))
		{
			bSpaceButtonState = false;
			m_instructions = false;
			playMusic = true;
			std::cout << "SPACE UP" << endl;
		}
	}
	if (playMusic)
	{
		soundSystem.playWaMoleMusic();
		playMusic = false;
	}
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
	//if (m_particleCount < MAX_PARTICLE)
	//{
	//	Particles* particle = getParticle();
	//	particle->type = ParticleObject_TYPE::P_ParticleTest;
	//	particle->scale.Set(2, 2, 2);
	//	particle->vel.Set(Math::RandFloatMinMax(0, 0.2f), Math::RandFloatMinMax(0, 0.2f), 0.0f);
	//	//particle->rotationSpeed = Math::RandFloatMinMax(20.f, 40.f);
	//	particle->pos.Set(Math::RandFloatMinMax(0, m_worldWidth), 0, 0);
	//	particle->lifeTime = 4.4f;
	//}
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
			if (particle->type == ParticleObject_TYPE::P_MOLE_SMOKE)
			{
				particle->vel *= 0.99f;
				particle->scale *= 0.99f;
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
	case ParticleObject_TYPE::P_MOLE_SMOKE:
		modelStack.PushMatrix();
		modelStack.Translate(particle->pos.x, particle->pos.y, particle->pos.z);
		modelStack.Rotate(particle->rotation, 0, 0, 1);
		modelStack.Scale(particle->scale.x, particle->scale.y, particle->scale.z);
		RenderMesh(meshList[GEO_MOLE_SMOKE_PARTICLE], false);
		modelStack.PopMatrix();
		break;
	default:
		cout << "Found NULL Particle" << endl;
		break;
	}

}

void SceneMole::RenderAnimation()
{
	for (unsigned int i = 0; i < exList.size(); i++)
	{
		if (exList[i]->m_anim->animActive)
		{
			modelStack.PushMatrix();
			modelStack.Translate(m_hammerPosList[i].x, m_hammerPosList[i].y, 0);
			modelStack.Scale(25, 25, 20);
			RenderMesh(meshList[GEO_MOLE_EXPLOSION + (SceneBase::GEOMETRY_TYPE)i], false);
			modelStack.PopMatrix();

		}
	}
}

void SceneMole::UpdateAnimations(double dt)
{
	for (unsigned int i = 0; i < exList.size(); i++)
	{
		if (exList[i]->m_anim->animActive)
		{
			exList[i]->Update(dt);
		}
	}
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
	if (m_instructions)
	{
		modelStack.PushMatrix();
		modelStack.Translate(m_halfWorldWidth, m_halfWorldHeight, 0);
		modelStack.Scale(70, 70, 1);
		RenderMesh(meshList[GEO_MOLE_INSTRUCT], false);
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		modelStack.Translate(m_halfWorldWidth - m_eightWorldWidth, m_sixthWorldHeight / 2, 0);
		modelStack.Scale(3, 3, 3);
		RenderText(meshList[GEO_GAMEFONT], "Hit Space to Start", Color(1, 1, 1));
		modelStack.PopMatrix();
	}

	if (!m_gameOver && !m_instructions)
	{
		RenderMachine();
		RenderUI();
		for (unsigned int i = 0; i < m_particleList.size(); i++)
		{
			if (m_particleList[i]->active)
			{
				RenderParticles(m_particleList[i]);
			}
		}
		RenderAnimation();
		RenderGO(m_Hammer);
	}
	if (m_gameOver)
	{
		Results::getInstance()->RenderResults(m_score, m_grade);
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
		RenderMesh(meshList[GEO_MOLE], false);
		modelStack.PopMatrix();
		break;
	case MoleObject::GO_MOLE_BRONZE:
		modelStack.PushMatrix();
		modelStack.Translate(go->pos.x, go->pos.y + go->mole_yOffset, go->pos.z);
		modelStack.Scale(go->scale.x, go->scale.y, go->scale.z);
		RenderMesh(meshList[GEO_MOLE_BRONZE], false);
		modelStack.PopMatrix();
		break;
	case MoleObject::GO_MOLE_SILVER:
		modelStack.PushMatrix();
		modelStack.Translate(go->pos.x, go->pos.y + go->mole_yOffset, go->pos.z);
		modelStack.Scale(go->scale.x, go->scale.y, go->scale.z);
		RenderMesh(meshList[GEO_MOLE_SILVER], false);
		modelStack.PopMatrix();
		break;
	case MoleObject::GO_MOLE_GOLD:
		modelStack.PushMatrix();
		modelStack.Translate(go->pos.x, go->pos.y + go->mole_yOffset, go->pos.z);
		modelStack.Scale(go->scale.x, go->scale.y, go->scale.z);
		RenderMesh(meshList[GEO_MOLE_GOLD], false);
		modelStack.PopMatrix();
		break;
	case MoleObject::GO_MOLE_BOMB:
		modelStack.PushMatrix();
		modelStack.Translate(go->pos.x, go->pos.y + go->mole_yOffset, go->pos.z);
		modelStack.Scale(go->scale.x, go->scale.y, go->scale.z);
		RenderMesh(meshList[GEO_MOLE_BOMB], false);
		modelStack.PopMatrix();
		break;
	case MoleObject::GO_MOLE_FROST:
		modelStack.PushMatrix();
		modelStack.Translate(go->pos.x, go->pos.y + go->mole_yOffset, go->pos.z);
		modelStack.Scale(go->scale.x, go->scale.y, go->scale.z);
		RenderMesh(meshList[GEO_MOLE_FROST], false);
		modelStack.PopMatrix();
		break;
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

void SceneMole::UpdateHammerPos(char wasd)
{
	//double x, y;
	//Application::GetCursorPos(&x, &y);
	//int w = Application::GetWindowWidth();
	//int h = Application::GetWindowHeight();
	//float posX = static_cast<float>(x) / w * m_worldWidth;
	//float posY = (h - static_cast<float>(y)) / h * m_worldHeight;
	//
	//m_Hammer->pos.Set(posX, posY, 5);
	switch (wasd)
	{
	case 'W':
		if (m_hammerPosIndex < 4) // Hammer at top row go down 
		{
			m_hammerPosIndex += 4;
		}
		else
		{
			m_hammerPosIndex -= 4;
		}
		break;
	case 'S':
		if (m_hammerPosIndex < 4)
		{
			m_hammerPosIndex += 4;
		}
		else
		{
			m_hammerPosIndex -= 4;
		}
		break;
	case 'A':
		if (m_hammerPosIndex == 0 || m_hammerPosIndex == 4)
		{
			m_hammerPosIndex += 3;
		}
		else
		{
			m_hammerPosIndex--;
		}
		break;
	case 'D':
		if (m_hammerPosIndex == 3 || m_hammerPosIndex == 7)
		{
			m_hammerPosIndex -= 3;
		}
		else
		{
			m_hammerPosIndex++;
		}
		break;
	default:
		break;
	}

	m_Hammer->pos = m_hammerPosList[m_hammerPosIndex];
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
				// do rng stuff here for mole type
				int randMoleType = Math::RandIntMinMax(0, 99);
				m_moleListTotal[randMole]->type = MoleObject::GO_MOLE_BOMB;//(MoleObject::MOLEOBJECT_TYPE)(moleTypeRNG[randMoleType]);
				break;
			}
		}
		if (m_gameTimer > 15.f)
			m_popUpTimer = Math::RandFloatMinMax(0.5f, 1.f);
		else
			m_popUpTimer = Math::RandFloatMinMax(0.3f, 0.6f);
	}

	// Check their lifetime
	for (unsigned int i = 0; i < m_moleListTotal.size(); i++)
	{
		if (m_moleListTotal[i]->active)
		{
			m_moleListTotal[i]->mole_lifeTime -= dt;
			if (m_moleListTotal[i]->mole_lifeTime <= 0.f) // When fail to hit in time
			{
				m_moleListTotal[i]->active = false;
				m_moleListTotal[i]->mole_hit = true;
				if (m_moleListTotal[i]->type == MoleObject::GO_MOLE ||
					m_moleListTotal[i]->type == MoleObject::GO_MOLE_BRONZE || 
					m_moleListTotal[i]->type == MoleObject::GO_MOLE_SILVER || 
					m_moleListTotal[i]->type == MoleObject::GO_MOLE_GOLD)
				{
					m_hitCounter = 0;
				}
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
	RenderTextOnScreen(meshList[GEO_GAMEFONT], ss.str(), Color(1, 1, 1), 3, 25, 6);

	ss.clear();
	ss.str("");
	ss.precision(2);
	ss << "Time Left: " << m_gameTimer;
	RenderTextOnScreen(meshList[GEO_GAMEFONT], ss.str(), Color(1, 1, 1), 3, 18, 2);

	ss.clear();
	ss.str("");
	ss << "Combo: " << m_hitCounter;
	modelStack.PushMatrix();
	modelStack.Translate(m_halfWorldWidth - m_eightWorldWidth, m_worldHeight - 5, 0);
	modelStack.Scale(5, 5, 5);
	RenderText(meshList[GEO_GAMEFONT], ss.str(), Color(1, 1, 1));
	modelStack.PopMatrix();

	ss.clear();
	ss.str("");
	ss << "x" << m_multiplier;
	modelStack.PushMatrix();
	modelStack.Translate(m_worldWidth - m_eightWorldWidth / 2, m_worldHeight - 5, 0);
	modelStack.Scale(10, 10, 10);
	RenderText(meshList[GEO_GAMEFONT], ss.str(), multiplier);
	modelStack.PopMatrix();

}

void SceneMole::GameEndCalculations() // Setting the stats and other stuff
{
	if (m_score >= 100000)
	{
		m_grade = 'S';
		StatManager::GetInstance()->UpdateChar01F(StatManager::GetInstance()->GetChar01().m_frustration -20);
		StatManager::GetInstance()->UpdateChar01M(StatManager::GetInstance()->GetChar01().m_motivation + 20);
		StatManager::GetInstance()->UpdateChar02F(StatManager::GetInstance()->GetChar02().m_frustration -20);
		StatManager::GetInstance()->UpdateChar02M(StatManager::GetInstance()->GetChar02().m_motivation + 20);
		StatManager::GetInstance()->UpdateChar03F(StatManager::GetInstance()->GetChar03().m_frustration -20);
		StatManager::GetInstance()->UpdateChar03M(StatManager::GetInstance()->GetChar03().m_motivation +20);
		StatManager::GetInstance()->UpdateChar04F(StatManager::GetInstance()->GetChar04().m_frustration -20);
		StatManager::GetInstance()->UpdateChar04M(StatManager::GetInstance()->GetChar04().m_motivation + 20);
		Results::getInstance()->InitStatsToDist(35);
	}
	else if (m_score >= 70000 && m_score < 100000)
	{
		m_grade = 'A';
		Results::getInstance()->InitStatsToDist(25);

	}
	else if (m_score >= 60000 && m_score < 70000)
	{
		m_grade = 'B';
		Results::getInstance()->InitStatsToDist(20);
	}
	else if (m_score >= 40000 && m_score < 50000)
	{
		m_grade = 'C';
		Results::getInstance()->InitStatsToDist(15);
	}
	else if (m_score >= 10000 && m_score < 40000)
	{
		m_grade = 'D';
		Results::getInstance()->InitStatsToDist(10);
	}
	else
	{
		m_grade = 'F';
		StatManager::GetInstance()->UpdateChar01F(StatManager::GetInstance()->GetChar01().m_frustration + 10);
		StatManager::GetInstance()->UpdateChar01M(StatManager::GetInstance()->GetChar01().m_motivation -10);
		StatManager::GetInstance()->UpdateChar02F(StatManager::GetInstance()->GetChar02().m_frustration + 10);
		StatManager::GetInstance()->UpdateChar02M(StatManager::GetInstance()->GetChar02().m_motivation -10);
		StatManager::GetInstance()->UpdateChar03F(StatManager::GetInstance()->GetChar03().m_frustration +10);
		StatManager::GetInstance()->UpdateChar03M(StatManager::GetInstance()->GetChar03().m_motivation -10);
		StatManager::GetInstance()->UpdateChar04F(StatManager::GetInstance()->GetChar04().m_frustration + 10);
		StatManager::GetInstance()->UpdateChar04M(StatManager::GetInstance()->GetChar01().m_motivation -10);
	}

}

void SceneMole::ResetVars()
{
	m_popUpTimer = Math::RandFloatMinMax(0.5f, 1.5f);
	m_multiplier = 1;
	m_score = 0;
	m_hitCounter = 0;
	m_frostTimer = 10.f;
	m_gameTimer = 90.f;
	m_gameOver = false;
	m_frostOn = false;
	m_instructions = true;

	multiplier.Set(1, 1, 1);
	m_hammerPosIndex = 0;

	m_setOriginValues = false;
	m_setStatsToDist = false;
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

void SceneMole::InitHammerPosList()
{
	//for (unsigned int i = 0; i < 8; i++)
	//{
	//	Vector3 temp;
	//	if (i < 4) // Top row
	//	{
	//		temp.Set(m_eightWorldWidth + (i * m_quarterWorldWidth), (m_worldHeight - m_sixthWorldHeight) - 35, -1);
	//	}
	//	else // Bottom Row
	//	{
	//		temp.Set(m_eightWorldWidth + (i * m_quarterWorldWidth), (m_worldHeight - 3 * m_sixthWorldHeight) - 35, -1);
	//	}
	//	m_hammerPosList.push_back(temp);
	//}


	for (unsigned int i = 0; i < m_moleListTop.size(); i++)
	{
		Vector3 temp;
		temp = m_moleListTop[i]->pos;
		temp.y += 30.f;
		m_hammerPosList.push_back(temp);
	}
	for (unsigned int i = 0; i < m_moleListBot.size(); i++)
	{
		Vector3 temp;
		temp = m_moleListBot[i]->pos;
		temp.y += 30.f;
		m_hammerPosList.push_back(temp);
	}


	m_Hammer->pos = m_hammerPosList[m_hammerPosIndex];
}

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
					m_moleListTotal[i]->mole_hit = true;
					m_moleListTotal[i]->active = false;
					int addToScore = 0;
					switch (m_moleListTotal[i]->type)
					{
					case MoleObject::GO_MOLE:
						addToScore = m_moleListTotal[i]->mole_lifeTime * 100 * m_multiplier;
						break;
					case MoleObject::GO_MOLE_BRONZE:
						addToScore += m_moleListTotal[i]->mole_lifeTime * 100 * m_multiplier * 1.5;
						break;
					case MoleObject::GO_MOLE_SILVER:
						addToScore += m_moleListTotal[i]->mole_lifeTime * 100 * m_multiplier * 2.f;
						break;
					case MoleObject::GO_MOLE_GOLD:
						addToScore += m_moleListTotal[i]->mole_lifeTime * 100 * m_multiplier * 5.f;
						break;
					case MoleObject::GO_MOLE_BOMB:
					{
						m_score /= 2;
						m_hitCounter = 0;
						exList[m_hammerPosIndex]->m_anim->Set(0, 80, 0, 2.f, true);
						break;
					}
					case MoleObject::GO_MOLE_FROST:
						m_frostOn = true;
						addToScore = 0;
						m_score -= m_score / 5;
						m_hitCounter = 0;
						break;
					default:
						break;
					}
					if (m_frostOn)
					{
						addToScore /= 2;
						m_score += addToScore;
					}
					else
					{
						m_score += addToScore;
					}
					cout << addToScore << endl;
					if (m_moleListTotal[i]->type != MoleObject::GO_MOLE_BOMB && m_moleListTotal[i]->type != MoleObject::GO_MOLE_FROST)
					{
						for (int i = 0; i < 50; i++)
						{
							if (m_particleCount < MAX_PARTICLE)
							{
								Particles* temp = getParticle();
								temp->type = ParticleObject_TYPE::P_MOLE_SMOKE;
								temp->pos = m_Hammer->pos;
								temp->pos.y -= 5.f;
								temp->lifeTime = 1.f;
								temp->scale.Set(3, 3, 3);
								temp->rotation = Math::RandFloatMinMax(45.f, 135.f);
								temp->rotationSpeed = Math::RandFloatMinMax(110.f, 220.f);
								temp->vel.Set(Math::RandFloatMinMax(-15.f, 15.f), Math::RandFloatMinMax(-15.f, 15.f), 0);
								temp->active = true;
							}
						}

					}
					//m_moleListTotal[i]->mole_lifeTime = 0.f;
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
