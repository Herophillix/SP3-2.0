#include "SheepGame.h"
#include "GL\glew.h"
#include "..\Application.h"
#include <sstream>
#include "..\Rendering\LoadTGA.h"
#include "..\Rendering\MeshBuilder.h"

SheepGame::SheepGame() :
	m_Gravity(0, -9.8f, 0),
	m_Timer(1.f),
	BossTimer(10.f),
	Timer1(10.f),
	Timer2(10.f),
	Timer3(10.f),
	Timer1Check(false),
	Timer2Check(false),
	Timer3Check(false),
	patternDone(false),
	gameOver(false),
	statsGain(false),
	isFiring(false),
	m_Grade('F'),
	fireRate(0.5f),
	SheepkingHit(false),
	timer(0.3f),
	Modifier(0.f),
	isInstructions(true),
	playMusic(false),
	bounceTime(0.5f)
{

}

SheepGame::~SheepGame()
{
}

void SheepGame::Init()
{
	SceneBase::Init();
	Results::getInstance()->InitVars();

	//Calculating aspect ratio
	m_worldHeight = 100.f;
	m_worldWidth = m_worldHeight * (float)Application::GetWindowWidth() / Application::GetWindowHeight();
	cout <<
		"Scene Sheep " << endl;
	//Variables here
	Math::InitRNG();
	blKeyboardState = false;
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

	meshList[GEO_LIGHTNING] = MeshBuilder::GenerateQuad("Lightning", Color(1, 1, 1), 1.f);
	meshList[GEO_LIGHTNING]->textureID = LoadTGA("Image//LightningBolt.tga");

	meshList[GEO_CHARACTER04_IDLE_RIGHT] = MeshBuilder::GenerateSpriteAnimation("c04_idle_right", 1, 4);
	meshList[GEO_CHARACTER04_IDLE_RIGHT]->textureID = LoadTGA("Image//CharacterSprites//Idle//wizzard_idle_anim_right.tga");

	meshList[GEO_CHARACTER04_IDLE_LEFT] = MeshBuilder::GenerateSpriteAnimation("c04_idle_left", 1, 4);
	meshList[GEO_CHARACTER04_IDLE_LEFT]->textureID = LoadTGA("Image//CharacterSprites//Idle//wizzard_idle_anim_left.tga");

	meshList[GEO_CHARACTER04_MOVE_LEFT] = MeshBuilder::GenerateSpriteAnimation("c04_move_left", 1, 4);
	meshList[GEO_CHARACTER04_MOVE_LEFT]->textureID = LoadTGA("Image//CharacterSprites//Move//wizzard_run_anim_left.tga");

	meshList[GEO_CHARACTER04_MOVE_RIGHT] = MeshBuilder::GenerateSpriteAnimation("c04_move_right", 1, 4);
	meshList[GEO_CHARACTER04_MOVE_RIGHT]->textureID = LoadTGA("Image//CharacterSprites//Move//wizzard_run_anim_right.tga");

	meshList[GEO_MANABAR] = MeshBuilder::GenerateQuad("Manabar", Color(0, 0, 1), 1.f);
	meshList[GEO_LIFEBAR] = MeshBuilder::GenerateQuad("Lifebar", Color(1, 0, 0), 1.f);


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

	meshList[GEO_SHEEPKINGHIT] = MeshBuilder::GenerateQuad("SheepKingHit", Color(1, 1, 1), 1.f);
	meshList[GEO_SHEEPKINGHIT]->textureID = LoadTGA("Image//EvilSheepKingHurt.tga");

	meshList[GEO_METEORWOOL] = MeshBuilder::GenerateQuad("MeteorWool", Color(1, 1, 1), 1.f);
	meshList[GEO_METEORWOOL]->textureID = LoadTGA("Image//WoolMeteor.tga");

	meshList[GEO_PARTICLE_TEST] = MeshBuilder::GenerateQuad("testParticle", Color(1, 1, 1), 1.f);
	meshList[GEO_PARTICLE_TEST]->textureID = LoadTGA("Image//Smoke.tga");

	meshList[GEO_HAM] = MeshBuilder::GenerateQuad("Ham", Color(1, 1, 1), 1.f);
	meshList[GEO_HAM]->textureID = LoadTGA("Image//Ham.tga");

	meshList[GEO_ELECTROCUTED] = MeshBuilder::GenerateQuad("Electrocuted", Color(1, 1, 1), 1.f);
	meshList[GEO_ELECTROCUTED]->textureID = LoadTGA("Image//SheepElectrocuted.tga");

	meshList[GEO_ELECTROCUTEDR] = MeshBuilder::GenerateQuad("ElectrocutedR", Color(1, 1, 1), 1.f);
	meshList[GEO_ELECTROCUTEDR]->textureID = LoadTGA("Image//SheepElectrocutedR.tga");

	meshList[GEO_INSTRUCT] = MeshBuilder::GenerateQuad("Instruction", Color(1, 1, 1), 1.f);
	meshList[GEO_INSTRUCT]->textureID = LoadTGA("Image//InstructionsSheep.tga");

	transitionY = 0;
	Transition = false;
	EvilKing = false;

	m_particleCount = 0;
	MAX_PARTICLES = 10;


	//Sound
	SoundSystem.AddSound("Fireball_Cast", "Sounds//Fireball_Cast.wav");
	SoundSystem.AddSound("Fireball_Explosion", "Sounds//Fireball_Explosion.wav");
	SoundSystem.AddSound("Lightning_Bolt", "Sounds//Lightning_Bolt.wav");
	SoundSystem.AddSound("Sheep", "Sounds//Sheep.mp3");
	Mtx44 projection;
	projection.SetToOrtho(0, m_worldWidth, 0, m_worldHeight, -10, 10);
	projectionStack.LoadMatrix(projection);

	pointGain = false;

	tempwall = FetchGO();
	tempwall->setType(SheepObject::E_WALL);
	tempwall->setPos(Vector3(m_worldWidth / 2, 5,0));
	tempwall->normal.Set(0, 1,0);
	tempwall->setScale(Vector3(2, m_worldWidth,1));

	EvilKingSheep = FetchGO();
	EvilKingSheep->setType(SheepObject::E_EYES);
	EvilKingSheep->setPos(Vector3(m_worldWidth / 2, 5, 0));
	EvilKingSheep->normal.Set(0, 1, 0);
	EvilKingSheep->setScale(Vector3(20, 30, 1));
	EvilKingSheep->setHealth(200);
	EvilKingSheep->setActive(true);

	Warning = FetchGO();
	Warning->setType(SheepObject::E_WARNING);
	Warning->setPos(Vector3(m_worldWidth/2 , m_worldHeight/2, 0));
	Warning->setScale(Vector3(100, 100, 1));
	Warning->setActive(false);

	Warning2 = FetchGO();
	Warning2->setType(SheepObject::E_WARNING);
	Warning2->setPos(Vector3(m_worldWidth/2 - 50, m_worldHeight / 2, 0));
	Warning2->setScale(Vector3(100, 100, 1));
	Warning2->setActive(false);

	Warning3 = FetchGO();
	Warning3->setType(SheepObject::E_WARNING);
	Warning3->setPos(Vector3(m_worldWidth / 2 + 65, m_worldHeight / 2, 0));
	Warning3->setScale(Vector3(100, 100, 1));
	Warning3->setActive(false);

	rndNum = 0;
	//Warning3 = FetchGO();
	//Warning3->type = SheepObject::E_WARNING;
	//Warning3->RightBound(m_worldWidth/2)

	//Ray Tracing
	for (int i = 0; i < TraceSize; ++i)
	{
		Trace[i] = new SheepObject;
		Trace[i]->setType(SheepObject::E_TRACE);
		Trace[i]->setScale(Vector3(5, 5, 1));
	}

	SpriteAnimation *C04IL = dynamic_cast<SpriteAnimation *>(meshList[GEO_CHARACTER04_IDLE_LEFT]);
	if (C04IL)
	{
		C04IL->m_anim = new Animation();
		C04IL->m_anim->Set(0, 3, 0, 1.f, true);
	}

	SpriteAnimation *C04IR = dynamic_cast<SpriteAnimation *>(meshList[GEO_CHARACTER04_IDLE_RIGHT]);
	if (C04IR)
	{
		C04IR->m_anim = new Animation();
		C04IR->m_anim->Set(0, 3, 0, 1.f, true);
	}

	SpriteAnimation *C04ML = dynamic_cast<SpriteAnimation *>(meshList[GEO_CHARACTER04_MOVE_LEFT]);
	if (C04ML)
	{
		C04ML->m_anim = new Animation();
		C04ML->m_anim->Set(0, 3, 0, 1.f, true);
	}

	SpriteAnimation *C04MR = dynamic_cast<SpriteAnimation *>(meshList[GEO_CHARACTER04_MOVE_RIGHT]);
	if (C04MR)
	{
		C04MR->m_anim = new Animation();
		C04MR->m_anim->Set(0, 3, 0, 1.f, true);
	}

	player = new SheepObject(SheepObject::E_PLAYER);
	player->setActive(true);
	player->setPos(Vector3(0, 18, 0));
	player->setScale(Vector3(10, 10, 10));
	player->setCooldown(2.f);
	player->vel.Set(0, 0, 0);
	player->setHealth(3);
	player->setMana(100);
	ManaRegen = 3.f;
	points = 0;

	startPhase = false;
	m_goList.push_back(player);
}

