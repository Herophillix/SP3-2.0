#include "SheepGame.h"
#include "GL\glew.h"
#include "Source/Application.h"
#include <sstream>
#include "Source/Rendering/LoadTGA.h"
#include "Source/Rendering/MeshBuilder.h"

SheepGame::SheepGame():
	m_Gravity(0,-9.8,0),
	m_Timer(2.f)
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

	meshList[GEO_SHEEPBG] = MeshBuilder::GenerateQuad("SheepBG", Color(1, 1, 1), 1.f);
	meshList[GEO_SHEEPBG]->textureID = LoadTGA("Image//sheepBG.tga");
	
	meshList[GEO_SHEEP] = MeshBuilder::GenerateQuad("Sheep", Color(1, 1, 1), 1.f);
	meshList[GEO_SHEEP]->textureID = LoadTGA("Image//Sheepy.tga");
	
	meshList[GEO_SHEEPFLIPPED] = MeshBuilder::GenerateQuad("SheepFlipped", Color(1, 1, 1), 1.f);
	meshList[GEO_SHEEPFLIPPED]->textureID = LoadTGA("Image//SheepyFlipped.tga");

	meshList[GEO_FIREBALL] = MeshBuilder::GenerateQuad("Fireball", Color(1, 1, 1), 1.f);
	meshList[GEO_FIREBALL]->textureID = LoadTGA("Image//fireball.tga");

	meshList[GEO_SPRITE_ANIMATION] = MeshBuilder::GenerateSpriteAnimation("test", 1, 4);
	meshList[GEO_SPRITE_ANIMATION]->textureID = LoadTGA("Image//Idle_anim.tga");
	meshList[GEO_WALKLEFT] = MeshBuilder::GenerateSpriteAnimation("char1walkleft", 1, 4);
	meshList[GEO_WALKLEFT]->textureID = LoadTGA("Image//Walk_animLeft.tga");
	meshList[GEO_WALKRIGHT] = MeshBuilder::GenerateSpriteAnimation("char1walkright", 1, 4);
	meshList[GEO_WALKRIGHT]->textureID = LoadTGA("Image//Walk_animRight.tga");
	meshList[GEO_SPRITE_TEST2] = MeshBuilder::GenerateSpriteAnimation("test2", 1, 6);
	meshList[GEO_SPRITE_TEST2]->textureID = LoadTGA("Image//Idle_anim2.tga");


	Mtx44 projection;
	projection.SetToOrtho(0, m_worldWidth, 0, m_worldHeight, -10, 10);
	projectionStack.LoadMatrix(projection);

	tempwall = FetchGO();
	tempwall->type = SheepObject::E_WALL;
	tempwall->pos.Set(m_worldWidth / 2, 5,0);
	tempwall->normal.Set(0, 1,0);
	tempwall->scale.Set(2, m_worldWidth,1);



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
	player = new SheepObject(SheepObject::E_PLAYER);
	player->health = 100;
	player->active = true;
	player->pos.Set(0, 18, 0);
	player->scale.Set(10, 10, 10);
	player->cooldown = 2.f;
}

