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
	m_worldHeight = 100.f;
	m_worldWidth = m_worldHeight * (float)Application::GetWindowWidth() / Application::GetWindowHeight();
	m_worldWidthDiv8 = (m_worldWidth / 4) / 2;

	//Variables here
	m_speed = 1.f;
	Math::InitRNG();
	m_eventTimer = Math::RandFloatMinMax(20.0f, 40.f);
	b_transitioning = false;

	/*meshList[GEO_AXES] = MeshBuilder::GenerateAxes("reference", 1000, 1000, 1000);
	meshList[GEO_TEXT] = MeshBuilder::GenerateText("text", 16, 16);
	meshList[GEO_TEXT]->textureID = LoadTGA("Image//calibri.tga");
	meshList[GEO_BACKGROUND] = MeshBuilder::GenerateQuad("testbg", Color(1, 1, 1), 1);
	meshList[GEO_BACKGROUND]->textureID = LoadTGA("Image//BGTest.tga");
	meshList[GEO_CUBE] = MeshBuilder::GenerateCube("cube", Color(1, 1, 1), 1.f);
	meshList[GEO_QUAD] = MeshBuilder::GenerateQuad("test", Color(1, 1, 1), 1.f);

	meshList[GEO_PARTICLE_TEST] = MeshBuilder::GenerateQuad("testParticle", Color(1, 1, 1), 1.f);
	meshList[GEO_PARTICLE_TEST]->textureID = LoadTGA("Image//balloon.tga");
	meshList[GEO_ARROW] = MeshBuilder::GenerateQuad("arrow", Color(1, 1, 1), 1.f);
	meshList[GEO_ARROW]->textureID = LoadTGA("Image//Arrow.tga");
	meshList[GEO_SPRITE_ANIMATION] = MeshBuilder::GenerateSpriteAnimation("test", 1, 4);
	meshList[GEO_SPRITE_ANIMATION]->textureID = LoadTGA("Image//Idle_anim.tga");
	meshList[GEO_WALKLEFT] = MeshBuilder::GenerateSpriteAnimation("char1walkleft", 1, 4);
	meshList[GEO_WALKLEFT]->textureID = LoadTGA("Image//Walk_animLeft.tga");
	meshList[GEO_WALKRIGHT] = MeshBuilder::GenerateSpriteAnimation("char1walkright", 1, 4);
	meshList[GEO_WALKRIGHT]->textureID = LoadTGA("Image//Walk_animRight.tga");
	meshList[GEO_SPRITE_TEST2] = MeshBuilder::GenerateSpriteAnimation("test2", 1, 6);
	meshList[GEO_SPRITE_TEST2]->textureID = LoadTGA("Image//Idle_anim2.tga");
	meshList[GEO_FROG_JUMP] = MeshBuilder::GenerateSpriteAnimation("frog_Jump", 1, 5);
	meshList[GEO_FROG_JUMP]->textureID = LoadTGA("Image//Frog_Jump.tga");
	*/

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
	meshList[GEO_FROG_JUMP] = MeshBuilder::GenerateSpriteAnimation("frog_Jump", 1, 5);
	meshList[GEO_FROG_JUMP]->textureID = LoadTGA("Image//Frog_Jump.tga");
	meshList[GEO_FRUSTRATION] = MeshBuilder::GenerateQuad("frustration", Color(1, 0, 0), 1.f);

	//meshList[GEO_FRUSTRATION] = MeshBuilder::GenerateQuad("frustration", Color(1, 0, 0), 1.f);

	Mtx44 projection;
	projection.SetToOrtho(0, m_worldWidth, 0, m_worldHeight, -10, 10);
	projectionStack.LoadMatrix(projection);



	/*************************************************************Testing*************************************************************/
	//TestCube1 = FetchGO();
	//TestCube1->type = GameObject::GO_SPRITE_TEST;
	//TestCube1->pos.Set(m_worldWidth / 4 - m_worldWidthDiv8, m_worldHeight / 2, 5);
	//TestCube1->setDirection(false); // if facing left bool = true, if right bool = false
	//TestCube1->scale = Vector3(30, 30, 30);
	//TestCube1->active = true;

	//TestCube2 = FetchGO();
	//TestCube2->type = GameObject::GO_CUBE;
	//TestCube2->pos.Set(m_worldWidth / 4 - m_worldWidthDiv8, m_worldHeight / 2, 5);
	//TestCube2->scale = Vector3(30, 30, 30);
	//TestCube2->active = true;

	//TestCube3 = FetchGO();
	//TestCube3->type = GameObject::GO_CUBE;
	//TestCube3->pos.Set(m_worldWidth / 4 - m_worldWidthDiv8, m_worldHeight / 2, 5);
	//TestCube3->scale = Vector3(30, 30, 30);
	//TestCube3->active = true;

	//TestCube4 = FetchGO();
	//TestCube4->type = GameObject::GO_CUBE;
	//TestCube4->pos.Set(m_worldWidth / 4 - m_worldWidthDiv8, m_worldHeight / 2, 5);
	//TestCube4->scale = Vector3(30, 30, 30);
	//TestCube4->active = true;


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
	// Initialize Character
	charOne = new CharacterObject(CharacterObject::GO_SPRITE_TEST);
	charOne->giveUp = false;
	charOne->experience = Math::RandFloatMinMax(1.f, 2.f);
	charOne->pos.Set(m_worldWidth / 4 - m_worldWidthDiv8, m_worldHeight / 2, 5);
	charOne->scale = Vector3(30, 30, 30);
	charOne->active = true;

	charTwo = new CharacterObject(CharacterObject::GO_CUBE);
	charTwo->giveUp = false;
	charTwo->experience = Math::RandFloatMinMax(1.f, 2.f);
	charTwo->pos.Set(m_worldWidth / 4 - m_worldWidthDiv8, m_worldHeight / 2, 5);
	charTwo->scale = Vector3(30, 30, 30);
	charTwo->active = true;

	charThree = new CharacterObject(CharacterObject::GO_CUBE);
	charThree->giveUp = false;
	charThree->experience = Math::RandFloatMinMax(1.f, 1.5f);
	charThree->pos.Set(m_worldWidth / 4 - m_worldWidthDiv8, m_worldHeight / 2, 5);
	charThree->scale = Vector3(30, 30, 30);
	charThree->active = true;

	charFour = new CharacterObject(CharacterObject::GO_CUBE);
	charFour->giveUp = false;
	charFour->experience = Math::RandFloatMinMax(1.f, 1.5f);
	charFour->pos.Set(m_worldWidth / 4 - m_worldWidthDiv8, m_worldHeight / 2, 5);
	charFour->scale = Vector3(30, 30, 30);
	charFour->active = true;

	currentChar = charOne;

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

	SpriteAnimation *Frog_Jump = dynamic_cast<SpriteAnimation*>(meshList[GEO_FROG_JUMP]);
	if (Frog_Jump)
	{
		Frog_Jump->m_anim = new Animation();
		Frog_Jump->m_anim->Set(0, 5, 0, 1.f, true);
	}


	color = 1.0f;

}