void SheepGame::reset()
{

	transitionY = 0;
	Transition = false;
	EvilKing = false;
	gameOver = false;
	isInstructions = true;
	blKeyboardState = false;
	pointGain = false;
	rndNum = 0;
	player->setActive(true);
	player->setPos(Vector3(0, 18, 0));
	player->setScale(Vector3(10, 10, 10));
	player->setCooldown(2.f);
	player->setMana(100.0f);
	player->vel.Set(0, 0, 0);
	player->setHealth(3);
	points = 0;
	statsGain = false;

	Warning3->setType(SheepObject::E_WARNING);
	Warning3->setPos(Vector3(m_worldWidth / 2 + 50, m_worldHeight / 2, 0));
	Warning3->setScale(Vector3(100, 100, 1));
	Warning3->setActive(false);

	Warning2->setType(SheepObject::E_WARNING);
	Warning2->setPos(Vector3(m_worldWidth / 2 - 50, m_worldHeight / 2, 0));
	Warning2->setScale(Vector3(100, 100, 1));
	Warning2->setActive(false);

	Warning->setType(SheepObject::E_WARNING);
	Warning->setPos(Vector3(m_worldWidth / 2, m_worldHeight / 2, 0));
	Warning->setScale(Vector3(100, 100, 1));
	Warning->setActive(false);

	EvilKingSheep->setType(SheepObject::E_EYES);
	EvilKingSheep->setPos(Vector3(m_worldWidth / 2, 5, 0));
	EvilKingSheep->normal.Set(0, 1, 0);
	EvilKingSheep->setScale(Vector3(20, 30, 1));
	EvilKingSheep->setHealth(150);
	EvilKingSheep->setActive(true);

	tempwall->setType(SheepObject::E_WALL);
	tempwall->setPos(Vector3(m_worldWidth / 2, 5, 0));
	tempwall->normal.Set(0, 1, 0);
	tempwall->setScale(Vector3(2, m_worldWidth, 1));
}

