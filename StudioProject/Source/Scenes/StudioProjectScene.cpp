#include "StudioProjectScene.h"
#include "GL\glew.h"
#include "../Application.h"
#include <sstream>
#include "../Rendering/LoadTGA.h"
#include "../Rendering/MeshBuilder.h"
#include "../Rendering/Particles.h"

StudioProjectScene::StudioProjectScene()
{

}

StudioProjectScene::~StudioProjectScene()
{
}

void StudioProjectScene::Init()
{
	SceneBase::Init();

	//Calculating aspect ratio
	m_worldHeight = 200.f;
	m_worldWidth = m_worldHeight * (float)Application::GetWindowWidth() / Application::GetWindowHeight();
	m_worldWidthDiv8 = (m_worldWidth / 4) / 2;
	GameArea.Set(960, 440, 0);
	StatsArea.Set(960, 100, 0);
	mTimer = 2.f;
	//Variables here
	m_speed = 1.f;
	Math::InitRNG();
	m_eventTimer = 10;//Math::RandFloatMinMax(20.0f, 40.f);
	b_transitioning = false;
	playMusic = false;
	meshList[GEO_QUAD] = MeshBuilder::GenerateQuad("test", Color(1, 1, 1), 1.f);
	meshList[GEO_BACKGROUND] = MeshBuilder::GenerateQuad("testbg", Color(1, 1, 1), 1);
	meshList[GEO_BACKGROUND]->textureID = LoadTGA("Image//BGTest.tga");
	meshList[GEO_PARTICLE_TEST] = MeshBuilder::GenerateQuad("testParticle", Color(1, 1, 1), 1.f);
	meshList[GEO_PARTICLE_TEST]->textureID = LoadTGA("Image//balloon.tga");
	meshList[GEO_ARROW] = MeshBuilder::GenerateQuad("arrow", Color(1, 1, 1), 1.f);
	meshList[GEO_ARROW]->textureID = LoadTGA("Image//Arrow.tga");
	meshList[GEO_SPRITE_ANIMATION] = MeshBuilder::GenerateSpriteAnimation("test", 1, 4);
	meshList[GEO_SPRITE_ANIMATION]->textureID = LoadTGA("Image//Idle_anim.tga");
	meshList[GEO_WALKLEFT] = MeshBuilder::GenerateSpriteAnimation("char1walkleft", 1, 4);
	meshList[GEO_WALKLEFT]->textureID = LoadTGA("Image//Walk_animLeft2.tga");
	meshList[GEO_WALKRIGHT] = MeshBuilder::GenerateSpriteAnimation("char1walkright", 1, 4);
	meshList[GEO_WALKRIGHT]->textureID = LoadTGA("Image//Walk_animRight2.tga");
	meshList[GEO_SPRITE_TEST2] = MeshBuilder::GenerateSpriteAnimation("test2", 1, 6);
	meshList[GEO_SPRITE_TEST2]->textureID = LoadTGA("Image//Idle_anim2.tga");
	meshList[GEO_TELEVISION] = MeshBuilder::GenerateQuad("Television", Color(1, 1, 1), 1.f);
	meshList[GEO_TELEVISION]->textureID = LoadTGA("Image//Television.tga");
	meshList[GEO_BORDER] = MeshBuilder::GenerateQuad("Border", Color(1, 1, 1), 1.f);
	meshList[GEO_BORDER]->textureID = LoadTGA("Image//Border.tga");
	meshList[GEO_TANK_CURSOR] = MeshBuilder::GenerateQuad("Cursor", Color(1, 1, 1), 1.f);
	meshList[GEO_TANK_CURSOR]->textureID = LoadTGA("Image//Tank_Cursor.tga");
	meshList[GEO_TANK_CURSOR_ALTERNATE] = MeshBuilder::GenerateQuad("Cursor	Alternate", Color(1, 1, 1), 1.f);
	meshList[GEO_TANK_CURSOR_ALTERNATE]->textureID = LoadTGA("Image//Tank_Cursor_Alternate.tga");
	meshList[GEO_MAIN_USE] = MeshBuilder::GenerateQuad("Use", Color(1, 1, 1), 1.f);
	meshList[GEO_MAIN_USE]->textureID = LoadTGA("Image//Main_Use.tga");
	meshList[GEO_MAIN_STOP] = MeshBuilder::GenerateQuad("Stop", Color(1, 1, 1), 1.f);
	meshList[GEO_MAIN_STOP]->textureID = LoadTGA("Image//Main_Stop.tga");
	meshList[GEO_MAIN_CONTINUE] = MeshBuilder::GenerateQuad("Continue", Color(1, 1, 1), 1.f);
	meshList[GEO_MAIN_CONTINUE]->textureID = LoadTGA("Image//Main_Continue.tga");


	Mtx44 projection;
	projection.SetToOrtho(0, m_worldWidth, 0, m_worldHeight, -10, 10);
	projectionStack.LoadMatrix(projection);
	soundSystem.AddSound("mainMusic", "Sounds//MainTheme.mp3");
	//Particles
	m_particleCount = 0;
	MAX_PARTICLE = 2000;
	m_Gravity.Set(0, -9.8, 0);
	m_Count = 4;
	for (unsigned i = 0; i < 10;++i)
	{
		Particles *particle = new Particles(ParticleObject_TYPE::P_ParticleTest);
		m_particleList.push_back(particle);
	}

	for (int i = 0; i < 4; ++i)
	{
		ScreenSplit[i] = new Screen(static_cast<Screen::SCREEN_AREA>(i));
		ScreenSplit[i]->Init(m_worldWidth, m_worldHeight);
	}

	ScreenSplit[0]->UseItem->pos.Set(m_worldWidth * 0.45f, m_worldHeight * 0.55f, 0);
	ScreenSplit[1]->UseItem->pos.Set(m_worldWidth * 0.95f, m_worldHeight * 0.55f, 0);
	ScreenSplit[2]->UseItem->pos.Set(m_worldWidth * 0.45f, m_worldHeight * 0.05f, 0);
	ScreenSplit[3]->UseItem->pos.Set(m_worldWidth * 0.95f, m_worldHeight * 0.05f, 0);

	currentChar = ScreenSplit[0]->Character;

	SpriteAnimation *sa = dynamic_cast<SpriteAnimation *>(meshList[GEO_SPRITE_ANIMATION]);
	if (sa)
	{
		sa->m_anim = new Animation();
		sa->m_anim->Set(0, 4, 0, 1.f, true);
	}
	SpriteAnimation *sa2 = dynamic_cast<SpriteAnimation *>(meshList[GEO_SPRITE_TEST2]);
	if (sa2)
	{
		sa2->m_anim = new Animation();
		sa2->m_anim->Set(0, 6, 0, 2.f, true);
	}

	SpriteAnimation *walkLeft = dynamic_cast<SpriteAnimation *>(meshList[GEO_WALKLEFT]);
	if (walkLeft)
	{
		walkLeft->m_anim = new Animation();
		walkLeft->m_anim->Set(0, 4, 0, 1.f, true);
	}
	SpriteAnimation *walkRight = dynamic_cast<SpriteAnimation *>(meshList[GEO_WALKRIGHT]);
	if (walkRight)
	{
		walkRight->m_anim = new Animation();
		walkRight->m_anim->Set(0, 4, 0, 1.f, true);
	}

	color = 1.0f;


	meshList[GEO_CHARONEFRUST] = MeshBuilder::GenerateQuad("charOneFrustration", Color(1, 0, 0), 1.f);
	meshList[GEO_CHARONEMOTIVE] = MeshBuilder::GenerateQuad("CharOneMotivation", Color(1, 1, 0), 1.f);
	meshList[GEO_CHARONEREST] = MeshBuilder::GenerateQuad("CharOneRest", Color(1, 0, 1), 1.f);
	meshList[GEO_CHARONEWD] = MeshBuilder::GenerateQuad("CharOneWorkDone", Color(0, 1, 1),1.f);

	meshList[GEO_CHARTWOFRUST] = MeshBuilder::GenerateQuad("charTwoFrustration", Color(1, 0, 0), 1.f);
	meshList[GEO_CHARTWOMOTIVE] = MeshBuilder::GenerateQuad("CharTwoMotivation", Color(1, 1, 0),1.f);
	meshList[GEO_CHARTWOREST] = MeshBuilder::GenerateQuad("CharTwoRest", Color(1, 0, 1),1.f);
	meshList[GEO_CHARTWOWD] = MeshBuilder::GenerateQuad("CharTwoWorkDone", Color(0, 1, 1),1.f);

	meshList[GEO_CHARTHREEFRUST] = MeshBuilder::GenerateQuad("charThreeFrustration", Color(1, 0, 0),1.f);
	meshList[GEO_CHARTHREEMOTIVE] = MeshBuilder::GenerateQuad("CharThreeMotivation", Color(1, 1, 0),1.f);
	meshList[GEO_CHARTHREEREST] = MeshBuilder::GenerateQuad("CharThreeRest", Color(1, 0, 1),1.f);
	meshList[GEO_CHARTHREEWD] = MeshBuilder::GenerateQuad("CharThreeWorkDone", Color(0, 1, 1),1.f);

	meshList[GEO_CHARFOURFRUST] = MeshBuilder::GenerateQuad("charThreeFrustration", Color(1, 0, 0),1.f);
	meshList[GEO_CHARFOURMOTIVE] = MeshBuilder::GenerateQuad("CharThreeMotivation", Color(1, 1, 0),1.f);
	meshList[GEO_CHARFOURREST] = MeshBuilder::GenerateQuad("CharThreeRest", Color(1, 0, 1), 1.f);
	meshList[GEO_CHARFOURWD] = MeshBuilder::GenerateQuad("CharFourWorkDone", Color(0, 1, 1),1.f);

	phase = 4;
	prevlevel = 0;
	currentlevel = 0;
	SceneState = S_GAME;
	
	Continue = new MenuObject(MenuObject::M_CONTINUE, Vector3(40, 40, 1));
	Continue->pos = Vector3(m_worldWidth * 0.9f, m_worldHeight * 0.1f, 0);
	Continue->active = true;
}
void StudioProjectScene::Update(double dt)
{
	SceneBase::Update(dt);

	//Calculating aspect ratio
	m_worldHeight = 200.f;
	m_worldWidth = m_worldHeight * (float)Application::GetWindowWidth() / Application::GetWindowHeight();

	double x, y;
	Application::GetCursorPos(&x, &y);
	int w = Application::GetWindowWidth();
	int h = Application::GetWindowHeight();
	v_mousepos = Vector3(static_cast<float>(x) / (w / m_worldWidth), (h - static_cast<float>(y)) / (h / m_worldHeight), 0.0f);

	m_eventTimer -= dt;

	switch (SceneState)
	{
	case S_GAME:
	{
		UpdateGame(dt);
		break;
	}
	case S_LEVELTRANSITION:
	{
		soundSystem.stopSheep();
		UpdateLevelTransition(dt);
		break;
	}
	default:
	{
		break;
	}
	}

	if (m_eventTimer < 0)
	{
		if (color >= 0)
		{
			color -= dt;
		}
	}
	if (m_eventTimer < -2)
	{
		phase++;
		switch (phase)
		{
		case 1:
		{
			m_eventTimer = 10.f;
			break;
		}
		case 5:
		{
			SceneState = S_LEVELTRANSITION;
			phase = 0;
			break;
		}
		default:
		{
			prevlevel = currentlevel;
			currentlevel = Math::RandIntMinMax(1, 5);
			while (currentlevel == prevlevel)
			{
				currentlevel = Math::RandIntMinMax(1, 5);
			}
			Application::setScene(currentlevel);
			m_eventTimer = Math::RandFloatMinMax(20.0f, 40.f);
			mTimer = 2.f;
			break;
		}
		}

	}
	UpdateParticles(dt);
	//cout << "Event Timer : " << m_eventTimer << endl;
}

