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
	gaveup = false;
	Math::InitRNG();
	m_eventTimer = Math::RandFloatMinMax(20.0f, 40.f);
	b_transitioning = false;
	playMusic = false;
	bounceTime = 0.5f;
	meshList[GEO_QUAD] = MeshBuilder::GenerateQuad("test", Color(1, 1, 1), 1.f);
	meshList[GEO_BACKGROUND] = MeshBuilder::GenerateQuad("Background", Color(1, 1, 1), 1);
	meshList[GEO_BACKGROUND]->textureID = LoadTGA("Image//BackGround.tga");
	meshList[GEO_PARTICLE_TEST] = MeshBuilder::GenerateQuad("testParticle", Color(1, 1, 1), 1.f);
	meshList[GEO_PARTICLE_TEST]->textureID = LoadTGA("Image//balloon.tga");
	meshList[GEO_ARROW] = MeshBuilder::GenerateQuad("arrow", Color(1, 1, 1), 1.f);
	meshList[GEO_ARROW]->textureID = LoadTGA("Image//Arrow.tga");
	meshList[GEO_TELEVISION] = MeshBuilder::GenerateQuad("Television", Color(1, 1, 1), 1.f);
	meshList[GEO_TELEVISION]->textureID = LoadTGA("Image//Item_TV.tga");
	meshList[GEO_COMPUTER] = MeshBuilder::GenerateQuad("Computer", Color(1, 1, 1), 1.f);
	meshList[GEO_COMPUTER]->textureID = LoadTGA("Image//Item_Comp.tga");
	meshList[GEO_SLEEPBOX] = MeshBuilder::GenerateQuad("SleepingBox", Color(1, 1, 1), 1.f);
	meshList[GEO_SLEEPBOX]->textureID = LoadTGA("Image//Item_Box.tga");
	meshList[GEO_BORDER] = MeshBuilder::GenerateQuad("Border", Color(1, 1, 1), 1.f);
	meshList[GEO_BORDER]->textureID = LoadTGA("Image//Border.tga");
	meshList[GEO_TANK_CURSOR] = MeshBuilder::GenerateQuad("Cursor", Color(1, 1, 1), 1.f);
	meshList[GEO_TANK_CURSOR]->textureID = LoadTGA("Image//gameCursor.tga");
	meshList[GEO_TANK_CURSOR_ALTERNATE] = MeshBuilder::GenerateQuad("Cursor	Alternate", Color(1, 1, 1), 1.f);
	meshList[GEO_TANK_CURSOR_ALTERNATE]->textureID = LoadTGA("Image//gameCursor.tga");
	meshList[GEO_MAIN_USE] = MeshBuilder::GenerateQuad("Use", Color(1, 1, 1), 1.f);
	meshList[GEO_MAIN_USE]->textureID = LoadTGA("Image//Main_Use.tga");
	meshList[GEO_MAIN_STOP] = MeshBuilder::GenerateQuad("Stop", Color(1, 1, 1), 1.f);
	meshList[GEO_MAIN_STOP]->textureID = LoadTGA("Image//Main_Stop.tga");
	meshList[GEO_MAIN_CONTINUE] = MeshBuilder::GenerateQuad("Continue", Color(1, 1, 1), 1.f);
	meshList[GEO_MAIN_CONTINUE]->textureID = LoadTGA("Image//Main_Continue.tga");
	meshList[GEO_LOSESCREEN] = MeshBuilder::GenerateQuad("LoseScreen", Color(1, 1, 1), 1.f);
	meshList[GEO_LOSESCREEN]->textureID = LoadTGA("Image//Lose_Screen.tga");
	meshList[GEO_WINSCREEN] = MeshBuilder::GenerateQuad("WinScreen", Color(1, 1, 1), 1.f);
	meshList[GEO_WINSCREEN]->textureID = LoadTGA("Image//WinScreen.tga");
	meshList[GEO_WINSCREENB] = MeshBuilder::GenerateQuad("WinScreenB", Color(1, 1, 1), 1.f);
	meshList[GEO_WINSCREENB]->textureID = LoadTGA("Image//WinscreenB.tga");
	meshList[GEO_WINSCREENC] = MeshBuilder::GenerateQuad("WinScreenC", Color(1, 1, 1), 1.f);
	meshList[GEO_WINSCREENC]->textureID = LoadTGA("Image//WinscreenC.tga");
	meshList[GEO_WINSCREEND] = MeshBuilder::GenerateQuad("WinScreenD", Color(1, 1, 1), 1.f);
	meshList[GEO_WINSCREEND]->textureID = LoadTGA("Image//WinScreenD.tga");
	meshList[GEO_GIVEUP] = MeshBuilder::GenerateQuad("Giveup", Color(1, 1, 1), 1.f);
	meshList[GEO_GIVEUP]->textureID = LoadTGA("Image//Gave_Up.tga");

	// CHARACTER SPRITE ANIMATIONS
	meshList[GEO_CHARACTER01_IDLE_LEFT] = MeshBuilder::GenerateSpriteAnimation("c01_idle_left", 1, 4);
	meshList[GEO_CHARACTER01_IDLE_LEFT]->textureID = LoadTGA("Image//CharacterSprites//Idle//knight_idle_anim_left.tga");
	meshList[GEO_CHARACTER02_IDLE_LEFT] = MeshBuilder::GenerateSpriteAnimation("c02_idle_left", 1, 4);
	meshList[GEO_CHARACTER02_IDLE_LEFT]->textureID = LoadTGA("Image//CharacterSprites//Idle//elf_idle_anim_left.tga");
	meshList[GEO_CHARACTER03_IDLE_LEFT] = MeshBuilder::GenerateSpriteAnimation("c03_idle_left", 1, 4);
	meshList[GEO_CHARACTER03_IDLE_LEFT]->textureID = LoadTGA("Image//CharacterSprites//Idle//necromancer_idle_anim_left.tga");
	meshList[GEO_CHARACTER04_IDLE_LEFT] = MeshBuilder::GenerateSpriteAnimation("c04_idle_left", 1, 4);
	meshList[GEO_CHARACTER04_IDLE_LEFT]->textureID = LoadTGA("Image//CharacterSprites//Idle//wizzard_idle_anim_left.tga");

	meshList[GEO_CHARACTER01_MOVE_LEFT] = MeshBuilder::GenerateSpriteAnimation("c01_move_left", 1, 4);
	meshList[GEO_CHARACTER01_MOVE_LEFT]->textureID = LoadTGA("Image//CharacterSprites//Move//knight_run_anim_left.tga");
	meshList[GEO_CHARACTER02_MOVE_LEFT] = MeshBuilder::GenerateSpriteAnimation("c02_move_left", 1, 4);
	meshList[GEO_CHARACTER02_MOVE_LEFT]->textureID = LoadTGA("Image//CharacterSprites//Move//elf_run_anim_left.tga");
	meshList[GEO_CHARACTER03_MOVE_LEFT] = MeshBuilder::GenerateSpriteAnimation("c03_move_left", 1, 4);
	meshList[GEO_CHARACTER03_MOVE_LEFT]->textureID = LoadTGA("Image//CharacterSprites//Move//necromancer_run_anim_left.tga");
	meshList[GEO_CHARACTER04_MOVE_LEFT] = MeshBuilder::GenerateSpriteAnimation("c04_move_left", 1, 4);
	meshList[GEO_CHARACTER04_MOVE_LEFT]->textureID = LoadTGA("Image//CharacterSprites//Move//wizzard_run_anim_left.tga");

	meshList[GEO_CHARACTER01_IDLE_RIGHT] = MeshBuilder::GenerateSpriteAnimation("c01_idle_right", 1, 4);
	meshList[GEO_CHARACTER01_IDLE_RIGHT]->textureID = LoadTGA("Image//CharacterSprites//Idle//knight_idle_anim_right.tga");
	meshList[GEO_CHARACTER02_IDLE_RIGHT] = MeshBuilder::GenerateSpriteAnimation("c02_idle_right", 1, 4);
	meshList[GEO_CHARACTER02_IDLE_RIGHT]->textureID = LoadTGA("Image//CharacterSprites//Idle//elf_idle_anim_right.tga");
	meshList[GEO_CHARACTER03_IDLE_RIGHT] = MeshBuilder::GenerateSpriteAnimation("c03_idle_right", 1, 4);
	meshList[GEO_CHARACTER03_IDLE_RIGHT]->textureID = LoadTGA("Image//CharacterSprites//Idle//necromancer_idle_anim_right.tga");
	meshList[GEO_CHARACTER04_IDLE_RIGHT] = MeshBuilder::GenerateSpriteAnimation("c04_idle_right", 1, 4);
	meshList[GEO_CHARACTER04_IDLE_RIGHT]->textureID = LoadTGA("Image//CharacterSprites//Idle//wizzard_idle_anim_right.tga");

	meshList[GEO_CHARACTER01_MOVE_RIGHT] = MeshBuilder::GenerateSpriteAnimation("c01_move_right", 1, 4);
	meshList[GEO_CHARACTER01_MOVE_RIGHT]->textureID = LoadTGA("Image//CharacterSprites//Move//knight_run_anim_right.tga");
	meshList[GEO_CHARACTER02_MOVE_RIGHT] = MeshBuilder::GenerateSpriteAnimation("c02_move_right", 1, 4);
	meshList[GEO_CHARACTER02_MOVE_RIGHT]->textureID = LoadTGA("Image//CharacterSprites//Move//elf_run_anim_right.tga");
	meshList[GEO_CHARACTER03_MOVE_RIGHT] = MeshBuilder::GenerateSpriteAnimation("c03_move_right", 1, 4);
	meshList[GEO_CHARACTER03_MOVE_RIGHT]->textureID = LoadTGA("Image//CharacterSprites//Move//necromancer_run_anim_right.tga");
	meshList[GEO_CHARACTER04_MOVE_RIGHT] = MeshBuilder::GenerateSpriteAnimation("c04_move_right", 1, 4);
	meshList[GEO_CHARACTER04_MOVE_RIGHT]->textureID = LoadTGA("Image//CharacterSprites//Move//wizzard_run_anim_right.tga");

	Mtx44 projection;
	projection.SetToOrtho(0, m_worldWidth, 0, m_worldHeight, -10, 10);
	projectionStack.LoadMatrix(projection);
	//Particles
	m_particleCount = 0;
	MAX_PARTICLE = 2000;
	soundSystem.Init();
	m_Gravity.Set(0, -9.8, 0);
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

	ScreenSplit[0]->UseItem->setPos(Vector3(m_worldWidth * 0.45f, m_worldHeight * 0.55f, 0));
	ScreenSplit[1]->UseItem->setPos(Vector3(m_worldWidth * 0.95f, m_worldHeight * 0.55f, 0));
	ScreenSplit[2]->UseItem->setPos(Vector3(m_worldWidth * 0.45f, m_worldHeight * 0.05f, 0));
	ScreenSplit[3]->UseItem->setPos(Vector3(m_worldWidth * 0.95f, m_worldHeight * 0.05f, 0));

	ScreenSplit[0]->Character->setType(CharacterObject::GO_CHAR01);
	ScreenSplit[1]->Character->setType(CharacterObject::GO_CHAR02);
	ScreenSplit[2]->Character->setType(CharacterObject::GO_CHAR03);
	ScreenSplit[3]->Character->setType(CharacterObject::GO_CHAR04);

	currentChar = ScreenSplit[0]->Character;

	// IDLE LEFT
	SpriteAnimation *C01IL = dynamic_cast<SpriteAnimation *>(meshList[GEO_CHARACTER01_IDLE_LEFT]);
	if (C01IL)
	{
		C01IL->m_anim = new Animation();
		C01IL->m_anim->Set(0, 3, 0, 1.f, true);
	}
	SpriteAnimation *C02IL = dynamic_cast<SpriteAnimation *>(meshList[GEO_CHARACTER02_IDLE_LEFT]);
	if (C02IL)
	{
		C02IL->m_anim = new Animation();
		C02IL->m_anim->Set(0, 3, 0, 1.f, true);
	}
	SpriteAnimation *C03IL = dynamic_cast<SpriteAnimation *>(meshList[GEO_CHARACTER03_IDLE_LEFT]);
	if (C03IL)
	{
		C03IL->m_anim = new Animation();
		C03IL->m_anim->Set(0, 3, 0, 1.f, true);
	}
	SpriteAnimation *C04IL = dynamic_cast<SpriteAnimation *>(meshList[GEO_CHARACTER04_IDLE_LEFT]);
	if (C04IL)
	{
		C04IL->m_anim = new Animation();
		C04IL->m_anim->Set(0, 3, 0, 1.f, true);
	}

	// IDLE RIGHT
	SpriteAnimation *C01IR = dynamic_cast<SpriteAnimation *>(meshList[GEO_CHARACTER01_IDLE_RIGHT]);
	if (C01IR)
	{
		C01IR->m_anim = new Animation();
		C01IR->m_anim->Set(0, 3, 0, 1.f, true);
	}
	SpriteAnimation *C02IR = dynamic_cast<SpriteAnimation *>(meshList[GEO_CHARACTER02_IDLE_RIGHT]);
	if (C02IR)
	{
		C02IR->m_anim = new Animation();
		C02IR->m_anim->Set(0, 3, 0, 1.f, true);
	}
	SpriteAnimation *C03IR = dynamic_cast<SpriteAnimation *>(meshList[GEO_CHARACTER03_IDLE_RIGHT]);
	if (C03IR)
	{
		C03IR->m_anim = new Animation();
		C03IR->m_anim->Set(0, 3, 0, 1.f, true);
	}
	SpriteAnimation *C04IR = dynamic_cast<SpriteAnimation *>(meshList[GEO_CHARACTER04_IDLE_RIGHT]);
	if (C04IR)
	{
		C04IR->m_anim = new Animation();
		C04IR->m_anim->Set(0, 3, 0, 1.f, true);
	}

	// MOVE LEFT
	SpriteAnimation *C01ML = dynamic_cast<SpriteAnimation *>(meshList[GEO_CHARACTER01_MOVE_LEFT]);
	if (C01ML)
	{
		C01ML->m_anim = new Animation();
		C01ML->m_anim->Set(0, 3, 0, 1.f, true);
	}
	SpriteAnimation *C02ML = dynamic_cast<SpriteAnimation *>(meshList[GEO_CHARACTER02_MOVE_LEFT]);
	if (C02ML)
	{
		C02ML->m_anim = new Animation();
		C02ML->m_anim->Set(0, 3, 0, 1.f, true);
	}
	SpriteAnimation *C03ML = dynamic_cast<SpriteAnimation *>(meshList[GEO_CHARACTER03_MOVE_LEFT]);
	if (C03ML)
	{
		C03ML->m_anim = new Animation();
		C03ML->m_anim->Set(0, 3, 0, 1.f, true);
	}
	SpriteAnimation *C04ML = dynamic_cast<SpriteAnimation *>(meshList[GEO_CHARACTER04_MOVE_LEFT]);
	if (C04ML)
	{
		C04ML->m_anim = new Animation();
		C04ML->m_anim->Set(0, 3, 0, 1.f, true);
	}

	// MOVE RIGHT
	SpriteAnimation *C01MR = dynamic_cast<SpriteAnimation *>(meshList[GEO_CHARACTER01_MOVE_RIGHT]);
	if (C01MR)
	{
		C01MR->m_anim = new Animation();
		C01MR->m_anim->Set(0, 3, 0, 1.f, true);
	}
	SpriteAnimation *C02MR = dynamic_cast<SpriteAnimation *>(meshList[GEO_CHARACTER02_MOVE_RIGHT]);
	if (C02MR)
	{
		C02MR->m_anim = new Animation();
		C02MR->m_anim->Set(0, 3, 0, 1.f, true);
	}
	SpriteAnimation *C03MR = dynamic_cast<SpriteAnimation *>(meshList[GEO_CHARACTER03_MOVE_RIGHT]);
	if (C03MR)
	{
		C03MR->m_anim = new Animation();
		C03MR->m_anim->Set(0, 3, 0, 1.f, true);
	}
	SpriteAnimation *C04MR = dynamic_cast<SpriteAnimation *>(meshList[GEO_CHARACTER04_MOVE_RIGHT]);
	if (C04MR)
	{
		C04MR->m_anim = new Animation();
		C04MR->m_anim->Set(0, 3, 0, 1.f, true);
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

	phase = 1;
	prevlevel = 0;
	currentlevel = 0;
	SceneState = S_GAME;

	Continue = new MenuObject(MenuObject::M_CONTINUE, Vector3(40, 40, 1));
	Continue->setPos(Vector3(m_worldWidth * 0.9f, m_worldHeight * 0.1f, 0));
	Continue->setActive(true);

	day = 0;
	for (int i = 0; i < 4; i++)
	{
		ScreenSplit[i]->Character->giveUp = false;
	}
}
void StudioProjectScene::Update(double dt)
{

	if (!StatManager::GetInstance()->GetBool_Game(StatManager::GetInstance()->GetPrevGame()))
	{
		switch (StatManager::GetInstance()->GetPrevGame())
		{
		case 1:
			StatManager::GetInstance()->SetBool_Maze(true);
			break;
		case 2:
			StatManager::GetInstance()->SetBool_Mole(true);
			break;
		case 3:
			StatManager::GetInstance()->SetBool_Tank(true);
			break;
		case 4:
			StatManager::GetInstance()->SetBool_Frogger(true);
			break;
		case 5:
			StatManager::GetInstance()->SetBool_Sheep(true);
			break;
		default:
			break;
		}
	}
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

	//Losing Condition



	/////


	switch (SceneState)
	{
	case S_GAME:
	{
		UpdateGame(dt);
		break;
	}
	case S_LEVELTRANSITION:
	{
		soundSystem.stopAllMusic();
		UpdateLevelTransition(dt);
		break;
	}
	case S_GAMEOVER:
	{
		UpdateLoseScreen(dt);
		break;
	}
	case S_GAMEWIN:
	{
		UpdateLoseScreen(dt);
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
			m_eventTimer = Math::RandFloatMinMax(20.f, 40.f);
			day++;
			break;
		}
		case 5:
		{
			SceneState = S_LEVELTRANSITION;
			phase = 0;
			mTimer = 2.f;
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

			break;
		}
		}

	}

	UpdateParticles(dt);
	//cout << "Event Timer : " << m_eventTimer << endl;
}