void SheepGame::Update(double dt)
{
	if (StatManager::GetInstance()->GetBool_Game(5))
	{
		reset();
		StatManager::GetInstance()->SetBool_Sheep(false);
	}
	bounceTime -= (float)dt;
	//CHEAT CODES BY SEAN
//Transition to maze
	if (Application::IsKeyPressed(VK_NUMPAD1) && bounceTime < 0)
	{
		Application::setScene(1);
		SoundSystem.stopAllMusic();
		reset();
		bounceTime = 0.5f;
	}
	//Transition to Mole
	if (Application::IsKeyPressed(VK_NUMPAD2) && bounceTime < 0)
	{
		Application::setScene(2);
		SoundSystem.stopAllMusic();
		reset();
		bounceTime = 0.5f;
	}
	//Transition to Tank Scene
	if (Application::IsKeyPressed(VK_NUMPAD3) && bounceTime < 0)
	{
		Application::setScene(3);
		SoundSystem.stopAllMusic();
		reset();
		bounceTime = 0.5f;
	}
	//Transition to Frog Scene
	if (Application::IsKeyPressed(VK_NUMPAD4) && bounceTime < 0)
	{
		Application::setScene(4);
		SoundSystem.stopAllMusic();
		reset();
		bounceTime = 0.5f;
	}
	//Transition to Main Scene
	if (Application::IsKeyPressed(VK_NUMPAD5) && bounceTime < 0)
	{
		Application::setScene(0);
		SoundSystem.stopAllMusic();
		reset();
		bounceTime = 0.5f;
	}
	//CHEAT CODES BY SEAN
	SceneBase::Update(dt);
			if (gameOver)
			{
				Results::getInstance()->UpdateVars(dt);
				player->setActive(false);
				//SoundSystem.stopAllMusic();
				if (!statsGain)
				{
					GameEndCalculations();
					StatManager::GetInstance()->SetCharsOriginalValues();
					//reset();
					statsGain = true;
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
			//Calculating aspect ratio
			m_worldHeight = 100.f;
			m_worldWidth = m_worldHeight * (float)Application::GetWindowWidth() / Application::GetWindowHeight();

			tempwall->setPos(Vector3(m_worldWidth / 2, 5, 0));
			tempwall->setScale(Vector3(2, m_worldWidth, 1));

			static bool bLButtonState = false;

			//Mouse Position
			double x, y;
			Application::GetCursorPos(&x, &y);

			int w = Application::GetWindowWidth();
			int h = Application::GetWindowHeight();
			mousePos = Vector3(static_cast<float>(x) / (w / m_worldWidth), (h - static_cast<float>(y)) / (h / m_worldHeight), 0.0f);
			if (!isInstructions)
			{

				if (!gameOver)
				{
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
					if (!player->getOnCooldown())
					{
						SoundSystem.PlayASound("Fireball_Cast");
						SheepObject *Fireball = FetchGO();
						Fireball->setType(SheepObject::E_FIREBALL);
						Fireball->setPos(player->getPos());
						Fireball->vel.Set((((float)x / w * m_worldWidth) - player->getPos().x), ((m_worldHeight - (float)y / h * m_worldHeight) - player->getPos().y), 0);
						Fireball->vel = 85 * Fireball->vel.Normalized();
						Fireball->setScale(Vector3(8, 8, 8));
						player->setOnCoolDown(true);
					}

					std::cout << "LBUTTON UP" << std::endl;
				}
				static bool bRButtonState = false;
				if (!bRButtonState && Application::IsMousePressed(1))
				{
					bRButtonState = true;
					isFiring = true;
					std::cout << "RBUTTON DOWN" << std::endl;
				}
				else if (bRButtonState && !Application::IsMousePressed(1))
				{

					isFiring = false;
					bRButtonState = false;
					std::cout << "RBUTTON UP" << std::endl;
				}
				if (m_Timer < 0)
				{
					SoundSystem.PlayASound("Sheep");
					SheepObject* Sheep = FetchGO();
					Sheep->setType(SheepObject::E_SHEEPFLIPPED);
					Sheep->setScale(Vector3(10, 10, 10));
					Sheep->vel.Set(Math::RandFloatMinMax(-10, -20), Math::RandFloatMinMax(10, 15), 0);
					Sheep->setPos(Vector3(m_worldWidth - 10, Math::RandFloatMinMax(m_worldHeight / 3, m_worldHeight / 2), 0));
					Sheep->setActive(true);
					Sheep->setIsDown(false);
					m_Timer = Math::RandFloatMinMax(2, 5);


					SheepObject* Sheep2 = FetchGO();
					Sheep2->setType(SheepObject::E_SHEEP);
					Sheep2->setScale(Vector3(10, 10, 10));
					Sheep2->vel.Set(Math::RandFloatMinMax(10, 20), Math::RandFloatMinMax(10, 15), 0);
					Sheep2->setPos(Vector3(0, Math::RandFloatMinMax(m_worldHeight / 3, m_worldHeight / 2), 0));
					Sheep2->setActive(true);
					Sheep2->setIsDown(false);
					m_Timer = Math::RandFloatMinMax(2, 5);
				}
				if (isFiring == true && player->getMana() > 0 && fireRate <= 0)
				{
					SoundSystem.PlayASound("Lightning_Bolt");
					SheepObject *LightningBolt = FetchGO();
					LightningBolt->setType(SheepObject::E_LIGHTNING);
					LightningBolt->setPos(player->getPos());
					LightningBolt->vel.Set((((float)x / w * m_worldWidth) - player->getPos().x), ((m_worldHeight - (float)y / h * m_worldHeight) - player->getPos().y), 0);
					LightningBolt->vel = 100 * LightningBolt->vel.Normalized();
					LightningBolt->setScale(Vector3(8, 8, 8));
					player->setMana(-20, true);
				}
				if (BossTimer < 0 && !startPhase)
				{
					rndNum = Math::RandIntMinMax(1, 3);
					BossTimer = 100.f;
				}
				switch (rndNum)
				{
				case 1:
					cout << "Pattern 1" << endl;
					Pattern1(dt);
					break;
				case 2:
					cout << "Pattern 2 " << endl;
					Pattern2(dt);
					break;
				case 3:
					cout << "pattern3" << endl;
					Pattern3(dt);
					break;
				default:
					break;
				}

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

				//Iterator for sheep objects
				for (std::vector<SheepObject *>::iterator it = m_goList.begin(); it != m_goList.end(); ++it)
				{
					SheepObject *go = (SheepObject *)*it;
					if (go->getActive())
					{
						if (go->getType() == SheepObject::E_SHEEPFLIPPED)
						{
							go->setPos(go->vel * (float)dt, true);
							if (go->getPos().y > m_worldHeight - 40)
							{
								go->setIsDown(true);
							}

							if (go->getIsDown())
							{
								go->vel.y -= sin(m_Gravity.y) * 2;
							}
							if (go->getPos().x < 0)
							{
								go->setActive(false);
							}

						}
						if (go->getType() == SheepObject::E_SHEEP)
						{
							go->setPos(go->vel * (float)dt, true);
							if (go->getPos().y > m_worldHeight - 40)
							{
								go->setIsDown(true);
							}

							if (go->getIsDown())
							{
								go->vel.y -= sin(m_Gravity.y) * 2;
							}
							if (go->getPos().x > m_worldWidth)
							{
								go->setActive(false);
							}
						}
						if (go->getType() == SheepObject::E_LINUX)
						{
							go->setPos(go->vel * (float)dt, true);
							Particles* particle = getParticle();
							if (particleCount < MAX_PARTICLES)
							{
								particle->type = ParticleObject_TYPE::P_ParticleTest;
								particle->active = true;
								particle->scale.Set(2, 2, 2);
								particle->vel.Set(Math::RandFloatMinMax(0, 2.f), 1.5f, 0.0f);
								particle->pos.Set(go->getPos().x + Math::RandFloatMinMax(-5.f, 5.f), go->getPos().y + 5, 0);
								particle->lifeTime = 1.f;
								if (go->getPos().y < -1)
								{
									go->setActive(false);
								}
							}
						}
						if (go->getType() == SheepObject::E_FIREBALL)
						{
							go->setPos(go->vel * (float)dt, true);
							if (go->getPos().y > m_worldHeight + go->getScale().y || go->getPos().x > m_worldWidth + go->getScale().x
								|| go->getPos().y < 0 - go->getScale().y || go->getPos().x < 0 - go->getScale().x)
							{
								go->setActive(false);
							}
						}
						if (go->getType() == SheepObject::E_LIGHTNING)
						{
							go->setPos(go->vel * (float)dt, true);
							if (go->getPos().y > m_worldHeight + go->getScale().y || go->getPos().x > m_worldWidth + go->getScale().x
								|| go->getPos().y < 0 - go->getScale().y || go->getPos().x < 0 - go->getScale().x)
							{
								go->setActive(false);
							}
						}
						for (std::vector<SheepObject *>::iterator it2 = m_goList.begin(); it2 != m_goList.end(); ++it2)
						{
							SheepObject* go2 = (SheepObject *)*it2;
							if (go2->getActive())
							{
								if (go2->getType() == SheepObject::E_WALL && go->getType() != SheepObject::E_LINUX)
								{
									if (CollisionCheck(go, go2))
									{
										go->vel.y = -go->vel.y;
									}
								}
								if (go2->getType() == SheepObject::E_FIREBALL && go->getType() == SheepObject::E_SHEEPFLIPPED
									|| go2->getType() == SheepObject::E_FIREBALL && go->getType() == SheepObject::E_SHEEP)
								{
									if (CollisionCheck(go, go2))
									{
										SoundSystem.PlayASound("Fireball_Explosion");
										go->setActive(false);
										go2->setActive(false);
										Particles* particle = getParticle();
										particle->type = ParticleObject_TYPE::P_ParticleTest;
										particle->active = true;
										particle->scale.Set(2, 2, 2);
										particle->vel.Set(0, 2.f, 0.0f);
										particle->pos = go->getPos();
										particle->lifeTime = 2.f;
										Particles* particle2 = getParticle();
										particle2->type = ParticleObject_TYPE::P_HAM;
										particle2->active = true;
										particle2->scale.Set(5, 5, 5);
										particle2->vel.Set(0, 4.5f, 0.0f);
										particle2->pos = go->getPos();
										particle2->lifeTime = 3.f;
										pointGain = true;
									}
								}
								if (go2->getType() == SheepObject::E_LIGHTNING && go->getType() == SheepObject::E_SHEEPFLIPPED)
								{
									if (CollisionCheck(go, go2))
									{
										go->setActive(false);
										go2->setActive(false);
										Particles* particle2 = getParticle();
										particle2->type = ParticleObject_TYPE::P_ParticleTest;
										particle2->active = true;
										particle2->scale.Set(2, 2, 2);
										particle2->vel.Set(0, 2.f, 0.0f);
										particle2->pos = go->getPos();
										particle2->lifeTime = 2.f;
										Particles* particle = getParticle();
										particle->type = ParticleObject_TYPE::P_ELECTROCUTE;
										particle->active = true;
										particle->scale.Set(10, 10, 10);
										particle->vel.Set(0, 4.5f, 0.0f);
										particle->pos = go->getPos();
										particle->lifeTime = 3.f;
										pointGain = true;
									}
								}
								if (go2->getType() == SheepObject::E_LIGHTNING && go->getType() == SheepObject::E_SHEEP)
								{
									if (CollisionCheck(go, go2))
									{
										go->setActive(false);
										go2->setActive(false);
										Particles* particle2 = getParticle();
										particle2->type = ParticleObject_TYPE::P_ParticleTest;
										particle2->active = true;
										particle2->scale.Set(2, 2, 2);
										particle2->vel.Set(0, 2.f, 0.0f);
										particle2->pos = go->getPos();
										particle2->lifeTime = 2.f;
										Particles* particle = getParticle();
										particle->type = ParticleObject_TYPE::P_ELECTROCUTER;
										particle->active = true;
										particle->scale.Set(10, 10, 10);
										particle->vel.Set(0, 4.5f, 0.0f);
										particle->pos = go->getPos();
										particle->lifeTime = 3.f;
										pointGain = true;
									}
								}
								if (go2->getType() == SheepObject::E_FIREBALL && go->getType() == SheepObject::E_EYES)
								{
									if (CollisionCheck(go, go2))
									{
										cout << "hit" << endl;
										go2->setActive(false);
										SheepkingHit = true;
										points += 100;
										EvilKingSheep->setHealth(-10, true);
									}
								}
								if (go2->getType() == SheepObject::E_LIGHTNING && go->getType() == SheepObject::E_EYES)
								{
									if (CollisionCheck(go, go2))
									{
										cout << "zap" << endl;
										go2->setActive(false);
										SheepkingHit = true;
										points += 50;
										EvilKingSheep->setHealth(-5, true);
									}
								}
								if (go2->getType() == SheepObject::E_SHEEPFLIPPED && go->getType() == SheepObject::E_PLAYER
									|| go2->getType() == SheepObject::E_SHEEP && go->getType() == SheepObject::E_PLAYER
									|| go2->getType() == SheepObject::E_LINUX && go->getType() == SheepObject::E_PLAYER)
								{
									if (CollisionCheck(go2, go))
									{
										go2->setActive(false);
										player->setHealth(-1, true);
										cout << player->getHealth() << endl;
									}
								}

							}
						}

					}
				}
				if (EvilKingSheep->getHealth() <= 0 || player->getHealth() == 0)
				{
					gameOver = true;
				}
				if (points > 150)
				{
					Transition = true;
				}
				if (player->getOnCooldown())
				{
					player->setCooldown((float)-dt, true);
				}
				if (player->getCooldown() < 0)
				{
					player->setCooldown(1.f);
					player->setOnCoolDown(false);
				}
				if (pointGain)
				{
					points += 20;
					pointGain = false;
				}
				UpdateRayTracing(dt);
				player->UpdateMovement(dt);
				m_Timer -= (float)dt;
				if (Transition == true)
				{
					BossTimer -= (float)dt;
				}
			}
			if (ManaRegen < 0)
			{
				player->setMana(10, true);
				ManaRegen = 3.f;
			}
			if (fireRate < 0)
			{
				fireRate = 0.222f;
			}
			if (SheepkingHit && timer > 0)
			{
				if (Modifier > 5)
				{
					isLeft = true;
				}
				if (Modifier < -5)
				{
					isLeft = false;
				}
				if (isLeft)
				{
					Modifier--;
				}
				if (!isLeft)
				{
					Modifier++;
				}
				timer -= (float)dt;
			}
			if (timer < 0)
			{
				SheepkingHit = false;
				timer = 0.3f;
			}

			UpdateParticles(dt);
			fireRate -= (float)dt;

			ManaRegen -= (float)dt;
		}
	else
	{

		if (!blKeyboardState && Application::IsKeyPressed(VK_SPACE))
		{
			isInstructions = false;
			playMusic = true;
			blKeyboardState = true;
			StatManager::GetInstance()->SetPrevGame(5);
		}
	}
	if (playMusic)
	{
		SoundSystem.playSheepMusic();
		playMusic = false;
	}

}
Particles* SheepGame::getParticle()
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
void SheepGame::UpdateParticles(double dt)
{
	for (std::vector<Particles *>::iterator it = m_particleList.begin(); it != m_particleList.end();++it)
	{
		Particles *particle = (Particles *)*it;
		if (particle->active)
		{
			if (particle->type == ParticleObject_TYPE::P_ParticleTest)
			{
				particle->pos.y += particle->vel.y  * (float)dt * 10;
				particle->pos.x += particle->vel.x * (float)dt * 10;
				particle->scale.x += particle->vel.y * (float)dt * 3;
				particle->scale.y += particle->vel.y * (float)dt * 3;
				particle->lifeTime -= (float)dt;
			}
			if (particle->type == ParticleObject_TYPE::P_HAM)
			{
				if (particle->pos.y > 8)
				{
					particle->pos.y -= particle->vel.y  * (float)dt * 10;
				}
				particle->lifeTime -= (float)dt;
			}
			if (particle->type == ParticleObject_TYPE::P_ELECTROCUTE || particle->type == ParticleObject_TYPE::P_ELECTROCUTER)
			{
				if (particle->pos.y > 8)
				{
					particle->pos.y -= particle->vel.y  * (float)dt * 10;
				}
				particle->lifeTime -= (float)dt;
			}
			if (particle->lifeTime < 0)
			{
				particle->active = false;
				m_particleCount--;
			}
			if (particle->cooldown < 0)
			{
				particle->cooldown = 0.05f;
			}
			if (particle->pos.y > m_worldHeight)
			{
				particle->active = false;
				m_particleCount--;
			}
		}
	}
}
void SheepGame::RenderParticles(Particles *particle)
{
	switch (particle->type)
	{
	case ParticleObject_TYPE::P_ParticleTest:
		modelStack.PushMatrix();
		modelStack.Translate(particle->pos.x, particle->pos.y, particle->pos.z);
		modelStack.Rotate(particle->rotation, 0, 0, 1);
		modelStack.Scale(particle->scale.x, particle->scale.y, particle->scale.z);
		RenderMesh(meshList[GEO_PARTICLE_TEST], false);
		modelStack.PopMatrix();
		break;
	case ParticleObject_TYPE::P_HAM:
		modelStack.PushMatrix();
		modelStack.Translate(particle->pos.x, particle->pos.y, particle->pos.z);
		modelStack.Rotate(particle->rotation, 0, 0, 1);
		modelStack.Scale(particle->scale.x, particle->scale.y, particle->scale.z);
		RenderMesh(meshList[GEO_HAM], false);
		modelStack.PopMatrix();
		break;
	case ParticleObject_TYPE::P_ELECTROCUTE:
		modelStack.PushMatrix();
		modelStack.Translate(particle->pos.x, particle->pos.y, particle->pos.z);
		modelStack.Rotate(particle->rotation, 0, 0, 1);
		modelStack.Scale(particle->scale.x, particle->scale.y, particle->scale.z);
		RenderMesh(meshList[GEO_ELECTROCUTED], false);
		modelStack.PopMatrix();
		break;
	case ParticleObject_TYPE::P_ELECTROCUTER:
		modelStack.PushMatrix();
		modelStack.Translate(particle->pos.x, particle->pos.y, particle->pos.z);
		modelStack.Rotate(particle->rotation, 0, 0, 1);
		modelStack.Scale(particle->scale.x, particle->scale.y, particle->scale.z);
		RenderMesh(meshList[GEO_ELECTROCUTEDR], false);
		modelStack.PopMatrix();
		break;
	default:
		cout << "Found NULL Particle" << endl;
		break;
	}

}
void SheepGame::Pattern1(double dt)
{
	cout << "Pattern 1" << endl;

	Timer1 -= (float)dt;
	if (Timer1 < 10)
	{
		if (!stop1)
		{
			Warning->setActive(true);
		}
		if (Timer1 < 8)
		{
			Timer2 -= (float)dt;
			if (Timer2 < 10)
			{
				if (!stop2)
				{
					Warning2->setActive(true);
				}
			}
			if (Timer2 < 8)
			{
				Timer3 -= (float)dt;
				if (Timer3 < 10)
				{
					if (!stop3)
					{
						Warning3->setActive(true);
					}
					if (Timer3 < 0 && Warning3->getActive() == true)
					{
						SheepObject* Linux = FetchGO();
						Linux->setType(SheepObject::E_LINUX);
						Linux->setScale(Vector3(40, 40, 40));
						Linux->vel.Set(0, -15.f, 0);
						Linux->setPos(Vector3(m_worldWidth / 2 + 45, m_worldHeight, 0));
						Linux->setActive(true);
						Linux->setIsDown(false);
						Warning3->setActive(false);
						Timer3Check = false;
						patternDone = true;
						stop3 = true;
					}
				}
				if (Timer2 < 0 && Warning2->getActive() == true)
				{
					SheepObject* Linux = FetchGO();
					Linux->setType(SheepObject::E_LINUX);
					Linux->setScale(Vector3(40, 40, 40));
					Linux->vel.Set(0, -15.f, 0);
					Linux->setPos(Vector3(m_worldWidth / 2 - 65, m_worldHeight, 0));
					Linux->setActive(true);
					Linux->setIsDown(false);
					Warning2->setActive(false);
					Timer2Check = false;
					stop2 = true;
				}
			}
			if (Timer1 < 0 && Warning->getActive() == true)
			{
				SheepObject* Linux = FetchGO();
				Linux->setType(SheepObject::E_LINUX);
				Linux->setScale(Vector3(40, 40, 40));
				Linux->vel.Set(0, -15.f, 0);
				Linux->setPos(Vector3(m_worldWidth / 2 - 10, m_worldHeight, 0));
				Linux->setActive(true);
				Linux->setIsDown(false);
				Warning->setActive(false);
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

	Timer2 -= (float)dt;
	if (Timer2 < 10)
	{
		if (!stop2)
		{
			Warning2->setActive(true);
		}
		if (Timer2 < 8)
		{
			Timer1 -= (float)dt;
			if (Timer1 < 10)
			{
				if (!stop1)
				{
					Warning->setActive(true);
				}
			}
			if (Timer1 < 8)
			{
				Timer3 -= (float)dt;
				if (Timer3 < 10)
				{
					if (!stop3)
					{
						Warning3->setActive(true);
					}
					if (Timer3 < 0 && Warning3->getActive() == true)
					{

						SheepObject* Linux = FetchGO();
						Linux->setType(SheepObject::E_LINUX);
						Linux->setScale(Vector3(40, 40, 40));
						Linux->vel.Set(0, -15.f, 0);
						Linux->setPos(Vector3(m_worldWidth / 2 + 45, m_worldHeight, 0));
						Linux->setActive(true);
						Linux->setIsDown(false);
						Warning3->setActive(false);
						Timer3Check = false;
						stop3 = true;
					}
				}
				if (Timer1 < 0 && Warning->getActive() == true)
				{
					SheepObject* Linux = FetchGO();
					Linux->setType(SheepObject::E_LINUX);
					Linux->setScale(Vector3(40, 40, 40));
					Linux->vel.Set(0, -15.f, 0);
					Linux->setPos(Vector3(m_worldWidth / 2 - 10, m_worldHeight, 0));
					Linux->setActive(true);
					Linux->setIsDown(false);
					Warning->setActive(false);
					Timer1Check = false;

					stop1 = true;
				}
			}
			if (Timer2 < 0 && Warning2->getActive() == true)
			{
				SheepObject* Linux = FetchGO();
				Linux->setType(SheepObject::E_LINUX);
				Linux->setScale(Vector3(40, 40, 40));
				Linux->vel.Set(0, -15.f, 0);
				Linux->setPos(Vector3(m_worldWidth / 2 - 65, m_worldHeight, 0));
				Linux->setActive(true);
				Linux->setIsDown(false);
				Warning2->setActive(false);
				Timer2Check = false;
				stop2 = true;
			}
		}
	}
}
void SheepGame::Pattern3(double dt)
{
	cout << "Pattern 3" << endl;

	Timer3 -= (float)dt;
	if (Timer3 < 10)
	{
		if (!stop3)
		{
			Warning3->setActive(true);
		}
		if (Timer3 < 8)
		{
			Timer2 -= (float)dt;
			if (Timer2 < 10)
			{
				if (!stop2)
				{
					Warning2->setActive(true);
				}
			}
			if (Timer2 < 8)
			{
				Timer1 -= (float)dt;
				if (Timer1 < 10)
				{
					if (!stop1)
					{
						Warning->setActive(true);
					}
					if (Timer1 < 0 && Warning->getActive() == true)
					{
						SheepObject* Linux = FetchGO();
						Linux->setType(SheepObject::E_LINUX);
						Linux->setScale(Vector3(40, 40, 40));
						Linux->vel.Set(0, -15.f, 0);
						Linux->setPos(Vector3(m_worldWidth / 2 - 10, m_worldHeight, 0));
						Linux->setActive(true);
						Linux->setIsDown(false);
						Warning->setActive(false);
						Timer1Check = false;
						patternDone = true;
						stop1 = true;
					}
				}
				if (Timer2 < 0 && Warning2->getActive() == true)
				{
					SheepObject* Linux = FetchGO();
					Linux->setType(SheepObject::E_LINUX);
					Linux->setScale(Vector3(40, 40, 40));
					Linux->vel.Set(0, -15.f, 0);
					Linux->setPos(Vector3(m_worldWidth / 2 - 65, m_worldHeight, 0));
					Linux->setActive(true);
					Linux->setIsDown(false);
					Warning2->setActive(false);
					Timer2Check = false;
					stop2 = true;
				}
			}
			if (Timer3 < 0 && Warning3->getActive() == true)
			{


				SheepObject* Linux = FetchGO();
				Linux->setType(SheepObject::E_LINUX);
				Linux->setScale(Vector3(40, 40, 40));
				Linux->vel.Set(0, -15.f, 0);
				Linux->setPos(Vector3(m_worldWidth / 2 + 45, m_worldHeight, 0));
				Linux->setActive(true);
				Linux->setIsDown(false);
				Warning3->setActive(false);
				Timer3Check = false;
				stop3 = true;
			}
		}
	}
}
void SheepGame::UpdateRayTracing(double dt)
{
	// James 13/8/2019
	for (int i = 0; i < TraceSize; ++i)
	{
		Trace[i]->setActive(false);
	}
	SheepObject temp;
	temp.vel = mousePos - player->getPos();
	temp.vel = 85.f * temp.vel.Normalized();
	temp.setType(SheepObject::E_TRACE);
	temp.setScale(Vector3(3, 3, 3));
	temp.setPos(player->getPos());
	temp.setActive(true);
	float time = 0.f;
	int index = 0;
	float accumulatedtime = 0.f;
	float totaldist = 0.f;
	//Vector3 prevpos = Ghost->pos + m_gravity * dt;
	for (float time = 0; time < 5.f; time += (float)dt)
	{
		if (totaldist > (mousePos - player->getPos()).Length())
		{
			break;
		}
		if (!temp.getActive())
		{
			break;
		}
		temp.setPos(temp.vel * (float)dt, true);
		accumulatedtime += temp.vel.Length() *(float)dt;
		totaldist += temp.vel.Length() *(float)dt;
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
			Trace[index]->setActive(true);
			Trace[index]->setPos(temp.getPos());
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
	switch (go2->getType())
	{
	case SheepObject::E_WALL:
	{
		Vector3 N = go2->normal;

		Vector3 w0minusb1 = go2->getPos() - go->getPos();

		Vector3 NP(N.y, -N.x);
		if (w0minusb1.Dot(N) < 0)
		{
			N = -N;
		}
		if (go->vel.Dot(N) < 0)
		{
			return false;
		}
		if (w0minusb1.Dot(N) < go->getScale().x + go2->getScale().x * 0.5f &&
			Math::FAbs(w0minusb1.Dot(NP)) < go->getScale().x + go2->getScale().y * 0.5f)
		{
			return true;
		}
		break;
	}
	case SheepObject::E_PLAYER:
	{
		Vector3 dist = go2->getPos() - go->getPos();
		//Vector3 u = go->vel - go2->vel;
		if (dist.Length() < (go->getScale().x/2) + (go2->getScale().x/2))
		{
			return true;
		}
		break;
	}
	case SheepObject::E_FIREBALL:
	{
		Vector3 dist = go2->getPos() - go->getPos();
		Vector3 u = go->vel - go2->vel;
		if (dist.Length() < (go->getScale().x/2) + (go2->getScale().x/2) && u.Dot(dist) > 0.0f)
		{
			return true;
		}
		break;
	}
	case SheepObject::E_LIGHTNING:
	{
		Vector3 dist = go2->getPos() - go->getPos();
		Vector3 u = go->vel - go2->vel;
		if (dist.Length() < (go->getScale().x / 2) + (go2->getScale().x / 2) && u.Dot(dist) > 0.0f)
		{
			return true;
		}
		break;
	}
	case SheepObject::E_EYES:
	{
		Vector3 N = go2->normal;

		Vector3 w0minusb1 = go2->getPos() - go->getPos();

		Vector3 NP(N.y, -N.x);
		if (w0minusb1.Dot(N) < 0)
		{
			N = -N;
		}
		if (go->vel.Dot(N) < 0)
		{
			return false;
		}
		if (w0minusb1.Dot(N) < go->getScale().x + go2->getScale().x * 0.5f &&
			Math::FAbs(w0minusb1.Dot(NP)) < go->getScale().x + go2->getScale().y * 0.5f)
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
		if (!isInstructions)
		{
			if (!gameOver)
			{
				renderBG();
				modelStack.PushMatrix();
				modelStack.Translate(m_worldWidth / 2 + player->getMana() / 2, 2.f, 0);
				modelStack.Scale(player->getMana(), 3, 1);
				RenderMesh(meshList[GEO_MANABAR], false);
				modelStack.PopMatrix();

				RenderTextOnScreen(meshList[GEO_GAMEFONT], "Mana", Color(1, 1, 1), 2, m_worldWidth / 2 - 63, 0.3f);
				if (Transition == true)
				{
					if (EvilKingSheep->getHealth() > 0)
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
							modelStack.Translate(m_worldWidth / 2 - 50 + EvilKingSheep->getHealth() / 4, m_worldHeight - 10, 0);
							modelStack.Scale(EvilKingSheep->getHealth() / 2, 3, 1);
							RenderMesh(meshList[GEO_LIFEBAR], false);
							modelStack.PopMatrix();
						}
					}
					else
					{
						EvilKingSheep->setActive(false);
					}
				}
				if (player->getActive())
				{
					RenderGO(player);
				}

				for (std::vector<SheepObject *>::iterator it = m_goList.begin(); it != m_goList.end(); ++it)
				{
					SheepObject *go = (SheepObject *)*it;
					if (go->getActive())
					{
						RenderGO(go);
					}
				}
				for (int i = 0; i < TraceSize; ++i)
				{
					if (Trace[i]->getActive())
					{
						RenderGO(Trace[i]);
					}
				}
				renderLives();
				renderCrossHair();
				for (std::vector<Particles *>::iterator it = m_particleList.begin(); it != m_particleList.end();++it)
				{
					Particles *particle = (Particles *)*it;
					if (particle->active)
					{
						RenderParticles(particle);
					}
				}
			}
			else
			{
				Results::getInstance()->RenderResults(points, m_Grade);
			}
		}
		else
		{
			RenderInstructions();
		}

}
void SheepGame::renderCrossHair()
{
	modelStack.PushMatrix();
	modelStack.Translate(mousePos);
	modelStack.Scale(5, 5, 1);
	RenderMesh(meshList[GEO_CROSSHAIR], false);
	modelStack.PopMatrix();
}
void SheepGame::GameEndCalculations() // Setting the stats and other stuff
{
	if (points >= 2800)
	{
		m_Grade = 'S';
		StatManager::GetInstance()->UpdateChar01F(StatManager::GetInstance()->GetChar01().m_frustration -20);
		StatManager::GetInstance()->UpdateChar01M(StatManager::GetInstance()->GetChar01().m_motivation + 20);
		StatManager::GetInstance()->UpdateChar01R(StatManager::GetInstance()->GetChar01().m_rest + 10);
		StatManager::GetInstance()->UpdateChar02F(StatManager::GetInstance()->GetChar02().m_frustration -20);
		StatManager::GetInstance()->UpdateChar02M(StatManager::GetInstance()->GetChar02().m_motivation + 20);
		StatManager::GetInstance()->UpdateChar02R(StatManager::GetInstance()->GetChar02().m_rest + 10);
		StatManager::GetInstance()->UpdateChar03F(StatManager::GetInstance()->GetChar03().m_frustration -20);
		StatManager::GetInstance()->UpdateChar03M(StatManager::GetInstance()->GetChar03().m_motivation + 20);
		StatManager::GetInstance()->UpdateChar03R(StatManager::GetInstance()->GetChar03().m_rest + 10);
		StatManager::GetInstance()->UpdateChar04F(StatManager::GetInstance()->GetChar04().m_frustration -20);
		StatManager::GetInstance()->UpdateChar04M(StatManager::GetInstance()->GetChar04().m_motivation + 20);
		StatManager::GetInstance()->UpdateChar04R(StatManager::GetInstance()->GetChar04().m_rest + 10);
		Results::getInstance()->InitStatsToDist(35);
	}
	else if (points >= 2500 && points < 2800)
	{
		m_Grade = 'A';
		Results::getInstance()->InitStatsToDist(25);

	}
	else if (points >= 2200 && points < 2500)
	{
		m_Grade = 'B';
		Results::getInstance()->InitStatsToDist(20);
	}
	else if (points >= 1900 && points < 2200)
	{
		m_Grade = 'C';
		Results::getInstance()->InitStatsToDist(15);
	}
	else if (points >=  1750 && points < 1900)
	{
		m_Grade = 'D';
		Results::getInstance()->InitStatsToDist(10);
	}
	else
	{
		m_Grade = 'F';
		StatManager::GetInstance()->UpdateChar01F(StatManager::GetInstance()->GetChar01().m_frustration + 10);
		StatManager::GetInstance()->UpdateChar01M(StatManager::GetInstance()->GetChar01().m_frustration -10);
		StatManager::GetInstance()->UpdateChar01R(StatManager::GetInstance()->GetChar01().m_rest - 10);
		StatManager::GetInstance()->UpdateChar02F(StatManager::GetInstance()->GetChar02().m_frustration + 10);
		StatManager::GetInstance()->UpdateChar02M(StatManager::GetInstance()->GetChar02().m_motivation -10);
		StatManager::GetInstance()->UpdateChar02R(StatManager::GetInstance()->GetChar02().m_rest - 10);
		StatManager::GetInstance()->UpdateChar03F(StatManager::GetInstance()->GetChar03().m_frustration + 10);
		StatManager::GetInstance()->UpdateChar03M(StatManager::GetInstance()->GetChar03().m_motivation -10);
		StatManager::GetInstance()->UpdateChar03R(StatManager::GetInstance()->GetChar03().m_rest - 10);
		StatManager::GetInstance()->UpdateChar04F(StatManager::GetInstance()->GetChar04().m_frustration + 10);
		StatManager::GetInstance()->UpdateChar04M(StatManager::GetInstance()->GetChar04().m_motivation -10);
		StatManager::GetInstance()->UpdateChar04R(StatManager::GetInstance()->GetChar04().m_rest - 10);
	}

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
		if (!SheepkingHit)
		{
			modelStack.PushMatrix();
			modelStack.Translate(m_worldWidth / 2, transitionY, 0);
			modelStack.Scale(80, 80, 1);
			RenderMesh(meshList[GEO_EVILSHEEPKING], false);
			modelStack.PopMatrix();
		}
		else
		{
			modelStack.PushMatrix();
			modelStack.Translate(m_worldWidth / 2 + Modifier, transitionY, 0);
			modelStack.Scale(80, 80, 1);
			RenderMesh(meshList[GEO_SHEEPKINGHIT], false);
			modelStack.PopMatrix();
		}
		EvilKingSheep->setPos(Vector3(m_worldWidth / 2, transitionY, 0)) ;
	}
}
void SheepGame::renderBG()
{
	modelStack.PushMatrix();
	modelStack.Translate(m_worldWidth / 2, m_worldHeight / 2, 0);
	modelStack.Scale(m_worldWidth, m_worldHeight, 1);
	RenderMesh(meshList[GEO_SHEEPBG], false);
	modelStack.PopMatrix();
}
void SheepGame::renderLives()
{
	if (player->getHealth() >= 3)
	{
		modelStack.PushMatrix();
		modelStack.Translate(20, m_worldHeight - 10, 0);
		modelStack.Scale(3, 3, 3);
		RenderMesh(meshList[GEO_LIVES], false);
		modelStack.PopMatrix();
	}
	if (player->getHealth() >= 2)
	{
		modelStack.PushMatrix();
		modelStack.Translate(15, m_worldHeight - 10, 0);
		modelStack.Scale(3, 3, 3);
		RenderMesh(meshList[GEO_LIVES], false);
		modelStack.PopMatrix();
	}
	if (player->getHealth() >= 1)
	{
		modelStack.PushMatrix();
		modelStack.Translate(10, m_worldHeight - 10, 0);
		modelStack.Scale(3, 3, 3);
		RenderMesh(meshList[GEO_LIVES], false);
		modelStack.PopMatrix();
	}
	std::ostringstream ss;
	ss.precision(4);
	ss << "Score : " << points;
	RenderTextOnScreen(meshList[GEO_GAMEFONT], ss.str(), Color(0, 1, 1), 2, 0, 0);
}
void SheepGame::RenderInstructions()
{
	modelStack.PushMatrix();
	modelStack.Translate(m_worldWidth / 2, m_worldHeight / 2, 0);
	modelStack.Scale(m_worldWidth, m_worldHeight, 1);
	RenderMesh(meshList[GEO_INSTRUCT], false);
	modelStack.PopMatrix();
}
void SheepGame::RenderGO(SheepObject * go)
{
	switch (go->getType())
	{
	case SheepObject::E_SHEEP:
	{
		modelStack.PushMatrix();
		modelStack.Translate(go->getPos());
		modelStack.Scale(go->getScale());
		RenderMesh(meshList[GEO_SHEEP], false);
		modelStack.PopMatrix();
		break;
	}
	case SheepObject::E_SHEEPFLIPPED:
	{
		modelStack.PushMatrix();
		modelStack.Translate(go->getPos());
		modelStack.Scale(go->getScale());
		RenderMesh(meshList[GEO_SHEEPFLIPPED], false);
		modelStack.PopMatrix();
		break;
	}
	case SheepObject::E_PLAYER:
	{
		if (go->getState() == true)
		{
			modelStack.PushMatrix();
			modelStack.Translate(go->getPos());
			if (go->getDirection() == true)
			{
				modelStack.Scale(go->getScale());
				RenderMesh(meshList[GEO_CHARACTER04_MOVE_LEFT], false);
				modelStack.PopMatrix();
			}
			else
			{
				modelStack.Scale(go->getScale());
				RenderMesh(meshList[GEO_CHARACTER04_MOVE_RIGHT], false);
				modelStack.PopMatrix();
			}
			break;
		}
		else if (!go->getState())
		{
			modelStack.PushMatrix();
			modelStack.Translate(go->getPos());
			if (go->getDirection() == true)
			{
				modelStack.Scale(go->getScale());
				RenderMesh(meshList[GEO_CHARACTER04_IDLE_LEFT], false);
				modelStack.PopMatrix();
			}
			else
			{
				modelStack.Scale(go->getScale());
				RenderMesh(meshList[GEO_CHARACTER04_IDLE_RIGHT], false);
				modelStack.PopMatrix();
			}
			break;
		}
	case SheepObject::E_LINUX:
	{
		modelStack.PushMatrix();
		modelStack.Translate(go->getPos());
		modelStack.Scale(go->getScale());
		RenderMesh(meshList[GEO_METEORWOOL], false);
		modelStack.PopMatrix();
		break;
	}
	case  SheepObject::E_FIREBALL:
	{
		modelStack.PushMatrix();
		modelStack.Translate(go->getPos());
		modelStack.Rotate(Math::RadianToDegree(atan2(go->vel.y, go->vel.x)), 0, 0, 1);
		modelStack.Scale(go->getScale());
		RenderMesh(meshList[GEO_FIREBALL], false);
		modelStack.PopMatrix();
		break;
	}
	case SheepObject::E_LIGHTNING:
	{
		modelStack.PushMatrix();
		modelStack.Translate(go->getPos());
		modelStack.Rotate(Math::RadianToDegree(atan2(go->vel.y, go->vel.x)), 0, 0, 1);
		modelStack.Scale(go->getScale());
		RenderMesh(meshList[GEO_LIGHTNING], false);
		modelStack.PopMatrix();
		break;
	}
	case SheepObject::E_WARNING:
	{
		modelStack.PushMatrix();
		modelStack.Translate(go->getPos());
		modelStack.Scale(go->getScale());
		RenderMesh(meshList[GEO_WARNING], false);
		modelStack.PopMatrix();
		break;
	}
	case SheepObject::E_TRACE:
	{
		modelStack.PushMatrix();
		modelStack.Translate(go->getPos());
		modelStack.Scale(go->getScale());
		RenderMesh(meshList[GEO_MAGICCIRCLE], false);
		modelStack.PopMatrix();
		break;
	}
	default:
		break;
	}
	}
}

SheepObject* SheepGame::FetchGO()
{
	for (unsigned int i = 0; i < m_goList.size(); i++)
	{
		if (m_goList[i] == Warning || m_goList[i] == Warning2 || m_goList[i] == Warning3)
		{
			continue;
		}
		if (!m_goList[i]->getActive())
		{
			m_goList[i]->setActive(true);
			return m_goList[i];
		}
	}

	for (int i = 0; i < 30; ++i)
	{
		m_goList.push_back(new SheepObject(SheepObject::E_NONE));
	}
	m_goList[m_goList.size() - 1]->setActive(true);
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