void StudioProjectScene::UpdateGame(double dt)
{
	ScreenSplit[0]->UseItem->pos.Set(m_worldWidth * 0.45f, m_worldHeight * 0.55f, 0);
	ScreenSplit[1]->UseItem->pos.Set(m_worldWidth * 0.95f, m_worldHeight * 0.55f, 0);
	ScreenSplit[2]->UseItem->pos.Set(m_worldWidth * 0.45f, m_worldHeight * 0.05f, 0);
	ScreenSplit[3]->UseItem->pos.Set(m_worldWidth * 0.95f, m_worldHeight * 0.05f, 0);

	int w = Application::GetWindowWidth();
	int h = Application::GetWindowHeight();
	//cout << v_mousepos << endl;
	rel_mousepos = v_mousepos;
	if (v_mousepos.x <= m_worldWidth * 0.5f)
	{
		rel_mousepos.x = v_mousepos.x * 2;
		if (v_mousepos.y <= m_worldHeight * 0.5f && v_mousepos.y >= StatsArea.y / h * m_worldHeight)
		{
			rel_mousepos.y = (v_mousepos.y - StatsArea.y / h * m_worldHeight) * m_worldHeight / ((m_worldHeight / 2) - StatsArea.y / h * m_worldHeight);
			ItemObject::CurrentScreenID = ItemObject::BotL;
		}
		else if (v_mousepos.y > m_worldHeight * 0.5f + StatsArea.y / h * m_worldHeight && v_mousepos.y < m_worldHeight)
		{
			rel_mousepos.y = (v_mousepos.y - m_worldHeight * 0.5f - StatsArea.y / h * m_worldHeight) * m_worldHeight / ((m_worldHeight / 2) - StatsArea.y / h * m_worldHeight);
			ItemObject::CurrentScreenID = ItemObject::UpL;
		}
	}
	else
	{
		rel_mousepos.x = (v_mousepos.x - m_worldWidth * 0.5f) * 2;
		if (v_mousepos.y <= m_worldHeight * 0.5f && v_mousepos.y >= StatsArea.y / h * m_worldHeight)
		{
			rel_mousepos.y = (v_mousepos.y - StatsArea.y / h * m_worldHeight) * m_worldHeight / ((m_worldHeight / 2) - StatsArea.y / h * m_worldHeight);
			ItemObject::CurrentScreenID = ItemObject::BotR;
		}
		else if (v_mousepos.y > m_worldHeight * 0.5f + StatsArea.y / h * m_worldHeight && v_mousepos.y < m_worldHeight)
		{
			rel_mousepos.y = (v_mousepos.y - m_worldHeight * 0.5f - StatsArea.y / h * m_worldHeight) * m_worldHeight / ((m_worldHeight / 2) - StatsArea.y / h * m_worldHeight);
			ItemObject::CurrentScreenID = ItemObject::UpR;
		}
	}


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


	if (Application::IsKeyPressed(VK_F1))
	{
		prevChar = currentChar;
		prevChar->setState(false);
		currentChar = ScreenSplit[0]->Character;
	}
	if (Application::IsKeyPressed(VK_F2))
	{
		prevChar = currentChar;
		prevChar->setState(false);
		currentChar = ScreenSplit[1]->Character;
	}
	if (Application::IsKeyPressed(VK_F3))
	{
		prevChar = currentChar;
		prevChar->setState(false);
		currentChar = ScreenSplit[2]->Character;
	}
	if (Application::IsKeyPressed(VK_F4))
	{
		prevChar = currentChar;
		prevChar->setState(false);
		currentChar = ScreenSplit[3]->Character;
	}

	for (int i = 0; i < 4; ++i)
	{
		ScreenSplit[i]->Update(dt,v_mousepos, rel_mousepos, Vector3(10,10,1));
		switch (i)
		{
		case 0:
		{
			StatManager::GetInstance()->m_char01 = ScreenSplit[i]->Character->Statistics;
			break;
		}
		case 1:
		{
			StatManager::GetInstance()->m_char02 = ScreenSplit[i]->Character->Statistics;
			break;
		}
		case 2:
		{
			StatManager::GetInstance()->m_char03 = ScreenSplit[i]->Character->Statistics;
			break;
		}
		case 3:
		{
			StatManager::GetInstance()->m_char04 = ScreenSplit[i]->Character->Statistics;
			break;
		}
		default:
			break;
		}
	}

	currentChar->UpdateMovement(dt, m_worldWidth, m_worldHeight);


	SpriteAnimation *sa = dynamic_cast<SpriteAnimation*>(meshList[GEO_SPRITE_ANIMATION]);
	if (sa)
	{
		sa->Update(dt);
		sa->m_anim->animActive = true;

	}

	SpriteAnimation *sa2 = dynamic_cast<SpriteAnimation*>(meshList[GEO_SPRITE_TEST2]);
	if (sa2)
	{
		sa2->Update(dt);
		sa2->m_anim->animActive = true;

	}

	SpriteAnimation *walkRight = dynamic_cast<SpriteAnimation*>(meshList[GEO_WALKRIGHT]);
	if (walkRight)
	{
		walkRight->Update(dt);
		walkRight->m_anim->animActive = true;

	}
	SpriteAnimation *walkLeft = dynamic_cast<SpriteAnimation*>(meshList[GEO_WALKLEFT]);
	if (walkLeft)
	{
		walkLeft->Update(dt);
		walkLeft->m_anim->animActive = true;

	}

	for (std::vector<GameObject *>::iterator it = m_goList.begin(); it != m_goList.end(); ++it)
	{
		GameObject *go = (GameObject *)*it;
		if (go->active)
		{

		}
	}
	mTimer -= dt;
	if (mTimer < 0 && playMusic == false)
	{
		playMusic = true;
	}
	if (playMusic == true)
	{
		soundSystem.playMainMusic();
		playMusic = false;
		mTimer = 99999999999.f;
	}
}