void StudioProjectScene::UpdateGame(double dt)
{
	ScreenSplit[0]->UseItem->setPos(Vector3(m_worldWidth * 0.45f, m_worldHeight * 0.55f, 0));
	ScreenSplit[1]->UseItem->setPos(Vector3(m_worldWidth * 0.95f, m_worldHeight * 0.55f, 0));
	ScreenSplit[2]->UseItem->setPos(Vector3(m_worldWidth * 0.45f, m_worldHeight * 0.05f, 0));
	ScreenSplit[3]->UseItem->setPos(Vector3(m_worldWidth * 0.95f, m_worldHeight * 0.05f, 0));

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
	totalWD = (ScreenSplit[0]->Character->Statistics.m_workDone
		+ ScreenSplit[1]->Character->Statistics.m_workDone
		+ ScreenSplit[2]->Character->Statistics.m_workDone
		+ ScreenSplit[3]->Character->Statistics.m_workDone) / 4;

	if (CharacterObject::m_Count < 1)
	{
		SceneState = S_GAMEOVER;
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
	bounceTime -= dt;
	//CHEAT CODES BY SEAN
	//Transition to maze
	if (Application::IsKeyPressed(VK_NUMPAD1) && bounceTime < 0)
	{
		soundSystem.stopAllMusic();
		Application::setScene(1);
		reset();
	}
	//Transition to Mole
	if (Application::IsKeyPressed(VK_NUMPAD2) && bounceTime < 0)
	{
		soundSystem.stopAllMusic();
		Application::setScene(2);
		reset();
		bounceTime = 0.5f;
	}
	//Transition to Tank Scene
	if (Application::IsKeyPressed(VK_NUMPAD3) && bounceTime < 0)
	{
		soundSystem.stopAllMusic();
		Application::setScene(3);
		reset();
		bounceTime = 0.5f;
	}
	//Transition to Frog Scene
	if (Application::IsKeyPressed(VK_NUMPAD4) && bounceTime < 0)
	{
		soundSystem.stopAllMusic();
		Application::setScene(4);
		reset();
		bounceTime = 0.5f;
	}
	//Transition to Sheep Game
	if (Application::IsKeyPressed(VK_NUMPAD5) && bounceTime < 0)
	{
		soundSystem.stopAllMusic();
		Application::setScene(5);
		reset();
		bounceTime = 0.5f;
	}
	//CHEAT CODES BY SEAN

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

	// IDLE LEFT
	SpriteAnimation *C01IL = dynamic_cast<SpriteAnimation *>(meshList[GEO_CHARACTER01_IDLE_LEFT]);
	if (C01IL)
	{
		C01IL->Update(dt);
		C01IL->m_anim->animActive = true;
	}
	SpriteAnimation *C02IL = dynamic_cast<SpriteAnimation *>(meshList[GEO_CHARACTER02_IDLE_LEFT]);
	if (C02IL)
	{
		C02IL->Update(dt);
		C02IL->m_anim->animActive = true;;
	}
	SpriteAnimation *C03IL = dynamic_cast<SpriteAnimation *>(meshList[GEO_CHARACTER03_IDLE_LEFT]);
	if (C03IL)
	{
		C03IL->Update(dt);
		C03IL->m_anim->animActive = true;
	}
	SpriteAnimation *C04IL = dynamic_cast<SpriteAnimation *>(meshList[GEO_CHARACTER04_IDLE_LEFT]);
	if (C04IL)
	{
		C04IL->Update(dt);
		C04IL->m_anim->animActive = true;
	}

	// IDLE RIGHT
	SpriteAnimation *C01IR = dynamic_cast<SpriteAnimation *>(meshList[GEO_CHARACTER01_IDLE_RIGHT]);
	if (C01IR)
	{
		C01IR->Update(dt);
		C01IR->m_anim->animActive = true;
	}
	SpriteAnimation *C02IR = dynamic_cast<SpriteAnimation *>(meshList[GEO_CHARACTER02_IDLE_RIGHT]);
	if (C02IR)
	{
		C02IR->Update(dt);
		C02IR->m_anim->animActive = true;
	}
	SpriteAnimation *C03IR = dynamic_cast<SpriteAnimation *>(meshList[GEO_CHARACTER03_IDLE_RIGHT]);
	if (C03IR)
	{
		C03IR->Update(dt);
		C03IR->m_anim->animActive = true;
	}
	SpriteAnimation *C04IR = dynamic_cast<SpriteAnimation *>(meshList[GEO_CHARACTER04_IDLE_RIGHT]);
	if (C04IR)
	{
		C04IR->Update(dt);
		C04IR->m_anim->animActive = true;
	}

	// MOVE LEFT
	SpriteAnimation *C01ML = dynamic_cast<SpriteAnimation *>(meshList[GEO_CHARACTER01_MOVE_LEFT]);
	if (C01ML)
	{
		C01ML->Update(dt);
		C01ML->m_anim->animActive = true;
	}
	SpriteAnimation *C02ML = dynamic_cast<SpriteAnimation *>(meshList[GEO_CHARACTER02_MOVE_LEFT]);
	if (C02ML)
	{
		C02ML->Update(dt);
		C02ML->m_anim->animActive = true;
	}
	SpriteAnimation *C03ML = dynamic_cast<SpriteAnimation *>(meshList[GEO_CHARACTER03_MOVE_LEFT]);
	if (C03ML)
	{
		C03ML->Update(dt);
		C03ML->m_anim->animActive = true;
	}
	SpriteAnimation *C04ML = dynamic_cast<SpriteAnimation *>(meshList[GEO_CHARACTER04_MOVE_LEFT]);
	if (C04ML)
	{
		C04ML->Update(dt);
		C04ML->m_anim->animActive = true;
	}

	// MOVE RIGHT
	SpriteAnimation *C01MR = dynamic_cast<SpriteAnimation *>(meshList[GEO_CHARACTER01_MOVE_RIGHT]);
	if (C01MR)
	{
		C01MR->Update(dt);
		C01MR->m_anim->animActive = true;
	}
	SpriteAnimation *C02MR = dynamic_cast<SpriteAnimation *>(meshList[GEO_CHARACTER02_MOVE_RIGHT]);
	if (C02MR)
	{
		C02MR->Update(dt);
		C02MR->m_anim->animActive = true;
	}
	SpriteAnimation *C03MR = dynamic_cast<SpriteAnimation *>(meshList[GEO_CHARACTER03_MOVE_RIGHT]);
	if (C03MR)
	{
		C03MR->Update(dt);
		C03MR->m_anim->animActive = true;
	}
	SpriteAnimation *C04MR = dynamic_cast<SpriteAnimation *>(meshList[GEO_CHARACTER04_MOVE_RIGHT]);
	if (C04MR)
	{
		C04MR->Update(dt);
		C04MR->m_anim->animActive = true;
	}
	mTimer -= dt;
	if (mTimer < 0 && playMusic == false)
	{
		soundSystem.playMainMusic();
		playMusic = true;
	}
}

void StudioProjectScene::UpdateLoseScreen(double dt)
{
	if (Application::IsKeyPressed(VK_SPACE))
	{
		Application::setScene(6);
		reset();
	}
}

void StudioProjectScene::reset()
{
	m_speed = 1.f;
	m_eventTimer = Math::RandFloatMinMax(20.0f, 40.f);
	b_transitioning = false;
	mTimer = 2.f;
	playMusic = false;
	ScreenSplit[0]->Character->reset();
	ScreenSplit[1]->Character->reset();
	ScreenSplit[2]->Character->reset();
	ScreenSplit[3]->Character->reset();
	currentChar = ScreenSplit[0]->Character;
	phase = 1;
	prevlevel = 0;
	currentlevel = 0;
	SceneState = S_GAME;

	Continue->setPos(Vector3(m_worldWidth * 0.9f, m_worldHeight * 0.1f, 0));
	Continue->setActive(true);
}
void StudioProjectScene::UpdateLevelTransition(double dt)
{
	Continue->Update(v_mousepos);
	if (Continue->getChanged())
	{
		m_eventTimer = -0.01;
		SceneState = S_GAME;
		phase = 0;
		Continue->setChanged(false);
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
	modelStack.Translate(currentChar->getPos() + Vector3(0,20,0));
	modelStack.Rotate(Math::RadianToDegree(atan2(camera.position.x - 0, camera.position.z - 0)), 0, 1, 0);
	modelStack.Scale(15, 15, 1);
	RenderMesh(meshList[GEO_ARROW], false);
	modelStack.PopMatrix();
}
void StudioProjectScene::RenderGiveUp()
{
	modelStack.PushMatrix();
	modelStack.Translate(m_worldWidth/2, m_worldHeight/2, 1);
	modelStack.Scale(m_worldWidth, m_worldHeight, 1);
	RenderMesh(meshList[GEO_GIVEUP], false);
	modelStack.PopMatrix();
}
void StudioProjectScene::RenderWinScreen()
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
	if (totalWD >= 90)
	{
		modelStack.PushMatrix();
		modelStack.Translate(m_worldWidth / 2, m_worldHeight / 2, 0);
		modelStack.Scale(m_worldWidth / 2, m_worldWidth / 2, 0);
		RenderMesh(meshList[GEO_WINSCREEN], false);
		modelStack.PopMatrix();
	}
	if (totalWD >= 75 && totalWD < 90)
	{
		modelStack.PushMatrix();
		modelStack.Translate(m_worldWidth / 2, m_worldHeight / 2, 0);
		modelStack.Scale(m_worldWidth / 2, m_worldWidth / 2, 0);
		RenderMesh(meshList[GEO_WINSCREENB], false);
		modelStack.PopMatrix();
	}
	if (totalWD >= 60 && totalWD < 75)
	{
		modelStack.PushMatrix();
		modelStack.Translate(m_worldWidth / 2, m_worldHeight / 2, 0);
		modelStack.Scale(m_worldWidth / 2, m_worldWidth / 2, 0);
		RenderMesh(meshList[GEO_WINSCREENC], false);
		modelStack.PopMatrix();
	}
	if (totalWD >= 50 && totalWD < 75)
	{
		modelStack.PushMatrix();
		modelStack.Translate(m_worldWidth / 2, m_worldHeight / 2, 0);
		modelStack.Scale(m_worldWidth / 2, m_worldWidth / 2, 0);
		RenderMesh(meshList[GEO_WINSCREEND], false);
		modelStack.PopMatrix();
	}
	if (totalWD < 50)
	{
		modelStack.PushMatrix();
		modelStack.Translate(m_worldWidth / 2, m_worldHeight / 2, 0);
		modelStack.Scale(m_worldWidth / 2, m_worldWidth / 2, 0);
		RenderMesh(meshList[GEO_LOSESCREEN], false);
		modelStack.PopMatrix();
	}
	std::ostringstream ss;
	ss.precision(3);
	ss << totalWD;
	RenderTextOnScreen(meshList[GEO_TEXT], ss.str(), Color(1, 0, 0), 3, 38, 20.5f);

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
	case S_GAMEWIN:
	{
		RenderWinScreen();
		break;
	}
	case S_GAMEOVER:
	{
		RenderLoseScreen();
		break;
	}
	default:
	{
		RenderLoseScreen();
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
	//std::ostringstream ss;
	//ss.precision(3);
	//ss << rel_mousepos;
	//RenderTextOnScreen(meshList[GEO_TEXT], ss.str(), Color(0, 1, 0), 3, 1, 1);

	//ss.str("");
	//ss << v_mousepos;
	//RenderTextOnScreen(meshList[GEO_TEXT], ss.str(), Color(0, 1, 0), 3, 1, 4);
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

void StudioProjectScene::RenderLoseScreen()
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
	modelStack.Translate(m_worldWidth / 2, m_worldHeight / 2, 0);
	modelStack.Scale(m_worldWidth/2, m_worldWidth/2, 0);
	RenderMesh(meshList[GEO_LOSESCREEN], false);
	modelStack.PopMatrix();

	std::ostringstream ss;
	ss.precision(3);
	ss << totalWD;
	RenderTextOnScreen(meshList[GEO_TEXT], ss.str(), Color(1, 0, 0), 3,38, 20.5f);
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
	modelStack.Translate(Continue->getPos());
	modelStack.Scale(Continue->getScale());
	RenderMesh(meshList[GEO_MAIN_CONTINUE], false);
	modelStack.PopMatrix();

	std::ostringstream ss;
	ss.precision(3);
	ss << "Work Done:";
	RenderTextOnScreen(meshList[GEO_TEXT], ss.str(), Color(0, 1, 0), 3, 1, 33);

	ss.str("");
	int value = (ScreenSplit[0]->Character->Statistics.m_workDone
		+ ScreenSplit[1]->Character->Statistics.m_workDone
		+ ScreenSplit[2]->Character->Statistics.m_workDone
		+ ScreenSplit[3]->Character->Statistics.m_workDone) / 4;
	/*value = value + 10 / 2;
	value -= value % 10;*/
	int add = 0;
	for (int i = 0; i < value; i += 5)
	{
		ss << "@";
		add += 3;
	}
	RenderTextOnScreen(meshList[GEO_TEXT], ss.str(), Color(0, 1, 0), 3, 1, 30);
	ss.str("");
	for (int i = 0; i < 100 - value; i += 5)
	{
		ss << "@";
	}
	RenderTextOnScreen(meshList[GEO_TEXT], ss.str(), Color(1, 0, 0), 3, 1 + add, 30);

	ss.str("");
	ss << "Day " << day << "/5";
	RenderTextOnScreen(meshList[GEO_TEXT], ss.str(), Color(1, 0, 0), 3, 40 - ss.tellp() / 2, 50);
}

void StudioProjectScene::RenderCharObj(CharacterObject * go)
{
	switch (go->getType())
	{
	case CharacterObject::GO_CUBE:
		modelStack.PushMatrix();
		modelStack.Translate(go->getPos());
		modelStack.Scale(go->getScale());
		RenderMesh(meshList[GEO_QUAD], false);
		modelStack.PopMatrix();
		break;
	case CharacterObject::GO_CHAR01:
		if (go->getState() == true)
		{
			modelStack.PushMatrix();
			modelStack.Translate(go->getPos());
			if (go->getDirection() == true)
			{
				modelStack.Scale(go->getScale());
				RenderMesh(meshList[GEO_CHARACTER01_MOVE_LEFT], false);
				modelStack.PopMatrix();
			}
			else
			{
				modelStack.Scale(go->getScale());
				RenderMesh(meshList[GEO_CHARACTER01_MOVE_RIGHT], false);
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
				RenderMesh(meshList[GEO_CHARACTER01_IDLE_LEFT], false);
				modelStack.PopMatrix();
			}
			else
			{
				modelStack.Scale(go->getScale());
				RenderMesh(meshList[GEO_CHARACTER01_IDLE_RIGHT], false);
				modelStack.PopMatrix();
			}
			break;
		}
	case CharacterObject::GO_CHAR02:
		if (go->getState() == true)
		{
			modelStack.PushMatrix();
			modelStack.Translate(go->getPos());
			if (go->getDirection() == true)
			{
				modelStack.Scale(go->getScale());
				RenderMesh(meshList[GEO_CHARACTER02_MOVE_LEFT], false);
				modelStack.PopMatrix();
			}
			else
			{
				modelStack.Scale(go->getScale());
				RenderMesh(meshList[GEO_CHARACTER02_MOVE_RIGHT], false);
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
				RenderMesh(meshList[GEO_CHARACTER02_IDLE_LEFT], false);
				modelStack.PopMatrix();
			}
			else
			{
				modelStack.Scale(go->getScale());
				RenderMesh(meshList[GEO_CHARACTER02_IDLE_RIGHT], false);
				modelStack.PopMatrix();
			}
			break;
		}
	case CharacterObject::GO_CHAR03:
		if (go->getState() == true)
		{
			modelStack.PushMatrix();
			modelStack.Translate(go->getPos());
			if (go->getDirection() == true)
			{
				modelStack.Scale(go->getScale());
				RenderMesh(meshList[GEO_CHARACTER03_MOVE_LEFT], false);
				modelStack.PopMatrix();
			}
			else
			{
				modelStack.Scale(go->getScale());
				RenderMesh(meshList[GEO_CHARACTER03_MOVE_RIGHT], false);
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
				RenderMesh(meshList[GEO_CHARACTER03_IDLE_LEFT], false);
				modelStack.PopMatrix();
			}
			else
			{
				modelStack.Scale(go->getScale());
				RenderMesh(meshList[GEO_CHARACTER03_IDLE_RIGHT], false);
				modelStack.PopMatrix();
			}
			break;
		}
	case CharacterObject::GO_CHAR04:
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
	case CharacterObject::GO_TELEVISION:
		modelStack.PushMatrix();
		modelStack.Translate(go->getPos());
		modelStack.Scale(go->getScale());
		RenderMesh(meshList[GEO_TELEVISION], false);
		modelStack.PopMatrix();
		break;

	case CharacterObject::GO_COMPUTER:
		modelStack.PushMatrix();
		modelStack.Translate(go->getPos());
		modelStack.Scale(go->getScale());
		RenderMesh(meshList[GEO_COMPUTER], false);
		modelStack.PopMatrix();
		break;

	default:
		break;
	}
}

void StudioProjectScene::RenderItemObj(ItemObject * go)
{
	switch (go->getType())
	{
	case ItemObject::I_TELEVISION:
		modelStack.PushMatrix();
		modelStack.Translate(go->getPos());
		modelStack.PushMatrix();
		modelStack.Scale(go->getScale());
		RenderMesh(meshList[GEO_TELEVISION], false);
		modelStack.PopMatrix();
		if (go->bounded)
		{
			modelStack.PushMatrix();
			modelStack.Scale(go->getScale() * 1.1f);
			RenderMesh(meshList[GEO_BORDER], false);
			modelStack.PopMatrix();
		}
		modelStack.PopMatrix();
		break;
	case ItemObject::I_COMPUTER:
		modelStack.PushMatrix();
		modelStack.Translate(go->getPos());
		modelStack.PushMatrix();
		modelStack.Scale(go->getScale());
		RenderMesh(meshList[GEO_COMPUTER], false);
		modelStack.PopMatrix();
		if (go->bounded)
		{
			modelStack.PushMatrix();
			modelStack.Scale(go->getScale() * 1.1f);
			RenderMesh(meshList[GEO_BORDER], false);
			modelStack.PopMatrix();
		}
		modelStack.PopMatrix();
		break;
	case ItemObject::I_BOX:
		modelStack.PushMatrix();
		modelStack.Translate(go->getPos());
		modelStack.PushMatrix();
		modelStack.Scale(go->getScale());
		RenderMesh(meshList[GEO_SLEEPBOX], false);
		modelStack.PopMatrix();
		if (go->bounded)
		{
			modelStack.PushMatrix();
			modelStack.Scale(go->getScale() * 1.1f);
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
		if (!m_goList[i]->getActive())
		{
			m_goList[i]->setActive(true);
			return m_goList[i];
		}
	}

	for (int i = 0; i < 20; ++i)
	{
		m_goList.push_back(new GameObject);
	}
	m_goList[m_goList.size() - 1]->setActive(true);
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
	modelStack.Scale(Application::GetWindowWidth() / 6, Application::GetWindowHeight() / 6, 1);
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
		if (ScreenSplit->m_itemList[i]->getActive())
		{
			RenderItemObj(ScreenSplit->m_itemList[i]);
		}
	}
	// Character
	if (ScreenSplit->Character->getActive())
		RenderCharObj(ScreenSplit->Character);
	if (ScreenSplit->Character->getGiveUp())
	{
		RenderGiveUp();

	}

}

void StudioProjectScene::RenderStats(CharacterObject* Character)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	modelStack.PushMatrix();
	modelStack.Translate(m_worldWidthDiv8 + 10 + Character->Statistics.m_frustration / 2, m_worldHeight / 2 + 15, 0);
	modelStack.Scale(Character->Statistics.m_frustration, 25, 1);
	RenderMesh(meshList[GEO_CHARONEFRUST], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(m_worldWidthDiv8 + 15 + Character->Statistics.m_motivation / 2, m_worldHeight / 2 + 60, 0);
	modelStack.Scale(Character->Statistics.m_motivation, 25, 1);
	RenderMesh(meshList[GEO_CHARONEMOTIVE], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(m_worldWidthDiv8 + 5 + Character->Statistics.m_rest / 2, m_worldHeight / 2 - 30, 0);
	modelStack.Scale(Character->Statistics.m_rest, 25, 1);
	RenderMesh(meshList[GEO_CHARONEREST], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(m_worldWidthDiv8 + Character->Statistics.m_workDone / 2, m_worldHeight / 2 - 75, 0);
	modelStack.Scale(Character->Statistics.m_workDone, 25, 1);
	RenderMesh(meshList[GEO_CHARONEWD], false);
	modelStack.PopMatrix();
}

void StudioProjectScene::RenderMenu(Screen* ScreenSplit)
{
	modelStack.PushMatrix();
	modelStack.Translate(ScreenSplit->UseItem->getPos());
	modelStack.Scale(ScreenSplit->UseItem->getScale());
	if (ScreenSplit->Character->currentItem)
	{
		if (ScreenSplit->UseItem->getChanged())
		{
			RenderMesh(meshList[GEO_MAIN_STOP], false);
		}
		else
		{
			RenderMesh(meshList[GEO_MAIN_USE], false);
		}
	}
	modelStack.PopMatrix();
	modelStack.PushMatrix();
	modelStack.Translate(ScreenSplit->UseItem->getPos().x - m_worldWidth * 0.05, ScreenSplit->UseItem->getPos().y, ScreenSplit->UseItem->getPos().z);
	modelStack.PushMatrix();
	modelStack.Scale(13, 13, 1);
	if (ScreenSplit->Character->currentItem)
	{
		switch (ScreenSplit->Character->currentItem->getType())
		{
		case ItemObject::I_TELEVISION:
		{
			RenderMesh(meshList[GEO_TELEVISION], false);
			break;
		}
		case ItemObject::I_COMPUTER:
		{
			RenderMesh(meshList[GEO_COMPUTER], false);
			break;
		}
		case ItemObject::I_BOX:
		{
			RenderMesh(meshList[GEO_SLEEPBOX], false);
			break;
		}
		}
	}
	modelStack.PopMatrix();
	modelStack.PushMatrix();
	modelStack.Scale(15, 15, 1);
	RenderMesh(meshList[GEO_BORDER], false);
	modelStack.PopMatrix();
	modelStack.PopMatrix();
}
