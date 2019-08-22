#include "SceneMaze.h"
#include "GL\glew.h"
#include "../Application.h"
#include <sstream>
#include "../Rendering/LoadTGA.h"
#include "../Rendering/MeshBuilder.h"

SceneMaze::SceneMaze()
{
}


SceneMaze::~SceneMaze()
{
}

void SceneMaze::Init()
{
	SceneBase::Init();

	Results::getInstance()->InitVars();
	//Calculating aspect ratio
	// James 13/8/2019
	m_worldHeight = 200.f;
	// End James 13/8/2019
	m_worldWidth = m_worldHeight * (float)Application::GetWindowWidth() / Application::GetWindowHeight();

	//Physics code here
	m_speed = 1.f;

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
	tempwall->pos = Vector3(m_worldWidth*0.5, 0, 0);
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

	Maze.SetUp("Source\\Minigames\\Maze\\Map\\Map1.txt",m_goList);

	// End James 14/8/2019
	// End James 13/8/2019

	// James 15/8/2019
	enableStencil = true;
	// End James 15/8/2019

	endGame = false;
	elapsedTime = 0;
}

void SceneMaze::Update(double dt)
{
	SceneBase::Update(dt);
	//Calculating aspect ratio
	// James 13/8/2019
	m_worldHeight = 200.f;
	// End James 13/8/2019
	m_worldWidth = m_worldHeight * (float)Application::GetWindowWidth() / Application::GetWindowHeight();

	// James 14/8/2019
	tempwall->pos = Vector3(m_worldWidth*0.5, 0, 0);
	tempwall->scale.Set(5, m_worldWidth, 1);

	tempwall2->pos = Vector3(m_worldWidth*0.5, m_worldHeight, 0);
	tempwall2->scale.Set(5, m_worldWidth, 1);

	tempwall3->pos = Vector3(0, m_worldHeight * 0.5f, 0);
	tempwall3->scale.Set(5, m_worldHeight, 1);

	tempwall4->pos = Vector3(m_worldWidth, m_worldHeight * 0.5f, 0);
	tempwall4->scale.Set(5, m_worldHeight, 1);

	// End James 14/8/2019
	// James 13/8/2019
	double x, y;
	Application::GetCursorPos(&x, &y);
	int w = Application::GetWindowWidth();
	int h = Application::GetWindowHeight();
	v_mousepos = Vector3(static_cast<float>(x) / (w / m_worldWidth), (h - static_cast<float>(y)) / (h / m_worldHeight), 0.0f);
	if (Ghost->active)
	{
		Ghost->vel = Ghost->pos - v_mousepos;
	}
	// End James 13/8/2019

	static bool bLButtonState = false;
	if (!bLButtonState && Application::IsMousePressed(0))
	{
		bLButtonState = true;
		std::cout << "LBUTTON DOWN" << std::endl;

		// James 13/8/2019
		Ghost->active = true;
		Ghost->pos = v_mousepos;
		// End James 13/8/2019
	}
	else if (bLButtonState && !Application::IsMousePressed(0))
	{
		bLButtonState = false;
		std::cout << "LBUTTON UP" << std::endl;

		// James 13/8/2019
		PhysicsObject *temp = FetchGO();
		temp->type = PhysicsObject::GO_BALL;
		temp->pos = Ghost->pos;
		temp->vel = Ghost->pos - v_mousepos;
		temp->scale.Set(2, 2, 1);
		Ghost->active = false;
		// End James 13/8/2019
		// James 15/8/2019
		//Ball = temp;
		// End James 15/8/2019
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

		endGame = true;
		// James 13/8/2019
		PhysicsObject *temp = FetchGO();
		temp->type = PhysicsObject::GO_PILLAR;
		temp->pos = v_mousepos;
		temp->scale.Set(5, 5, 1);
		temp->normal.Set(1, 0, 0);
		// End James 13/8/2019

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

	// James 13/8/2019
	for (int i = 0; i < TraceSize; ++i)
	{
		Trace[i]->active = false;
	}
	if (Ghost->active && !Ghost->vel.IsZero())
	{
		Vector3 m_gravity(0, -9.8f, 0);
		PhysicsObject temp;
		temp = *Ghost;
		temp.type = PhysicsObject::GO_TRACE;
		float time = 0.f;
		int index = 0;
		float accumulatedtime = 0.f;
		//Vector3 prevpos = Ghost->pos + m_gravity * dt;
		for (float time = 0; time < 5.f; time += dt)
		{
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
	for (int i = 0; i < (int)m_goList->size(); ++i)
	{
		PhysicsObject *go = (*m_goList)[i];
		if (go->active)
		{
			go->Update(dt, m_worldWidth, m_worldHeight);
			if (go == Ball)
			{
				if ((go->pos - Vector3(m_worldWidth * 0.5f, m_worldHeight * 0.5f, 0)).Length() > Maze.getBiggestLength())
				{
					endGame = true;
				}
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
	else
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
}

// James 13/8/2019
bool SceneMaze::CheckCollision(PhysicsObject* go, PhysicsObject* go2)
{
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

float SceneMaze::CheckCollision2(PhysicsObject* go, PhysicsObject* go2)
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

void SceneMaze::Render()
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

	//On screen text
	std::ostringstream ss;
	ss.precision(3);
	ss << "T:" << elapsedTime;
	RenderTextOnScreen(meshList[GEO_TEXT], ss.str(), Color(0, 1, 0), 3, 0, 0);
	// End James 14/8/2019

	if (endGame)
	{
		Results::getInstance()->RenderResults(0, 'A');
	}
}

void SceneMaze::Exit()
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

void SceneMaze::RenderGO(PhysicsObject * go)
{
	switch (go->type)
	{
		// James 13/8/2019
	case PhysicsObject::GO_BALL:
	{
		modelStack.PushMatrix();
		modelStack.Translate(go->pos);
		modelStack.Scale(go->scale);
		RenderMesh(meshList[GEO_BALL], false);
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
		RenderMesh(meshList[GEO_BALL], false);
		modelStack.PopMatrix();
		break;
	}
	// End James 13/8/2019
	default:
		break;
	}
}

PhysicsObject * SceneMaze::FetchGO()
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
void SceneMaze::ActivateStencil()
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

void SceneMaze::DeactivateStencil()
{
	// Switch off alpha test
	glDisable(GL_ALPHA_TEST);
	// Disable stencil test
	glDisable(GL_STENCIL_TEST);
}
// End James 15/8/2019

void SceneMaze::GameEndCalculations() // Setting the stats and other stuff
{
	if (score >= 6000)
	{
		grade = 'S';
		StatManager::GetInstance()->UpdateChar01F(-20);
		StatManager::GetInstance()->UpdateChar01M(20);
		StatManager::GetInstance()->UpdateChar02F(-20);
		StatManager::GetInstance()->UpdateChar02M(20);
		StatManager::GetInstance()->UpdateChar03F(-20);
		StatManager::GetInstance()->UpdateChar03M(20);
		StatManager::GetInstance()->UpdateChar04F(-20);
		StatManager::GetInstance()->UpdateChar04M(20);
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