#include "SheepGame.h"
#include "GL\glew.h"
#include "Source/Application.h"
#include <sstream>
#include "Source/Rendering/LoadTGA.h"
#include "Source/Rendering/MeshBuilder.h"

SheepGame::SheepGame() :
	m_Gravity(0, -9.8, 0),
	m_Timer(1.f),
	BossTimer(10.f),
	Timer1(10.f),
	Timer2(10.f),
	Timer3(10.f),
	Timer1Check(false),
	Timer2Check(false),
	Timer3Check(false),
	patternDone(false),
	gameOver(false)
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

	meshList[GEO_LIVES] = MeshBuilder::GenerateQuad("Lives", Color(1, 1, 1), 1.f);
	meshList[GEO_LIVES]->textureID = LoadTGA("Image//Life.tga");
	
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


	meshList[GEO_SHEEPKING] = MeshBuilder::GenerateQuad("SheepKing", Color(1, 1, 1), 1.f);
	meshList[GEO_SHEEPKING]->textureID = LoadTGA("Image//SheepKing.tga");

	meshList[GEO_EVILSHEEPKING] = MeshBuilder::GenerateQuad("EvilSheepKing", Color(1, 1, 1), 1.f);
	meshList[GEO_EVILSHEEPKING]->textureID = LoadTGA("Image//EvilSheepKing.tga");

	meshList[GEO_GAMEFONT] = MeshBuilder::GenerateText("Text",16,16);
	meshList[GEO_GAMEFONT]->textureID = LoadTGA("Image//KidsZone.tga");

	meshList[GEO_CROSSHAIR] = MeshBuilder::GenerateQuad("CrossHair", Color(1, 1, 1), 1.f);
	meshList[GEO_CROSSHAIR]->textureID = LoadTGA("Image//Crosshair.tga");
	
	meshList[GEO_MAGICCIRCLE] = MeshBuilder::GenerateQuad("Magic_Circle", Color(1, 1, 1), 1.f);
	meshList[GEO_MAGICCIRCLE]->textureID = LoadTGA("Image//MagicCircle.tga");

	meshList[GEO_WARNING] = MeshBuilder::GenerateQuad("Warning", Color(1,1, 1), 1.f);
	meshList[GEO_WARNING]->textureID = LoadTGA("Image//Warning.tga");

	meshList[GEO_LINUX] = MeshBuilder::GenerateQuad("LinuxPenguin", Color(1, 1, 1), 1.f);
	meshList[GEO_LINUX]->textureID = LoadTGA("Image//LinuxPenguin.tga");

	transitionY = 0;
	Transition = false;
	EvilKing = false;

	Mtx44 projection;
	projection.SetToOrtho(0, m_worldWidth, 0, m_worldHeight, -10, 10);
	projectionStack.LoadMatrix(projection);

	pointGain = false;

	tempwall = FetchGO();
	tempwall->type = SheepObject::E_WALL;
	tempwall->pos.Set(m_worldWidth / 2, 5,0);
	tempwall->normal.Set(0, 1,0);
	tempwall->scale.Set(2, m_worldWidth,1);

	EvilKingSheep = FetchGO();
	EvilKingSheep->type = SheepObject::E_EYES;
	EvilKingSheep->pos.Set(m_worldWidth / 2, 5, 0);
	EvilKingSheep->normal.Set(0, 1, 0);
	EvilKingSheep->scale.Set(20, 30, 1);
	EvilKingSheep->health = 150;
	EvilKingSheep->active = true;

	Warning = FetchGO();
	Warning->type = SheepObject::E_WARNING;
	Warning->pos.Set(m_worldWidth/2 , m_worldHeight/2, 0);
	Warning->scale.Set(100, 100, 1);
	Warning->active = false;

	Warning2 = FetchGO();
	Warning2->type = SheepObject::E_WARNING;
	Warning2->pos.Set(m_worldWidth/2 - 50, m_worldHeight / 2, 0);
	Warning2->scale.Set(100, 100, 1);
	Warning2->active = false;

	Warning3 = FetchGO();
	Warning3->type = SheepObject::E_WARNING;
	Warning3->pos.Set(m_worldWidth / 2 + 50, m_worldHeight / 2, 0);
	Warning3->scale.Set(100, 100, 1);
	Warning3->active = false;

	rndNum = 0;

	//Warning3 = FetchGO();
	//Warning3->type = SheepObject::E_WARNING;
	//Warning3->RightBound(m_worldWidth/2)

	//Ray Tracing
	for (int i = 0; i < TraceSize; ++i)
	{
		Trace[i] = new SheepObject;
		Trace[i]->type = SheepObject::E_TRACE;
		Trace[i]->scale.Set(5, 5, 1);
	}

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
	player->active = true;
	player->pos.Set(0, 18, 0);
	player->scale.Set(10, 10, 10);
	player->cooldown = 2.f;
	player->vel.Set(0, 0, 0);
	player->health = 3;
	points = 0;

	startPhase = false;
	m_goList.push_back(player);
}