void StudioProjectScene::Update(double dt)
{
	SceneBase::Update(dt);

	/*vel.Set(0.1, 0, 0);
	pos += vel;*/

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

	if (Application::IsKeyPressed(VK_F1))
	{
		currentChar = charOne;
	}
	if (Application::IsKeyPressed(VK_F2))
	{
		currentChar = charTwo;
	}
	if (Application::IsKeyPressed(VK_F3))
	{
		currentChar = charThree;
	}
	if (Application::IsKeyPressed(VK_F4))
	{
		currentChar = charFour;
	}

	//CharOne
	/*if (charOne->frustration < 100)
	{
		charOne->frustration += 0.4f / charOne->experience * 1 / m_Count * dt;
	}
	if (charOne->rest > 0)
	{
		charOne->rest -= 1.5f  *  charOne->experience * dt / m_Count;
	}
	else
	{
		charOne->rest = 0.005f;
	}
	if (charOne->motivation > 0)
	{
		charOne->motivation -= 0.5f * charOne->experience * dt / m_Count;
	}
	else
	{
		charOne->rest = 0.005f;
	}
	if (charOne->workDone < 100)
	{
		charOne->workDone += 0.25f/charOne->experience * charOne->motivation / charOne->rest *  dt / m_Count;
	}*/
	charOne->Update(dt);
	meshList[GEO_CHARONEFRUST] = MeshBuilder::GenerateBar("charOneFrustration", Color(1, 0, 0), charOne->frustration / 3, 1.f);
	meshList[GEO_CHARONEMOTIVE] = MeshBuilder::GenerateBar("CharOneMotivation", Color(1, 1, 0), charOne->motivation / 3, 1.f);
	meshList[GEO_CHARONEREST] = MeshBuilder::GenerateBar("CharOneRest", Color(1, 0, 1), charOne->rest / 3, 1.f);
	meshList[GEO_CHARONEWD] = MeshBuilder::GenerateBar("CharOneWorkDone", Color(0, 1, 1), charOne->workDone / 3, 1.f);
	//CharTwo
	/*if (charTwo->frustration < 100)
	{
		charTwo->frustration += 0.4f / charTwo->experience * 1 / m_Count * dt;
	}
	if (charTwo->rest > 0)
	{
		charTwo->rest -= 1.5f * charTwo->experience * dt / m_Count;
	}
	else
	{
		charTwo->rest = 0.005f;
	}
	if (charTwo->motivation > 0)
	{
		charTwo->motivation -= 0.15f / charTwo->experience * dt / m_Count;

	}
	else
	{
		charTwo->motivation = 0.005f;
	}
	if (charTwo->workDone < 100)
	{
		charTwo->workDone += 0.25f / charTwo->experience * charTwo->motivation / charTwo->rest *  dt / m_Count;
	}*/
	meshList[GEO_CHARTWOFRUST] = MeshBuilder::GenerateBar("charTwoFrustration", Color(1, 0, 0), charTwo->frustration / 3, 1.f);
	meshList[GEO_CHARTWOMOTIVE] = MeshBuilder::GenerateBar("CharTwoMotivation", Color(1, 1, 0), charTwo->motivation / 3, 1.f);
	meshList[GEO_CHARTWOREST] = MeshBuilder::GenerateBar("CharTwoRest", Color(1, 0, 1), charTwo->rest / 3, 1.f);
	meshList[GEO_CHARTWOWD] = MeshBuilder::GenerateBar("CharTwoWorkDone", Color(0, 1, 1), charTwo->workDone / 3, 1.f);
	//CharThree
	/*if (charThree->frustration < 100)
	{
		charThree->frustration += 0.4f / charThree->experience * 1 / m_Count * dt;
	}
	if (charThree->rest > 0)
	{
		charThree->rest -= 1.5f * charThree->experience * dt / m_Count;
	}
	else
	{
		charThree->rest = 0.005f;
	}
	if (charThree->motivation > 0)
	{
		charThree->motivation -= 0.15f / charThree->experience * dt / m_Count;
	}
	else
	{
		charThree->motivation = 0.005f;
	}
	if (charThree->workDone < 100)
	{
		charThree->workDone += 0.25f / charThree->experience * charThree->motivation / charThree->rest *  dt / m_Count;
	}*/
	meshList[GEO_CHARTHREEFRUST] = MeshBuilder::GenerateBar("charThreeFrustration", Color(1, 0, 0), charThree->frustration / 3, 1.f);
	meshList[GEO_CHARTHREEMOTIVE] = MeshBuilder::GenerateBar("CharThreeMotivation", Color(1, 1, 0), charThree->motivation / 3, 1.f);
	meshList[GEO_CHARTHREEREST] = MeshBuilder::GenerateBar("CharThreeRest", Color(1, 0, 1), charThree->rest / 3, 1.f);
	meshList[GEO_CHARTHREEWD] = MeshBuilder::GenerateBar("CharThreeWorkDone", Color(0, 1, 1), charThree->workDone / 3, 1.f);
	//CharFour
	/*if (charFour->frustration < 100)
	{
		charFour->frustration += 0.4f / charFour->experience * 1 / m_Count * dt;
	}
	if (charFour->rest > 0)
	{
		charFour->rest -= 1.5f * charFour->experience * dt / m_Count;
	}
	else
	{
		charFour->rest = 0.005f;
	}
	if (charFour->motivation > 0)
	{
		charFour->motivation -= 0.15f / charFour->experience * dt / m_Count;
	}
	else
	{
		charFour->motivation = 0.005f;
	}
	if (charFour->workDone < 100)
	{
		charFour->workDone += 0.25f / charFour->experience * charFour->motivation / charFour->rest *  dt / m_Count;
	}*/
	meshList[GEO_CHARFOURFRUST] = MeshBuilder::GenerateBar("charThreeFrustration", Color(1, 0, 0), charFour->frustration / 3, 1.f);
	meshList[GEO_CHARFOURMOTIVE] = MeshBuilder::GenerateBar("CharThreeMotivation", Color(1, 1, 0), charFour->motivation / 3, 1.f);
	meshList[GEO_CHARFOURREST] = MeshBuilder::GenerateBar("CharThreeRest", Color(1, 0, 1), charFour->rest / 3, 1.f);
	meshList[GEO_CHARFOURWD] = MeshBuilder::GenerateBar("CharFourWorkDone", Color(0, 1, 1), charFour->workDone / 3, 1.f);

	currentChar->UpdateMovement(dt);

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
	SpriteAnimation *Frog_Jump = dynamic_cast<SpriteAnimation*>(meshList[GEO_FROG_JUMP]);
	if (Frog_Jump)
	{
		Frog_Jump->Update(dt);
		Frog_Jump->m_anim->animActive = true;

	}

	for (std::vector<CharacterObject *>::iterator it = m_goList.begin(); it != m_goList.end(); ++it)
	{
		CharacterObject *go = (CharacterObject *)*it;
		if (go->active)
		{

		}
	}
	if (m_eventTimer < 0)
	{
		if (color >= 0)
		{
		color -= dt;
		}
		m_eventTimer = 0;
	}
	UpdateParticles(dt);
	m_eventTimer -= dt;
	cout << "Event Timer : " << m_eventTimer << endl;
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
		particle->lifeTime = 4.4f;
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
	//modelStack.PushMatrix();
	//modelStack.Translate(70, 50, 0);
	//modelStack.Rotate(Math::RadianToDegree(atan2(camera.position.x - 0, camera.position.z - 0)), 0, 1, 0);

	//modelStack.Scale(10, 10, 10);

	//RenderMesh(meshList[GEO_FROG_JUMP], false);
	//modelStack.PopMatrix();
	//std::cout << "WOKRING" << std::endl;
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

	// Multiple viewports
	//{
		// Character Rooms
		if (m_eventTimer > 0)
		{
			glEnable(GL_SCISSOR_TEST);
			glViewport(0, 640, 990, 440);
			glScissor(0, 640, 990, 440);

			RenderCharacter1(); // TOP LEFT


			glViewport(990, 640, 990, 440);
			glScissor(990, 640, 990, 440);

			RenderCharacter2(); // TOP RIGHT

			glViewport(0, 100, 990, 440);
			glScissor(0, 100, 990, 440);

			RenderCharacter3();

			glViewport(990, 100, 990, 440);
			glScissor(990, 100, 990, 440);

			RenderCharacter4();

			// Statistics
			glViewport(0, 540, 990, 100);
			glScissor(0, 540, 990, 100);

			RenderStats1();

			glViewport(990, 540, 990, 100);
			glScissor(990, 540, 990, 100);

			RenderStats2();

			glViewport(0, 0, 990, 100);
			glScissor(0, 0, 990, 100);

			RenderStats3();

			glViewport(990, 0, 990, 100);
			glScissor(990, 0, 990, 100);

			RenderStats4();
			glDisable(GL_SCISSOR_TEST);

		}
		else
		{
			glViewport(0, 0, 1980, 1080);
			glClearColor(color, color, color, 1.0f);
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
	//}

	// End of Multiple viewports
}

void StudioProjectScene::RenderGO(CharacterObject * go)
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

	default:
		break;
	}
}

