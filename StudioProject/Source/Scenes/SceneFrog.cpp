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
	m_worldHeight = 200.f;
	m_worldWidth = m_worldHeight * (float)Application::GetWindowWidth() / Application::GetWindowHeight();
	m_halfWorldHeight = m_worldHeight / 2;
	m_halfWorldWidth = m_worldWidth / 2;
	//Physics code here
	m_speed = 1.f;

	Math::InitRNG();
	//  ******************************* PROPS HERE  ******************************* //


	meshList[GEO_FROG] = MeshBuilder::GenerateQuad("frog", Color(1, 1, 1), 2.f);
	//meshList[GEO_FROG]->textureID = LoadTGA("Image//balloon.tga");
	meshList[GEO_FROG_MAP] = MeshBuilder::GenerateQuad("map", Color(1, 1, 1), 1.f);
	meshList[GEO_FROG_MAP]->textureID = LoadTGA("Image//BGTest.tga");
	meshList[GEO_FROG_PLATFORM] = MeshBuilder::GenerateQuad("platform", Color(1, 1, 1), 1.f);
	//meshList[GEO_FROG_PLATFORM]->textureID = LoadTGA("Image//BGTest.tga");
	meshList[GEO_FROG_ROCK] = MeshBuilder::GenerateQuad("rock", Color(1, 1, 1), 2.f);
	meshList[GEO_FROG_ROCK]->textureID = LoadTGA("Image//rock.tga");
	meshList[GEO_COIN] = MeshBuilder::GenerateCircle("coin", Color(1, 1, 1), 2.f);
	meshList[GEO_COIN]->textureID = LoadTGA("Image//coin.tga");
	meshList[GEO_TEXT] = MeshBuilder::GenerateText("text", 16, 16);
	meshList[GEO_TEXT]->textureID = LoadTGA("Image//calibri.tga");
	//  ******************************* SPRITE ANIMATIONS HERE  ******************************* //



	//  ******************************* PARTICLES HERE  ******************************* //
	Mtx44 projection;
	projection.SetToOrtho(0, m_worldWidth, 0, m_worldHeight, -10, 10);
	projectionStack.LoadMatrix(projection);



	m_rockCount = 0;
	m_coinCount = 0;

	Frog = FetchGO();
	Frog->active = true;
	Frog->type = FrogObject::GO_FROG;
	Frog->scale.Set(3, 3, 1);
	Frog->Frog_pos.Set(200, 10, 0);
	Frog->Frog_vel.Set(0, 0, 0);
	Frog->Frog_jumpVel.Set(0, 20, 0);
	hp = Frog->getHP();
	cout << m_worldHeight << " , " << m_worldWidth << endl;
	max_rock = 5;
	max_coin = 5;

	for (int i = 0; i < 5; i++)
	{
		FrogObject* rock = new FrogObject(FrogObject::GO_ROCK);
		rock_List.push_back(rock);
	}
	for (int i = 0; i < 5; i++)
	{
		FrogObject* coin = new FrogObject(FrogObject::GO_COIN);
		rock_List.push_back(coin);
	}
	
}

FrogObject* SceneFrog::getRock()
{
	for (std::vector<FrogObject *>::iterator it = rock_List.begin(); it != rock_List.end(); ++it)
	{
		FrogObject *Rock = (FrogObject *)*it;
		if (Rock->type == FrogObject::GO_COIN)
		{
			if (!Rock->active)
			{
				Rock->active = true;
				m_coinCount++;
				return Rock;
			}
		}
		else if (Rock->type == FrogObject::GO_ROCK)
		{
			if (!Rock->active)
			{
				Rock->active = true;
				m_rockCount++;
				return Rock;
			}
		}
	}
	for (unsigned i = 0; i < 2; ++i)
	{
		FrogObject *rock = new FrogObject(FrogObject::GO_ROCK);
		rock_List.push_back(rock);
	}
	for (unsigned i = 0; i < 2; ++i)
	{
		FrogObject *coin = new FrogObject(FrogObject::GO_COIN);
		rock_List.push_back(coin);
	}
	m_rockCount++;
	rock_List[rock_List.size() - 1]->active = true;
	return rock_List[rock_List.size() - 1];
}

void SceneFrog::UpdateRock(double dt)
{
	float sc;
	sc = Math::RandFloatMinMax(15, 30) / 2;
	m_grav.Set(0, -sc * 2, 0);

	if (m_rockCount < max_rock)
	{
		FrogObject* rock = getRock();
		rock->type = FrogObject::GO_ROCK;
		rock->scale.Set(sc, sc, sc);
		rock->pos.Set(Math::RandFloatMinMax((m_worldWidth / 2) - 50,(m_worldWidth / 2) + 50), m_worldHeight, 0);
	}
	if (m_coinCount < max_coin)
	{
		FrogObject* coin = getRock();
		coin->type = FrogObject::GO_COIN;
		coin->scale.Set(3, 3, 1);
		coin->pos.Set(Math::RandIntMinMax(14, 25) * 10, Math::RandIntMinMax(2, 38) * 5, 0);
	}
	for (std::vector<FrogObject *>::iterator it = rock_List.begin(); it != rock_List.end(); ++it)
	{
		FrogObject *rock = (FrogObject *)*it;
		if (rock->active)
		{
			if (rock->type == FrogObject::GO_ROCK)
			{
				rock->Frog_vel += Vector3(0, m_grav.y, 0)* (float)dt;
				rock->pos += rock->Frog_vel * (float)dt;
			}
			if (rock->type == FrogObject::GO_COIN)
			{
			}
			if (rock->pos.y <= 0)
			{
				rock->Frog_vel.SetZero();
				rock->pos.y = m_worldHeight;
				rock->pos.x = Math::RandFloatMinMax((m_worldWidth / 2) - 50, (m_worldWidth / 2) + 50);
			}
		}
	}
}