void SheepGame::Update(double dt)
{
	SceneBase::Update(dt);
	//Calculating aspect ratio
	m_worldHeight = 100.f;
	m_worldWidth = m_worldHeight * (float)Application::GetWindowWidth() / Application::GetWindowHeight();

	tempwall->pos.Set(m_worldWidth / 2, 5);
	tempwall->scale.Set(2, m_worldWidth, 1);
	static bool bLButtonState = false;
	if (!bLButtonState && Application::IsMousePressed(0))
	{
		bLButtonState = true;
		
		std::cout << "LBUTTON DOWN" << std::endl;
	}
	else if (bLButtonState && !Application::IsMousePressed(0))
	{
		bLButtonState = false;

		double x, y;
		Application::GetCursorPos(&x, &y);

		int w = Application::GetWindowWidth();
		int h = Application::GetWindowHeight();
		if (!player->onCooldown)
		{
			SheepObject *Fireball = FetchGO();
			Fireball->type = SheepObject::E_FIREBALL;
			Fireball->pos.Set(player->pos.x, player->pos.y, 0);
			Fireball->vel.Set(((x / w * m_worldWidth) - player->pos.x) / 2, ((m_worldHeight - y / h * m_worldHeight) - player->pos.y) / 2, 0);
			Fireball->scale.Set(8, 8, 8);
			player->onCooldown = true;
		}

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
	if (m_Timer < 0)
	{
		SheepObject* Sheep = FetchGO();
		Sheep->type = SheepObject::E_SHEEPFLIPPED;
		Sheep->scale.Set(10, 10, 10);
		Sheep->vel.Set(Math::RandFloatMinMax(-10, -20), Math::RandFloatMinMax(10, 15), 0);
		Sheep->pos.Set(m_worldWidth - 10, Math::RandFloatMinMax(m_worldHeight / 3,m_worldHeight/2), 0);
		Sheep->active = true;
		Sheep->isDown = false;
		cout << "spawned " << endl;
		m_Timer = Math::RandFloatMinMax(5, 10);
	}
	//Iterator for sheep objects
	for (std::vector<SheepObject *>::iterator it = m_goList.begin(); it != m_goList.end(); ++it)
	{
		SheepObject *go = (SheepObject *)*it;
		
		if (go->type == SheepObject::E_SHEEPFLIPPED)
		{
			go->pos += go->vel * (float)dt;
			if (go->pos.y > m_worldHeight - 40)
			{
				go->isDown = true;
			}
			//if (go->pos.y < 60)
			//{
			//	go->isDown = false;
			//}
			if(go->isDown == true)
			{
				go->vel.y -=sin(m_Gravity.y) * 2;
				//go->vel += m_Gravity * dt;
			}
			//if (go->isDown == false)
			//{
			//	go->vel.y += sin(m_Gravity.y) * 2;
			//}
			for (std::vector<SheepObject *>::iterator it2 = m_goList.begin(); it2 != m_goList.end(); ++it2)
			{
				SheepObject* go2 = (SheepObject *)*it2;

				if (go2->type == SheepObject::E_WALL)
				{
					if (CollisionCheck(go, go2))
					{
						cout << "Collide" << endl;
						go->vel.y = -go->vel.y;
						//cout << CollisionCheck(go2,go) << endl;
					}
				}
			}
		}
		if (go->type == SheepObject::E_FIREBALL)
		{
			go->pos += go->vel * (float)dt;
		}
	}
	if (player->onCooldown)
	{
		player->cooldown -= dt;
	}
	if (player->cooldown < 0)
	{
		player->cooldown = 2.f;
		player->onCooldown = false;
	}
	player->UpdateMovement(dt);
	m_Timer -= dt;
	cout << player->cooldown << endl;
}

bool SheepGame::CollisionCheck(SheepObject *go, SheepObject *go2)
{
	switch (go2->type)
	{
	case SheepObject::E_WALL:
	{
		Vector3 N = go2->normal;

		Vector3 w0minusb1 = go2->pos - go->pos;

		Vector3 NP(N.y, -N.x);
		if (w0minusb1.Dot(N) < 0)
		{
			N = -N;
		}
		if (go->vel.Dot(N) < 0)
		{
			return false;
		}
		if (w0minusb1.Dot(N) < go->scale.x + go2->scale.x * 0.5f &&
			Math::FAbs(w0minusb1.Dot(NP)) < go->scale.x + go2->scale.y * 0.5f)
		{
			return true;
		}
		break;
	}
	default:
		return false;
		break;
	}
	return false;
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

		renderBG();
		if (player->active)
		{
			RenderGO(player);
		}
		for (std::vector<SheepObject *>::iterator it = m_goList.begin(); it != m_goList.end(); ++it)
		{
			SheepObject *go = (SheepObject *)*it;
			if (go->active)
			{
				RenderGO(go);
			}
		}
}

void SheepGame::renderBG()
{
	modelStack.PushMatrix();
	modelStack.Translate(m_worldWidth / 2, m_worldHeight / 2, 0);
	modelStack.Scale(198, 108, 1);
	RenderMesh(meshList[GEO_SHEEPBG], false);
	modelStack.PopMatrix();
}

void SheepGame::RenderGO(SheepObject * go)
{
	switch (go->type)
	{
	case SheepObject::E_SHEEP:
	{
		modelStack.PushMatrix();
		modelStack.Translate(go->pos.x, go->pos.y, go->pos.z);
		modelStack.Scale(go->scale.x, go->scale.y, go->scale.z);
		RenderMesh(meshList[GEO_SHEEP], false);
		modelStack.PopMatrix();
		break;
	}
	case SheepObject::E_SHEEPFLIPPED:
	{
		modelStack.PushMatrix();
		modelStack.Translate(go->pos.x, go->pos.y, go->pos.z);
		modelStack.Scale(go->scale.x, go->scale.y, go->scale.z);
		RenderMesh(meshList[GEO_SHEEPFLIPPED], false);
		modelStack.PopMatrix();
		break;
	}
	case SheepObject::E_PLAYER:
	{
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
	}
	case  SheepObject::E_FIREBALL:
	{
		modelStack.PushMatrix();
		modelStack.Translate(go->pos.x, go->pos.y, go->pos.z);
		modelStack.Scale(go->scale.x, go->scale.y, go->scale.z);
		RenderMesh(meshList[GEO_FIREBALL], false);
		modelStack.PopMatrix();
		break;
	}
	
	/* case SheepObject::E_WALL:
	{
		modelStack.PushMatrix();
		modelStack.Translate(go->pos);
		modelStack.Rotate(Math::RadianToDegree(atan2(go->normal.y, go->normal.x)), 0, 0, 1);
		modelStack.Scale(go->scale);
		RenderMesh(meshList[GEO_WALL], false);
		modelStack.PopMatrix();
		break;
	}*/
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
		go = nullptr;
		delete go;
		m_goList.pop_back();
	}
}