CharacterObject * StudioProjectScene::FetchGO()
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
		m_goList.push_back(new CharacterObject(CharacterObject::GO_NONE));
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
	modelStack.Translate(m_worldWidth / 2, m_worldHeight / 2, 0);
	modelStack.Scale(198, 108, 1);
	RenderMesh(meshList[GEO_BACKGROUND], false);
	modelStack.PopMatrix();
}

void StudioProjectScene::RenderCharacter1()
{
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

	// BackGround
	RenderBG();

	// Particles
	for (std::vector<Particles *>::iterator it = m_particleList.begin(); it != m_particleList.end(); ++it)
	{
		Particles *particle = (Particles*)*it;
		if (particle->active)
		{
			RenderParticles(particle);
		}
	}

	// Props
	//RenderAnimation();
	modelStack.PushMatrix();
	modelStack.Translate(70, 50, 0);
	modelStack.Rotate(Math::RadianToDegree(atan2(camera.position.x - 0, camera.position.z - 0)), 0, 1, 0);

	modelStack.Scale(10, 10, 10);

	RenderMesh(meshList[GEO_FROG_JUMP], false);
	modelStack.PopMatrix();


	if (currentChar == charOne)
	{
		RenderArrow();
	}


	//Particles
	for (std::vector<Particles *>::iterator it = m_particleList.begin(); it != m_particleList.end();++it)
	{
		Particles *particle = (Particles *)*it;
		if (particle->active)
		{
			RenderParticles(particle);
		}
	}

	//// Character
	if (charOne->active)
		RenderGO(charOne);
}