void StudioProjectScene::UpdateLevelTransition(double dt)
{
	Continue->Update(v_mousepos);
	if (Continue->changed)
	{
		m_eventTimer = -0.01;
		SceneState = S_GAME;
		phase = 0;
	}
}

Particles* StudioProjectScene::getParticle()
{
	for (std::vector<Particles *>::iterator it = m_particleList.begin(); it != m_particleList.end();++it)
	{
		Particles *particle = (Particles *)*it;

		if (!particle->active)
		{
			particle->active = true;
			m_particleCount++;
			return particle;
		}
	}
	for (unsigned i = 0; i < 2;++i)
	{
		Particles *particle = new Particles(ParticleObject_TYPE::P_ParticleTest);
		m_particleList.push_back(particle);
	}
	m_particleCount++;
	m_particleList[m_particleList.size() - 1]->active = true;
	return m_particleList[m_particleList.size() - 1];
}

void StudioProjectScene::UpdateParticles(double dt)
{
	if (m_particleCount < MAX_PARTICLE)
	{
		Particles* particle = getParticle();
		particle->type = ParticleObject_TYPE::P_ParticleTest;
		particle->scale.Set(2, 2, 2);
		particle->vel.Set(Math::RandFloatMinMax(0,0.2f), Math::RandFloatMinMax(0,0.2f), 0.0f);
		//particle->rotationSpeed = Math::RandFloatMinMax(20.f, 40.f);
		particle->pos.Set(Math::RandFloatMinMax(0, m_worldWidth), 0, 0);
		particle->lifeTime = 8.8f;
	}
	for (std::vector<Particles *>::iterator it = m_particleList.begin(); it != m_particleList.end();++it)
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
void StudioProjectScene::RenderParticles(Particles *particle)
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


void StudioProjectScene::RenderAnimation()
{
	modelStack.PushMatrix();
	modelStack.Translate(pos.x, 50, 0);
	modelStack.Rotate(Math::RadianToDegree(atan2(camera.position.x - 0, camera.position.z - 0)), 0, 1, 0);
	modelStack.Scale(10, 10, 10);

	RenderMesh(meshList[GEO_SPRITE_ANIMATION], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(100, 50, 0);
	modelStack.Rotate(Math::RadianToDegree(atan2(camera.position.x - 0, camera.position.z - 0)), 0, 1, 0);
	modelStack.Scale(10, 10, 10);

	RenderMesh(meshList[GEO_SPRITE_TEST2], false);
	modelStack.PopMatrix();
}

void StudioProjectScene::RenderArrow()
{
	modelStack.PushMatrix();
	modelStack.Translate(currentChar->pos.x, currentChar->pos.y + 20, currentChar->pos.z);
	modelStack.Rotate(Math::RadianToDegree(atan2(camera.position.x - 0, camera.position.z - 0)), 0, 1, 0);
	modelStack.Scale(10, 10, 10);
	RenderMesh(meshList[GEO_ARROW], false);
	modelStack.PopMatrix();
}

// ********************************************** DO NOT TOUCH RENDER ANYMORE *******************************************//

void StudioProjectScene::Render()
{
	switch (SceneState)
	{
	case S_GAME:
	{
		RenderGame();
		break;
	}
	case S_LEVELTRANSITION:
	{
		RenderLevelTransition();
		break;
	}
	default:
	{
		break;
	}
	}
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
	std::ostringstream ss;
	ss.precision(3);
	ss << rel_mousepos;
	RenderTextOnScreen(meshList[GEO_TEXT], ss.str(), Color(0, 1, 0), 3, 1, 1);

	ss.str("");
	ss << v_mousepos;
	RenderTextOnScreen(meshList[GEO_TEXT], ss.str(), Color(0, 1, 0), 3, 1, 4);
	// End of Multiple viewports
}

void StudioProjectScene::RenderGame()
{
	if (m_eventTimer > 0)
	{
		glEnable(GL_SCISSOR_TEST);
		glViewport(0, StatsArea.y + GameArea.y + StatsArea.y, GameArea.x, GameArea.y);
		glScissor(0, StatsArea.y + GameArea.y + StatsArea.y, GameArea.x, GameArea.y);

		RenderScreen(ScreenSplit[0]);
		//RenderCharacter1(); // TOP LEFT

		glViewport(GameArea.x, StatsArea.y + GameArea.y + StatsArea.y, GameArea.x, GameArea.y);
		glScissor(GameArea.x, StatsArea.y + GameArea.y + StatsArea.y, GameArea.x, GameArea.y);

		RenderScreen(ScreenSplit[1]);
		//RenderCharacter2(); // TOP RIGHT

		glViewport(0, StatsArea.y, GameArea.x, GameArea.y);
		glScissor(0, StatsArea.y, GameArea.x, GameArea.y);

		RenderScreen(ScreenSplit[2]);
		//RenderCharacter3();

		glViewport(GameArea.x, StatsArea.y, GameArea.x, GameArea.y);
		glScissor(GameArea.x, StatsArea.y, GameArea.x, GameArea.y);

		RenderScreen(ScreenSplit[3]);
		//RenderCharacter4();

		// Statistics
		glViewport(0, StatsArea.y + GameArea.y, StatsArea.x, StatsArea.y);
		glScissor(0, StatsArea.y + GameArea.y, StatsArea.x, StatsArea.y);

		RenderStats(ScreenSplit[0]->Character);
		//RenderStats1();

		glViewport(StatsArea.x, StatsArea.y + GameArea.y, StatsArea.x, StatsArea.y);
		glScissor(StatsArea.x, StatsArea.y + GameArea.y, StatsArea.x, StatsArea.y);

		RenderStats(ScreenSplit[1]->Character);
		//RenderStats2();

		glViewport(0, 0, StatsArea.x, StatsArea.y);
		glScissor(0, 0, StatsArea.x, StatsArea.y);

		RenderStats(ScreenSplit[2]->Character);
		//RenderStats3();

		glViewport(StatsArea.x, 0, StatsArea.x, StatsArea.y);
		glScissor(StatsArea.x, 0, StatsArea.x, StatsArea.y);

		RenderStats(ScreenSplit[3]->Character);
		//RenderStats4();
		glDisable(GL_SCISSOR_TEST);

		//}
		glViewport(0, 0, 1920, 1080);

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

		for (int i = 0; i < 4; ++i)
		{
			RenderMenu(ScreenSplit[i]);
		}
		// Model matrix : an identity matrix (model will be at the origin)
		modelStack.LoadIdentity();
	}
	else
	{
		glViewport(0, 0, 1920, 1080);
		glClearColor(color, color, color, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

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

		//Particles
		for (std::vector<Particles *>::iterator it = m_particleList.begin(); it != m_particleList.end(); ++it)
		{
			Particles *particle = (Particles *)*it;
			if (particle->active)
			{
				RenderParticles(particle);
			}
		}
	}
}

void StudioProjectScene::RenderLevelTransition()
{
	glViewport(0, 0, 1920, 1080);
	glClearColor(0, 0, 0, 0.f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

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
	modelStack.Translate(Continue->pos);
	modelStack.Scale(Continue->scale);
	RenderMesh(meshList[GEO_MAIN_CONTINUE], false);
	modelStack.PopMatrix();

	/*std::ostringstream ss;
	ss.precision(3);
	ss << "Work Done:";
	for (int i = 0; i < )
	RenderTextOnScreen(meshList[GEO_TEXT], ss.str(), Color(0, 1, 0), 3, 1, 1);

	ss.str("");
	ss << v_mousepos;
	RenderTextOnScreen(meshList[GEO_TEXT], ss.str(), Color(0, 1, 0), 3, 1, 4);*/
}

void StudioProjectScene::RenderCharObj(CharacterObject * go)
{
	switch (go->type)
	{
	case CharacterObject::GO_CUBE:
		modelStack.PushMatrix();
		modelStack.Translate(go->pos.x, go->pos.y, go->pos.z);
		modelStack.Scale(go->scale.x, go->scale.y, go->scale.z);
		RenderMesh(meshList[GEO_QUAD], false);
		modelStack.PopMatrix();
		break;
	case CharacterObject::GO_SPRITE_TEST:
		if (go->getState() == true)
		{
			modelStack.PushMatrix();
			modelStack.Translate(go->pos.x, go->pos.y, go->pos.z);
			if (go->getDirection() == true)
			{
				modelStack.Scale(go->scale.x, go->scale.y, go->scale.z);
				RenderMesh(meshList[GEO_WALKLEFT], false);
				modelStack.PopMatrix();
			}
			else
			{
				modelStack.Scale(go->scale.x, go->scale.y, go->scale.z);
				RenderMesh(meshList[GEO_WALKRIGHT], false);
				modelStack.PopMatrix();
			}
			break;
		}
		else if (!go->getState())
		{
			modelStack.PushMatrix();
			modelStack.Translate(go->pos.x, go->pos.y, go->pos.z);
			modelStack.Scale(go->scale.x, go->scale.y, go->scale.z);
			RenderMesh(meshList[GEO_SPRITE_TEST2], false);
			modelStack.PopMatrix();
			break;
		}
	case CharacterObject::GO_TELEVISION:
		modelStack.PushMatrix();
		modelStack.Translate(go->pos.x, go->pos.y, go->pos.z);
		modelStack.Scale(go->scale.x, go->scale.y, go->scale.z);
		RenderMesh(meshList[GEO_TELEVISION], false);
		modelStack.PopMatrix();
		break;

	default:
		break;
	}
}

void StudioProjectScene::RenderItemObj(ItemObject * go)
{
	switch (go->type)
	{
	case ItemObject::I_TELEVISION:
		modelStack.PushMatrix();
		modelStack.Translate(go->pos);
		modelStack.PushMatrix();
		modelStack.Scale(go->scale);
		RenderMesh(meshList[GEO_TELEVISION], false);
		modelStack.PopMatrix();
		if (go->bounded)
		{
			modelStack.PushMatrix();
			modelStack.Scale(go->scale * 1.1f);
			RenderMesh(meshList[GEO_BORDER], false);
			modelStack.PopMatrix();
		}
		modelStack.PopMatrix();
		break;
	default:
		break;
	}
}

GameObject * StudioProjectScene::FetchGO()
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
		m_goList.push_back(new GameObject);
	}
	m_goList[m_goList.size() - 1]->active = true;
	return m_goList[m_goList.size() - 1];
}

void StudioProjectScene::Exit()
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

void StudioProjectScene::RenderBG()
{
	modelStack.PushMatrix();
	modelStack.Translate(m_worldWidth * 0.5f, m_worldHeight * 0.5f, 0);
	modelStack.Scale(Application::GetWindowWidth() / 5, Application::GetWindowHeight() / 5, 1);
	RenderMesh(meshList[GEO_BACKGROUND], false);
	modelStack.PopMatrix();
}

void StudioProjectScene::RenderScreen(Screen* ScreenSplit)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// BackGround
	RenderBG();

	// Props
	if (currentChar == ScreenSplit->Character)
	{
		RenderArrow();
	}
	for (int i = 0; i < ScreenSplit->m_itemList.size(); ++i)
	{
		if (ScreenSplit->m_itemList[i]->active)
		{
			RenderItemObj(ScreenSplit->m_itemList[i]);
		}
	}
	// Character
	if (ScreenSplit->Character->active)
		RenderCharObj(ScreenSplit->Character);
}

void StudioProjectScene::RenderStats(CharacterObject* Character)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	modelStack.PushMatrix();
	modelStack.Translate(m_worldWidthDiv8 + 10 + Character->Statistics.m_frustration / 2, m_worldHeight / 2, 0);
	modelStack.Scale(Character->Statistics.m_frustration, 10, 1);
	RenderMesh(meshList[GEO_CHARONEFRUST], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(m_worldWidthDiv8 + 15 + Character->Statistics.m_motivation / 2, m_worldHeight / 2 + 15, 0);
	modelStack.Scale(Character->Statistics.m_motivation, 10, 1);
	RenderMesh(meshList[GEO_CHARONEMOTIVE], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(m_worldWidthDiv8 + 5 + Character->Statistics.m_rest / 2, m_worldHeight / 2 - 15, 0);
	modelStack.Scale(Character->Statistics.m_rest, 10, 1);
	RenderMesh(meshList[GEO_CHARONEREST], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(m_worldWidthDiv8 + Character->Statistics.m_workDone / 2, m_worldHeight / 2 - 30, 0);
	modelStack.Scale(Character->Statistics.m_workDone, 10, 1);
	RenderMesh(meshList[GEO_CHARONEWD], false);
	modelStack.PopMatrix();
}

void StudioProjectScene::RenderMenu(Screen* ScreenSplit)
{
	modelStack.PushMatrix();
	modelStack.Translate(ScreenSplit->UseItem->pos);
	modelStack.Scale(ScreenSplit->UseItem->scale);
	if (ScreenSplit->Character->currentItem)
	{
		if (ScreenSplit->UseItem->changed)
		{
			RenderMesh(meshList[GEO_MAIN_STOP], false);
		}
		else
		{
			RenderMesh(meshList[GEO_MAIN_USE], false);
		}
	}
	modelStack.PopMatrix();
}