bool SceneFrog::CheckCollision(FrogObject* go, FrogObject* go2) 
{
	switch (go2->type)
	{
	case FrogObject::GO_ROCK:
	{
		Vector3 dis = go2->pos - go->Frog_pos;
		Vector3 u = go->Frog_vel - go2->Frog_vel;
		if ((dis).Length() <= go2->scale.x && u.Dot(dis) > 0)
		{
			return true;
		}
		break;
	}
	case FrogObject::GO_COIN:
	{
		Vector3 dis = go2->pos - go->Frog_pos;
		Vector3 u = go->Frog_vel - go2->Frog_vel;
		if ((dis).Length() <= go2->scale.x)
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
	double x, y;
	Frog->timerInvincibility += dt;
	Application::GetCursorPos(&x, &y);
	int w = Application::GetWindowWidth();
	int h = Application::GetWindowHeight();
	v_mousepos = Vector3(static_cast<float>(x) / (w / m_worldWidth), (h - static_cast<float>(y)) / (h / m_worldHeight), 0.0f);


	static bool bMovingLeft = false;
	if (Frog->Frog_pos.x >= (m_worldWidth / 2) - 50)
	{
		if (Application::IsKeyPressed('A') && !bMovingLeft)
		{
			Frog->Frog_pos.x -= 10.f;
			bMovingLeft = true;
		}

		else if (!Application::IsKeyPressed('A') && bMovingLeft)
		{
			bMovingLeft = false;
		}
	}
	static bool bMovingRight = false;
	if (Frog->Frog_pos.x <= (m_worldWidth / 2) + 50)
	{
		if (Application::IsKeyPressed('D') && !bMovingRight)
		{
			Frog->Frog_pos.x += 10.f;
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

	UpdateRock(dt);

	for (int i = 0; i < (int)m_goList->size(); ++i)
	{

		FrogObject *go = (*m_goList)[i];

		if (go->active)
		{
			switch (go->type)
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
				if (go2->active)
				{
					go = (*m_goList)[i];
					//cout << go2->pos << endl;
					if (CheckCollision(go, go2))
					{
						go->CollisionResponse(go, go2, dt);
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


void SceneFrog::RenderRock(FrogObject* rock)
{
	switch (rock->type)
	{
	case FrogObject::GO_ROCK:
		modelStack.PushMatrix();
		modelStack.Translate(rock->pos.x, rock->pos.y, rock->pos.z);
		modelStack.Scale(rock->scale.x, rock->scale.y, rock->scale.z);
		RenderMesh(meshList[GEO_FROG_ROCK], false);
		modelStack.PopMatrix();
		break;
	case FrogObject::GO_COIN:
		modelStack.PushMatrix();
		modelStack.Translate(rock->pos.x, rock->pos.y, rock->pos.z);
		modelStack.Scale(rock->scale.x, rock->scale.y, rock->scale.z);
		RenderMesh(meshList[GEO_COIN], false);
		modelStack.PopMatrix();
		break;
	}
}

void SceneFrog::RenderCoin(FrogObject* coin)
{
	modelStack.PushMatrix();
	modelStack.Translate(coin->pos);
	modelStack.Scale(coin->scale);
	RenderMesh(meshList[GEO_COIN], false);
	modelStack.PopMatrix();
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
	modelStack.Scale(2 *m_worldWidth,2* m_worldHeight, 1);
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

	RenderMap();

	for (std::vector<FrogObject *>::iterator it = m_goList->begin(); it != m_goList->end(); ++it)
	{
		FrogObject *go = (FrogObject *)*it;
		if (go->active)
		{
			RenderGO(go);
		}
	}

	for (std::vector<FrogObject *>::iterator it = rock_List.begin(); it != rock_List.end(); ++it)
	{
		FrogObject *rock = (FrogObject*)*it;
		if (rock->active)
		{
			RenderRock(rock);
		}
	}

	cout << m_worldWidth << endl;
	std::ostringstream ss;
	ss.precision(5);
	ss << "M:" << v_mousepos;
	RenderTextOnScreen(meshList[GEO_TEXT], ss.str(), Color(0, 1, 0), 3, 0, 0);

	std::ostringstream ss2;
	ss2.precision(2);
	ss2 << "HP: " << Frog->getHP();
	RenderTextOnScreen(meshList[GEO_TEXT], ss2.str(), Color(0, 1, 0), 3, 0, 3);
	std::ostringstream ss3;
	ss3.precision(5);
	ss3 << "Pos: " << Frog->Frog_pos;
	RenderTextOnScreen(meshList[GEO_TEXT], ss3.str(), Color(0, 1, 0), 3, 0, 6);
	std::ostringstream ss4;
	ss4.precision(6);
	ss4 << "Score: " << Frog->score;
	RenderTextOnScreen(meshList[GEO_TEXT], ss4.str(), Color(0, 1, 0), 3, 0, 9);


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