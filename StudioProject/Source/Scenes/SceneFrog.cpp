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


	//m_worldHeight = 200.f;
	//// End James 13/8/2019
	//m_worldWidth = m_worldHeight * (float)Application::GetWindowWidth() / Application::GetWindowHeight();

	m_halfWorldHeight = m_worldHeight / 2;
	m_halfWorldWidth = m_worldWidth / 2;
	m_goList = new std::vector<FrogObject*>;


	//Calculating aspect ratio
	m_worldHeight = 100.f;
	m_worldWidth = m_worldHeight * (float)Application::GetWindowWidth() / Application::GetWindowHeight();
	m_halfWorldHeight = m_worldHeight / 2;
	m_halfWorldWidth = m_worldWidth / 2;
	//Physics code here
	m_speed = 1.f;

	Math::InitRNG();
	//  ******************************* PROPS HERE  ******************************* //


	meshList[GEO_FROG] = MeshBuilder::GenerateQuad("frog", Color(1, 1, 1), 1.f);
	meshList[GEO_FROG]->textureID = LoadTGA("Image//Idle_anim2.tga");
	meshList[GEO_FROG_MAP] = MeshBuilder::GenerateQuad("map", Color(1, 1, 1), 1.f);
	meshList[GEO_FROG_MAP]->textureID = LoadTGA("Image//BGTest.tga");
	meshList[GEO_FROG_PLATFORM] = MeshBuilder::GenerateQuad("platform", Color(1, 1, 1), 1.f);
	meshList[GEO_FROG_PLATFORM]->textureID = LoadTGA("Image//Frog_ground.tga");
	meshList[GEO_FROG_ROCK] = MeshBuilder::GenerateCircle("rock", Color(1, 1, 1), 1.f);
	meshList[GEO_FROG_ROCK]->textureID = LoadTGA("Image//Frog_rock.tga");
	meshList[GEO_TEXT] = MeshBuilder::GenerateText("text", 16, 16);
	meshList[GEO_TEXT]->textureID = LoadTGA("Image//calibri.tga");
	//  ******************************* SPRITE ANIMATIONS HERE  ******************************* //



	//  ******************************* PARTICLES HERE  ******************************* //
	Mtx44 projection;
	projection.SetToOrtho(0, m_worldWidth, 0, m_worldHeight, -10, 10);
	projectionStack.LoadMatrix(projection);


	m_grav.Set(0, -10 * (1 / rockSize), 0);

	Frog = FetchGO();
	Frog->active = true;
	Frog->type = FrogObject::GO_FROG;
	Frog->Frog_pos.Set(10, 10, 0);
	Frog->Frog_vel.Set(0, 0, 0);
	Frog->Frog_jumpVel.Set(0, 20, 0);

	rockSize = (Math::RandFloatMinMax(10, 20));

	for (int i = 0; i < 10; i++)
	{
		FrogObject* rock = new FrogObject(FrogObject::GO_ROCK);
		rock->active = true;
		rock->pos.Set(Math::RandFloatMinMax(50, m_worldWidth - 50), m_worldHeight + 10, 0);
		rock->Frog_vel.Set(0, m_grav.y, 0);
	}
	
}

bool CheckCollision(FrogObject* go, FrogObject* go2) 
{
	switch (go2->type)
	{
	case FrogObject::GO_ROCK:
	{
		Vector3 dis = go2->pos - go->pos;
		if ((dis).Length() <= go->scale.x + go2->scale.x)
		{
			return true;
		}
		break;
	}
	case FrogObject::GO_PLATFORM:
	{
		Vector3 N = go2->normal;
		Vector3 dist = go2->pos - go->pos;
		if (dist.Dot(N) < 0)
		{
			N = -N;
		}
		Vector3 NP(N.y, -N.x);
		if (dist.Dot(N) < (go->scale.x + go2->scale.x * 0.5f) &&
			abs(dist.Dot(NP)) < (go->scale.y + go2->scale.y * 0.5f))
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
	SceneBase::Update(dt);
	if (Application::IsKeyPressed('A'))
	{
		Frog->Frog_vel.x -= 1;
	}
	if (Application::IsKeyPressed('D'))
	{
		Frog->Frog_vel.x += 1;
	}
	m_grav.Set(0, -10 * (1 / rockSize), 0);

	for (int i = 0; i < (int)m_goList->size(); ++i)
	{
		FrogObject *go = (*m_goList)[i];
		if (go->active)
		{
			switch (go->type)
			{
			case FrogObject::GO_FROG:
			{
				break;
			}
			case FrogObject::GO_ROCK:
			{
				if (0 > go->pos.y + go->scale.y)
				{
					go->active = false;
					RockCount--;
				}
			}
			}
			go->pos += go->Frog_vel;
			for (int k = i + 1; k < (int)m_goList->size(); ++k)
			{
				FrogObject* go2 = (*m_goList)[k];
				if (go2->active)
				{
					if (CheckCollision(go, go2))
					{
						go->CollisionResponse(go, go2, dt);
					}
					go = (*m_goList)[i];
				}
			}
		}
	}

}

FrogObject * SceneFrog::FetchGO()
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
		m_goList->push_back(new	FrogObject(FrogObject::GO_NONE));
	}

	(*m_goList)[m_goList->size() - 20]->active = true;
	return (*m_goList)[m_goList->size() - 20];
}


void SceneFrog::UpdateParticles(double dt)
{

}

void SceneFrog::RenderGO(FrogObject* go)
{
	switch (go->type)
	{
	case FrogObject::GO_FROG:
	{
		modelStack.PushMatrix();
		modelStack.Translate(go->Frog_pos);
		modelStack.Scale(go->scale);
		RenderMesh(meshList[GEO_FROG], false);
		modelStack.PopMatrix();
		break;
	}
	case FrogObject::GO_PLATFORM:
	{
		modelStack.PushMatrix();
		modelStack.Translate(go->pos);
		modelStack.Scale(go->scale);
		RenderMesh(meshList[GEO_FROG_PLATFORM], false);
		modelStack.PopMatrix();
		break;
	}
	case FrogObject::GO_ROCK:
	{
		modelStack.PushMatrix();
		modelStack.Translate(go->pos);
		modelStack.Scale(go->scale);
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
	modelStack.PushMatrix();
	modelStack.Translate(m_worldHeight / 2.f, m_worldWidth / 2.f, 0);
	modelStack.Rotate(Math::RadianToDegree(atan2(camera.position.x - 0, camera.position.z - 0)), 0, 1, 0);
	modelStack.Scale(m_worldWidth, m_worldHeight, 1);
	RenderMesh(meshList[GEO_FROG_MAP], false);
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

	for (std::vector<FrogObject *>::iterator it = m_goList->begin(); it != m_goList->end(); ++it)
	{
		FrogObject *go = (FrogObject *)*it;
		if (go->active)
		{
			RenderGO(go);
		}
	}

	RenderMap();
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
	delete m_goList;
}