void StudioProjectScene::RenderCharacter2()
{
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

	// BackGround
	RenderBG();

	// Props
	if (currentChar == charTwo)
	{
		RenderArrow();
	}

	// Character
	if (charTwo->active)
		RenderGO(charTwo);
}

void StudioProjectScene::RenderCharacter3()
{
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

	// BackGround
	RenderBG();

	// Props
	if (currentChar == charThree)
	{
		RenderArrow();
	}

	// Character
	if (charThree->active)
	RenderGO(charThree);
}

void StudioProjectScene::RenderCharacter4()
{
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

	// BackGround
	RenderBG();

	// Props
	if (currentChar == charFour)
	{
		RenderArrow();
	}

	// Character
	if (charFour->active)
	RenderGO(charFour);
}

void StudioProjectScene::RenderStats1()
{
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

	// BackGround

	// RenderStats here
	modelStack.PushMatrix();
	modelStack.Translate(m_worldWidthDiv8 + 10 , m_worldHeight / 2, 0);
	modelStack.Scale(5, 10, 1);
	RenderMesh(meshList[GEO_CHARONEFRUST], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(m_worldWidthDiv8 + 15, m_worldHeight / 2 + 15, 0);
	modelStack.Scale(5, 10, 1);
	RenderMesh(meshList[GEO_CHARONEMOTIVE], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(m_worldWidthDiv8 + 5, m_worldHeight / 2 - 15 , 0);
	modelStack.Scale(5, 10, 1);
	RenderMesh(meshList[GEO_CHARONEREST], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(m_worldWidthDiv8, m_worldHeight / 2 - 30, 0);
	modelStack.Scale(5, 10, 1);
	RenderMesh(meshList[GEO_CHARONEWD], false);
	modelStack.PopMatrix();
}

void StudioProjectScene::RenderStats2()
{
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

	// BackGround

	// RenderStats here
	modelStack.PushMatrix();
	modelStack.Translate(m_worldWidthDiv8 + 15, m_worldHeight / 2 + 15, 0);
	modelStack.Scale(5, 10, 1);
	RenderMesh(meshList[GEO_CHARTWOMOTIVE], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(m_worldWidthDiv8 + 10, m_worldHeight / 2, 0);
	modelStack.Scale(5, 10, 1);
	RenderMesh(meshList[GEO_CHARTWOFRUST], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(m_worldWidthDiv8 + 5, m_worldHeight / 2 - 15, 0);
	modelStack.Scale(5, 10, 1);
	RenderMesh(meshList[GEO_CHARTWOREST], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(m_worldWidthDiv8, m_worldHeight / 2 - 30, 0);
	modelStack.Scale(5, 10, 1);
	RenderMesh(meshList[GEO_CHARTWOWD], false);
	modelStack.PopMatrix();
}


void StudioProjectScene::RenderStats3()
{
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

	// BackGround

	// RenderStats here
	modelStack.PushMatrix();
	modelStack.Translate(m_worldWidthDiv8 + 15, m_worldHeight / 2 + 15, 0);
	modelStack.Scale(5, 10, 1);
	RenderMesh(meshList[GEO_CHARTHREEMOTIVE], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(m_worldWidthDiv8 + 10, m_worldHeight / 2, 0);
	modelStack.Scale(5, 10, 1);
	RenderMesh(meshList[GEO_CHARTHREEFRUST], false);
	modelStack.PopMatrix();


	modelStack.PushMatrix();
	modelStack.Translate(m_worldWidthDiv8 + 5, m_worldHeight / 2 - 15, 0);
	modelStack.Scale(5, 10, 1);
	RenderMesh(meshList[GEO_CHARTHREEREST], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(m_worldWidthDiv8, m_worldHeight / 2 - 30, 0);
	modelStack.Scale(5, 10, 1);
	RenderMesh(meshList[GEO_CHARTHREEWD], false);
	modelStack.PopMatrix();
}


void StudioProjectScene::RenderStats4()
{
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

	// BackGround

	// RenderStats here

	modelStack.PushMatrix();
	modelStack.Translate(m_worldWidthDiv8 + 15, m_worldHeight / 2 + 15, 0);
	modelStack.Scale(5, 10, 1);
	RenderMesh(meshList[GEO_CHARFOURMOTIVE], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(m_worldWidthDiv8 + 10, m_worldHeight / 2, 0);
	modelStack.Scale(5, 10, 1);
	RenderMesh(meshList[GEO_CHARFOURFRUST], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(m_worldWidthDiv8 + 5, m_worldHeight / 2 - 15, 0);
	modelStack.Scale(5, 10, 1);
	RenderMesh(meshList[GEO_CHARFOURREST], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(m_worldWidthDiv8, m_worldHeight / 2 - 30, 0);
	modelStack.Scale(5, 10, 1);
	RenderMesh(meshList[GEO_CHARFOURWD], false);
	modelStack.PopMatrix();
}