void SheepGame::Update(double dt)
{
	SceneBase::Update(dt);
	//Calculating aspect ratio
	m_worldHeight = 100.f;
	m_worldWidth = m_worldHeight * (float)Application::GetWindowWidth() / Application::GetWindowHeight();

	tempwall->pos.Set(m_worldWidth / 2, 5);
	tempwall->scale.Set(2, m_worldWidth, 1);

	//Warnings

	//Warning->pos.Set(m_worldWidth / 2, m_worldHeight / 2, 0);
	//Warning->scale.Set(100, 100, 1);

	//Warning2->pos.Set(m_worldWidth / 2 - 50, m_worldHeight / 2, 0);
	//Warning2->scale.Set(100, 100, 1);

	//Warning3->pos.Set(m_worldWidth / 2 + 50, m_worldHeight / 2, 0);
	//Warning3->scale.Set(100, 100, 1);
	static bool bLButtonState = false;

	//Mouse Position
	double x, y;
	Application::GetCursorPos(&x, &y);

	int w = Application::GetWindowWidth();
	int h = Application::GetWindowHeight();
	mousePos = Vector3(static_cast<float>(x) / (w / m_worldWidth), (h - static_cast<float>(y)) / (h / m_worldHeight), 0.0f);



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
			Fireball->vel.Set(((x / w * m_worldWidth) - player->pos.x), ((m_worldHeight - y / h * m_worldHeight) - player->pos.y), 0);
			Fireball->vel = 85 * Fireball->vel.Normalized();
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
		Sheep->pos.Set(m_worldWidth - 10, Math::RandFloatMinMax(m_worldHeight / 3, m_worldHeight / 2), 0);
		Sheep->active = true;
		Sheep->isDown = false;
		m_Timer = Math::RandFloatMinMax(2, 5);


		SheepObject* Sheep2 = FetchGO();
		Sheep2->type = SheepObject::E_SHEEP;
		Sheep2->scale.Set(10, 10, 10);
		Sheep2->vel.Set(Math::RandFloatMinMax(10, 20), Math::RandFloatMinMax(10, 15), 0);
		Sheep2->pos.Set(0, Math::RandFloatMinMax(m_worldHeight / 3, m_worldHeight / 2), 0);
		Sheep2->active = true;
		Sheep2->isDown = false;
		m_Timer = Math::RandFloatMinMax(2, 5);
	}
	if (BossTimer < 0 && !startPhase)
	{
		rndNum = Math::RandIntMinMax(1, 3);
		BossTimer = 100.f;
	}
	switch (rndNum)
	{
	case 1:
		Pattern1(dt);
		break;
	case 2:
		Pattern2(dt);
		break;
	case 3:
		Pattern3(dt);
		break;
	default:
		cout << "???" << endl;
		break;
	}
	/*if (!patternDone && Timer1Check)
	{
		Pattern1(dt);
	}
	if (!patternDone && Timer2Check)
	{
		Pattern2(dt);
	}
	if (!patternDone && Timer3Check)
	{
		Pattern3(dt);
	}*/
	if (patternDone == true)
	{
		Timer1 = 10.f;
		Timer2 = 10.f;
		Timer3 = 10.f;
		patternDone = false;
		startPhase = false;
		BossTimer = Math::RandFloatMinMax(30.f, 40.f);
		stop1 = false;
		stop2 = false;
		stop3 = false;
		rndNum = 0;
	}
	//Iterator for sheep objects
	for (std::vector<SheepObject *>::iterator it = m_goList.begin(); it != m_goList.end(); ++it)
	{
		SheepObject *go = (SheepObject *)*it;
		if(go->active)
		{ 
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
				if (go->isDown == true)
				{
					go->vel.y -= sin(m_Gravity.y) * 2;
					//go->vel += m_Gravity * dt;
				}
				if (go->pos.x < 0)
				{
					go->active = false;
				}
				//if (go->isDown == false)
				//{
				//	go->vel.y += sin(m_Gravity.y) * 2;
				//}
				
			}
			if (go->type == SheepObject::E_SHEEP)
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
				if (go->isDown == true)
				{
					go->vel.y -= sin(m_Gravity.y) * 2;
					//go->vel += m_Gravity * dt;
				}
				if (go->pos.x > m_worldWidth)
				{
					go->active = false;
				}
				//if (go->isDown == false)
				//{
				//	go->vel.y += sin(m_Gravity.y) * 2;
				//}
			}
		if (go->type == SheepObject::E_LINUX)
		{
			go->pos += go->vel * (float)dt;
			if (go->pos.y < -1)
			{
				go->active = false;
			}
		}
		if (go->type == SheepObject::E_FIREBALL)
		{
			go->pos += go->vel * (float)dt;
		}
		for (std::vector<SheepObject *>::iterator it2 = m_goList.begin(); it2 != m_goList.end(); ++it2)
		{
			SheepObject* go2 = (SheepObject *)*it2;
			if (go2->active)
			{
				if (go2->type == SheepObject::E_WALL && go->type != SheepObject::E_LINUX)
				{
					if (CollisionCheck(go, go2))
					{
						go->vel.y = -go->vel.y;
						//cout << CollisionCheck(go2,go) << endl;
					}
				}
				if (go2->type == SheepObject::E_FIREBALL && go->type == SheepObject::E_SHEEPFLIPPED
					|| go2->type == SheepObject::E_FIREBALL && go->type == SheepObject::E_SHEEP)
				{
					if (CollisionCheck(go, go2))
					{
						go->active = false;
						go2->active = false;
						pointGain = true;
					}
				}
				if (go2->type == SheepObject::E_FIREBALL && go->type == SheepObject::E_EYES)
				{
					if (CollisionCheck(go, go2))
					{
						cout << "hit" << endl;
						go2->active = false;
						points += 100;
						EvilKingSheep->health -= 10;
					}
				}
				if (go2->type == SheepObject::E_SHEEPFLIPPED && go->type == SheepObject::E_PLAYER 
					|| go2->type == SheepObject::E_SHEEP && go->type == SheepObject::E_PLAYER
					|| go2->type == SheepObject::E_LINUX && go->type == SheepObject::E_PLAYER)
				{
					if (CollisionCheck(go2, go))
					{
						go2->active = false;
						player->health -= 1;
						cout << player->health << endl;
					}
				}

			}
		}

		}
	}
	if (EvilKingSheep->health == 100 || player->health == 0)
	{
		gameOver = true;
	}
	if (points > 150)
	{
		Transition = true;
	}
	if (player->onCooldown)
	{
		player->cooldown -= dt;
	}
	if (player->cooldown < 0)
	{
		player->cooldown = 1.f;
		player->onCooldown = false;
	}
	if (pointGain)
	{
		points += 20;
		pointGain = false;
	}
	if (Transition == true)
	{
		meshList[GEO_LIFEBAR] = MeshBuilder::GenerateBar("GEO_LIFEBAR", Color(1, 0, 0), EvilKingSheep->health / 2, 1.f);
	}
	UpdateRayTracing(dt);
	player->UpdateMovement(dt);
	m_Timer -= dt;
	if (Transition == true)
	{
		BossTimer -= dt;
	}
}
void SheepGame::Pattern1(double dt)
{
	cout << "Pattern 1" << endl;

	Timer1 -= dt;
	if (Timer1 < 10)
	{
		if (!stop1)
		{
			Warning->active = true;
		}
		if (Timer1 < 8)
		{
			Timer2 -= dt;
			if (Timer2 < 10)
			{
				if (!stop2)
				{
					Warning2->active = true;
				}
			}
			if (Timer2 < 8)
			{
				Timer3 -= dt;
				if (Timer3 < 10)
				{
					if (!stop3)
					{
						Warning3->active = true;
					}
					if (Timer3 < 0 && Warning3->active == true)
					{
						SheepObject* Linux = FetchGO();
						Linux->type = SheepObject::E_LINUX;
						Linux->scale.Set(40, 40, 40);
						Linux->vel.Set(0, -15.f, 0);
						Linux->pos.Set(m_worldWidth / 2 + 35, m_worldHeight, 0);
						Linux->active = true;
						Linux->isDown = false;
						Warning3->active = false;
						Timer3Check = false;
						patternDone = true;
						stop3 = true;
					}
				}
				if (Timer2 < 0 && Warning2->active == true)
				{
					SheepObject* Linux = FetchGO();
					Linux->type = SheepObject::E_LINUX;
					Linux->scale.Set(40, 40, 40);
					Linux->vel.Set(0, -15.f, 0);
					Linux->pos.Set(m_worldWidth / 2 - 65, m_worldHeight, 0);
					Linux->active = true;
					Linux->isDown = false;
					Warning2->active = false;
					Timer2Check = false;
					stop2 = true;
				}
			}
			if (Timer1 < 0 && Warning->active == true)
			{
				SheepObject* Linux = FetchGO();
				Linux->type = SheepObject::E_LINUX;
				Linux->scale.Set(40, 40, 40);
				Linux->vel.Set(0, -15.f, 0);
				Linux->pos.Set(m_worldWidth / 2 - 15, m_worldHeight, 0);
				Linux->active = true;
				Linux->isDown = false;
				Warning->active = false;
				Timer1Check = false;
				stop1 = true;
			}
		}
	}
	
	/*if (Timer1Check)
	{
	}
	if (Timer2Check)
	{
		Timer2 -= dt;
	}
	if (Timer3Check)
	{

	}*/
}
void SheepGame::Pattern2(double dt)
{
	cout << "Pattern 2" << endl;

	Timer2 -= dt;
	if (Timer2 < 10)
	{
		if (!stop2)
		{
			Warning2->active = true;
		}
		if (Timer2 < 8)
		{
			Timer1 -= dt;
			if (Timer1 < 10)
			{
				if (!stop1)
				{
					Warning->active = true;
				}
			}
			if (Timer1 < 8)
			{
				Timer3 -= dt;
				if (Timer3 < 10)
				{
					if (!stop3)
					{
						Warning3->active = true;
					}
					if (Timer3 < 0 && Warning3->active == true)
					{

						SheepObject* Linux = FetchGO();
						Linux->type = SheepObject::E_LINUX;
						Linux->scale.Set(40, 40, 40);
						Linux->vel.Set(0, -15.f, 0);
						Linux->pos.Set(m_worldWidth / 2 - 15, m_worldHeight, 0);
						Linux->active = true;
						Linux->isDown = false;
						Warning2->active = false;
						Timer2Check = false;
						stop2 = true;
					}
				}
				if (Timer1 < 0 && Warning->active == true)
				{
					SheepObject* Linux = FetchGO();
					Linux->type = SheepObject::E_LINUX;
					Linux->scale.Set(40, 40, 40);
					Linux->vel.Set(0, -15.f, 0);
					Linux->pos.Set(m_worldWidth / 2 - 65, m_worldHeight, 0);
					Linux->active = true;
					Linux->isDown = false;
					Warning->active = false;
					Timer1Check = false;
					stop1 = true;
				}
			}
			if (Timer2 < 0 && Warning2->active == true)
			{
				SheepObject* Linux = FetchGO();
				Linux->type = SheepObject::E_LINUX;
				Linux->scale.Set(40, 40, 40);
				Linux->vel.Set(0, -15.f, 0);
				Linux->pos.Set(m_worldWidth / 2 + 35, m_worldHeight, 0);
				Linux->active = true;
				Linux->isDown = false;
				Warning3->active = false;
				Timer3Check = false;
				patternDone = true;
				stop3 = true;
			}
		}
	}
}
void SheepGame::Pattern3(double dt)
{
	cout << "Pattern 3" << endl;

	Timer3 -= dt;
	if (Timer3 < 10)
	{
		if (!stop3)
		{
			Warning3->active = true;
		}
		if (Timer3 < 8)
		{
			Timer2 -= dt;
			if (Timer2 < 10)
			{
				if (!stop2)
				{
					Warning2->active = true;
				}
			}
			if (Timer2 < 8)
			{
				Timer1 -= dt;
				if (Timer1 < 10)
				{
					if (!stop1)
					{
						Warning->active = true;
					}
					if (Timer1 < 0 && Warning->active == true)
					{
						SheepObject* Linux = FetchGO();
						Linux->type = SheepObject::E_LINUX;
						Linux->scale.Set(40, 40, 40);
						Linux->vel.Set(0, -15.f, 0);
						Linux->pos.Set(m_worldWidth / 2 + 35, m_worldHeight, 0);
						Linux->active = true;
						Linux->isDown = false;
						Warning->active = false;
						Timer1Check = false;
						patternDone = true;
						stop1 = true;
					}
				}
				if (Timer2 < 0 && Warning2->active == true)
				{
					SheepObject* Linux = FetchGO();
					Linux->type = SheepObject::E_LINUX;
					Linux->scale.Set(40, 40, 40);
					Linux->vel.Set(0, -15.f, 0);
					Linux->pos.Set(m_worldWidth / 2 - 15, m_worldHeight, 0);
					Linux->active = true;
					Linux->isDown = false;
					Warning3->active = false;
					Timer3Check = false;
					stop3 = true;
				}
			}
			if (Timer3 < 0 && Warning3->active == true)
			{


				SheepObject* Linux = FetchGO();
				Linux->type = SheepObject::E_LINUX;
				Linux->scale.Set(40, 40, 40);
				Linux->vel.Set(0, -15.f, 0);
				Linux->pos.Set(m_worldWidth / 2 - 65, m_worldHeight, 0);
				Linux->active = true;
				Linux->isDown = false;
				Warning2->active = false;
				Timer2Check = false;
				stop2 = true;
			}
		}
	}
}
void SheepGame::UpdateRayTracing(double dt)
{
	// James 13/8/2019
	for (int i = 0; i < TraceSize; ++i)
	{
		Trace[i]->active = false;
	}
	SheepObject temp;
	temp.vel = mousePos - player->pos;
	temp.vel = 85.f * temp.vel.Normalized();
	temp.type = SheepObject::E_TRACE;
	temp.scale.Set(3, 3, 3);
	temp.pos = player->pos;
	temp.active = true;
	float time = 0.f;
	int index = 0;
	float accumulatedtime = 0.f;
	float totaldist = 0.f;
	//Vector3 prevpos = Ghost->pos + m_gravity * dt;
	for (float time = 0; time < 5.f; time += dt)
	{
		if (totaldist > (mousePos - player->pos).Length())
		{
			break;
		}
		if (!temp.active)
		{
			break;
		}
		temp.pos += temp.vel * dt;
		accumulatedtime += temp.vel.Length() * dt;
		totaldist += temp.vel.Length() * dt;
		//for (int k = 0; k < (int)m_goList.size(); ++k)
		//{
		//	SheepObject* go2 = (m_goList)[k];
		//	if (go2->active && go2->type != SheepObject::E_PLAYER)
		//	{
		//		if (CollisionCheck(&temp, go2))
		//		{
		//			temp.active = false;
		//			break;
		//			//CollisionResponse(&temp, go2, dt);
		//		}
		//	}
		//}
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
	case SheepObject::E_PLAYER:
	{
		Vector3 dist = go2->pos - go->pos;
		//Vector3 u = go->vel - go2->vel;
		if (dist.Length() < (go->scale.x/2) + (go2->scale.x/2))
		{
			return true;
		}
		break;
	}
	case SheepObject::E_FIREBALL:
	{
		Vector3 dist = go2->pos - go->pos;
		Vector3 u = go->vel - go2->vel;
		if (dist.Length() < (go->scale.x/2) + (go2->scale.x/2) && u.Dot(dist) > 0.0f)
		{
			return true;
		}
		break;
	}
	case SheepObject::E_EYES:
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
		if (Transition == true)
		{
			if (EvilKingSheep->health > 0)
			{
				renderEvilSheep();
				if (transitionY < m_worldHeight / 2)
				{
					transitionY += 0.5f;
				}
				else
				{
					EvilKing = true;
					modelStack.PushMatrix();
					modelStack.Translate(m_worldWidth / 2 - 50, m_worldHeight - 10, 0);
					modelStack.Scale(3, 3, 1);
					RenderMesh(meshList[GEO_LIFEBAR], false);
					modelStack.PopMatrix();
				}
			}
			else
			{
				EvilKingSheep->active = false;
			}
		}
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
		for (int i = 0; i < TraceSize; ++i)
		{
			if (Trace[i]->active)
			{
				RenderGO(Trace[i]);
			}
		}
		renderLives();
		renderCrossHair();

}
void SheepGame::renderCrossHair()
{
	modelStack.PushMatrix();
	modelStack.Translate(mousePos);
	modelStack.Scale(5, 5, 1);
	RenderMesh(meshList[GEO_CROSSHAIR], false);
	modelStack.PopMatrix();
}

void SheepGame::renderEvilSheep()
{
	if (EvilKing == false)
	{
		modelStack.PushMatrix();
		modelStack.Translate(m_worldWidth / 2, transitionY, 0);
		modelStack.Scale(80, 80, 1);
		RenderMesh(meshList[GEO_SHEEPKING], false);
		modelStack.PopMatrix();
	}
	if (EvilKing == true)
	{
		modelStack.PushMatrix();
		modelStack.Translate(m_worldWidth / 2, transitionY, 0);
		modelStack.Scale(80, 80, 1);
		RenderMesh(meshList[GEO_EVILSHEEPKING], false);
		modelStack.PopMatrix();

		EvilKingSheep->pos.Set(m_worldWidth / 2, transitionY, 0);
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
void SheepGame::renderLives()
{
	if (player->health >= 3)
	{
		modelStack.PushMatrix();
		modelStack.Translate(20, m_worldHeight - 10, 0);
		modelStack.Scale(3, 3, 3);
		RenderMesh(meshList[GEO_LIVES], false);
		modelStack.PopMatrix();
	}
	if (player->health >= 2)
	{
		modelStack.PushMatrix();
		modelStack.Translate(15, m_worldHeight - 10, 0);
		modelStack.Scale(3, 3, 3);
		RenderMesh(meshList[GEO_LIVES], false);
		modelStack.PopMatrix();
	}
	if (player->health >= 1)
	{
		modelStack.PushMatrix();
		modelStack.Translate(10, m_worldHeight - 10, 0);
		modelStack.Scale(3, 3, 3);
		RenderMesh(meshList[GEO_LIVES], false);
		modelStack.PopMatrix();
	}
	std::ostringstream ss;
	ss.precision(3);
	ss << "Score : " << points;
	RenderTextOnScreen(meshList[GEO_GAMEFONT], ss.str(), Color(0, 1, 1), 2, 0, 0);
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
	case SheepObject::E_LINUX:
	{
		modelStack.PushMatrix();
		modelStack.Translate(go->pos.x, go->pos.y, go->pos.z);
		modelStack.Scale(go->scale.x, go->scale.y, go->scale.z);
		RenderMesh(meshList[GEO_LINUX], false);
		modelStack.PopMatrix();
		break;
	}
	case  SheepObject::E_FIREBALL:
	{
		modelStack.PushMatrix();
		modelStack.Translate(go->pos.x, go->pos.y, go->pos.z);
		modelStack.Rotate(90, 0, 0, 1);
		modelStack.Scale(go->scale.x, go->scale.y, go->scale.z);
		RenderMesh(meshList[GEO_FIREBALL], false);
		modelStack.PopMatrix();
		break;
	}
	case SheepObject::E_WARNING:
	{
		modelStack.PushMatrix();
		modelStack.Translate(go->pos.x, go->pos.y, go->pos.z);
		modelStack.Scale(go->scale.x, go->scale.y, go->scale.z);
		RenderMesh(meshList[GEO_WARNING], false);
		modelStack.PopMatrix();
		break;
	}
	case SheepObject::E_TRACE:
	{
		modelStack.PushMatrix();
		modelStack.Translate(go->pos.x, go->pos.y, go->pos.z);
		modelStack.Scale(go->scale.x, go->scale.y, go->scale.z);
		RenderMesh(meshList[GEO_MAGICCIRCLE], false);
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
	//case SheepObject::E_EYES:
	//{
	//	modelStack.PushMatrix();
	//	modelStack.Translate(go->pos);
	//	modelStack.Rotate(Math::RadianToDegree(atan2(go->normal.y, go->normal.x)), 0, 0, 1);
	//	modelStack.Scale(go->scale);
	//	RenderMesh(meshList[GEO_WALL], false);
	//	modelStack.PopMatrix();
	//}
	default:
		break;
	}
}

SheepObject* SheepGame::FetchGO()
{
	for (int i = 0; i < m_goList.size(); i++)
	{
		if (m_goList[i] == Warning || m_goList[i] == Warning2 || m_goList[i] == Warning3)
		{
			continue;
		}
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