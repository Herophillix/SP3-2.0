#include "Results.h"

Results* Results::r_instance = nullptr;

Results * Results::getInstance()
{
	if (r_instance == nullptr)
	{
		r_instance = new Results;
	}
	return r_instance;
}

Results::Results()
{
}

// Add on as you please 
void Results::InitVars()
{
	SceneBase::Init();
	// THE PROPS
	meshList[GEO_RESULTSCREEN_QUAD] = MeshBuilder::GenerateQuad("results", Color(0, 0, 0), 1.f);
	meshList[GEO_C01_RESULT_QUAD] = MeshBuilder::GenerateQuad("c01result", Color(1, 1, 1), 1.f);
	//meshList[GEO_C01_RESULT_QUAD]->textureID = LoadTGA("Image//resultTest.tga");
	meshList[GEO_C02_RESULT_QUAD] = MeshBuilder::GenerateQuad("c01result", Color(0.8, 0.8, 0.8), 1.f);
	meshList[GEO_C03_RESULT_QUAD] = MeshBuilder::GenerateQuad("c01result", Color(0.6, 0.6, 0.6), 1.f);
	meshList[GEO_C04_RESULT_QUAD] = MeshBuilder::GenerateQuad("c01result", Color(0.4, 0.4, 0.4), 1.f);

	meshList[GEO_RESULT_PLUS] = MeshBuilder::GenerateQuad("plusButton", Color(0, 0, 1), 1.f);
	meshList[GEO_RESULT_MINUS] = MeshBuilder::GenerateQuad("minusButton", Color(1, 0, 0), 1.f);
	

	meshList[GEO_GAMEFONT] = MeshBuilder::GenerateText("teko", 16, 16);
	meshList[GEO_GAMEFONT]->textureID = LoadTGA("Image//KidsZone.tga");

	// THE VARS
	m_worldHeight = 100.f;
	m_worldWidth = m_worldHeight * (float)Application::GetWindowWidth() / Application::GetWindowHeight();
	m_halfWorldHeight = m_worldHeight / 2;
	m_halfWorldWidth = m_worldWidth / 2;

	m_quarterWorldWidth = m_worldWidth / 4;
	m_eightWorldWidth = m_worldWidth / 8;
	m_sixteenthWorldWidth = m_worldWidth / 16;
	m_thirtytwothWorldWidth = m_worldWidth / 32;

	m_sixthWorldHeight = m_worldHeight / 6;
	m_quarterWorldHeight = m_worldHeight / 4;
	m_twelfthWorldHeight = m_worldHeight / 12;
	m_twentyfourthWorldHeight = m_worldHeight / 24;

	r_quad01Pos.Set(m_quarterWorldWidth, m_sixthWorldHeight * 3, 0.5f);
	r_quad02Pos.Set(m_quarterWorldWidth * 3, m_sixthWorldHeight * 3, 0.5f);
	r_quad03Pos.Set(m_quarterWorldWidth, m_sixthWorldHeight, 0.5f);
	r_quad04Pos.Set(m_quarterWorldWidth * 3, m_sixthWorldHeight, 0.5f);

	m_statsToDistribute = 0;
	m_originStatsToDistribute = 0;
	InitButtons();

	MousePos.SetZero();
}

void Results::UpdateVars(double dt)
{
	SceneBase::Update(dt);
	m_worldHeight = 100.f;
	m_worldWidth = m_worldHeight * (float)Application::GetWindowWidth() / Application::GetWindowHeight();
	m_halfWorldHeight = m_worldHeight / 2;
	m_halfWorldWidth = m_worldWidth / 2;

	m_quarterWorldWidth = m_worldWidth / 4;
	m_eightWorldWidth = m_worldWidth / 8;
	m_sixteenthWorldWidth = m_worldWidth / 16;
	m_thirtytwothWorldWidth = m_worldWidth / 32;

	m_sixthWorldHeight = m_worldHeight / 6;
	m_quarterWorldHeight = m_worldHeight / 4;
	m_twelfthWorldHeight = m_worldHeight / 12;
	m_twentyfourthWorldHeight = m_worldHeight / 24;

	r_quad01Pos.Set(m_quarterWorldWidth, m_sixthWorldHeight * 3, 0.5f);
	r_quad02Pos.Set(m_quarterWorldWidth * 3, m_sixthWorldHeight * 3, 0.5f);
	r_quad03Pos.Set(m_quarterWorldWidth, m_sixthWorldHeight, 0.5f);
	r_quad04Pos.Set(m_quarterWorldWidth * 3, m_sixthWorldHeight, 0.5f);

	// Update mouse pos
	double x, y;
	Application::GetCursorPos(&x, &y);
	int w = Application::GetWindowWidth();
	int h = Application::GetWindowHeight();
	float posX = static_cast<float>(x) / w * m_worldWidth;
	float posY = (h - static_cast<float>(y)) / h * m_worldHeight;

	MousePos.Set(posX, posY, 0);
}

// MAIN RENDERING FUNCTION
void Results::RenderResults(int score)
{
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


	// the black bg the player sees
	modelStack.PushMatrix();
	modelStack.Translate(m_halfWorldWidth, m_halfWorldHeight, 0.6f);
	modelStack.Scale(198, 108, 1);
	RenderMesh(meshList[GEO_RESULTSCREEN_QUAD], false);
	modelStack.PopMatrix();

	std::ostringstream ss;
	ss << "MINIGAME OVER";
	RenderTextOnScreen(meshList[GEO_GAMEFONT], ss.str(), Color(1, 1, 1), 5, 10, 50);



	ss.clear();
	ss.str("");
	ss << "Score: " << score;
	RenderTextOnScreen(meshList[GEO_GAMEFONT], ss.str(), Color(1, 1, 1), 2, 5, 45);

	ss.clear();
	ss.str("");
	ss << "Stats left: " << m_statsToDistribute;
	RenderTextOnScreen(meshList[GEO_GAMEFONT], ss.str(), Color(1, 1, 1), 2, 50, 45);
	// get instance of player stats

	// Render Character Quad -> stats
	// C01 Quad
	modelStack.PushMatrix();
	modelStack.Translate(r_quad01Pos);
	modelStack.Scale(96, 33.5f, 1);
	RenderMesh(meshList[GEO_C01_RESULT_QUAD], false);
	modelStack.PopMatrix();

	// C02 Quad
	modelStack.PushMatrix();
	modelStack.Translate(r_quad02Pos);
	modelStack.Scale(96, 33.5f, 1);
	RenderMesh(meshList[GEO_C02_RESULT_QUAD], false);
	modelStack.PopMatrix();

	// C03 Quad
	modelStack.PushMatrix();
	modelStack.Translate(r_quad03Pos);
	modelStack.Scale(96, 33.5f, 1);
	RenderMesh(meshList[GEO_C03_RESULT_QUAD], false);
	modelStack.PopMatrix();

	// C04 Quad
	modelStack.PushMatrix();
	modelStack.Translate(r_quad04Pos);	
	modelStack.Scale(96, 33.5f, 1);
	RenderMesh(meshList[GEO_C04_RESULT_QUAD], false);
	modelStack.PopMatrix();


	// Buttons
	RenderButtons();

	// Stats
	RenderStats();

	// Render Reset and Continue
	modelStack.PushMatrix();
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.PopMatrix();
}

void Results::RenderGO(ResultObject * go)
{
	switch (go->objType)
	{
	case ResultObject::GO_PLUS:
		modelStack.PushMatrix();
		modelStack.Translate(go->pos.x, go->pos.y, go->pos.z);
		modelStack.Scale(go->scale.x, go->scale.y, go->scale.z);
		RenderMesh(meshList[GEO_RESULT_PLUS], false);
		modelStack.PopMatrix();
		break;
	case ResultObject::GO_MINUS:
		modelStack.PushMatrix();
		modelStack.Translate(go->pos.x, go->pos.y, go->pos.z);
		modelStack.Scale(go->scale.x, go->scale.y, go->scale.z);
		RenderMesh(meshList[GEO_RESULT_MINUS], false);
		modelStack.PopMatrix();
		break;
	default:
		break;
	}
}

void Results::InitButtons()
{

	// Create for loop to store buttons
	// 4 For loops for each button for each type?
	// + M buttons
	for (unsigned int i = 0; i < 4; i++)
	{
		ResultObject* temp = new ResultObject(ResultObject::GO_NONE);
		temp->objType = ResultObject::GO_PLUS;
		temp->belong = (ResultObject::WHICH_CHARACTER)(i + 1);
		temp->stat = ResultObject::S_MOTIVATION;
		temp->scale.Set(11.25f, 17.f, 1);
		switch (i)
		{
		case 0:
			temp->pos.Set((r_quad01Pos.x - 3 * m_thirtytwothWorldWidth), (r_quad01Pos.y + m_twelfthWorldHeight), 0.65f);
			break;
		case 1:
			temp->pos.Set((r_quad02Pos.x - m_thirtytwothWorldWidth), (r_quad02Pos.y + m_twelfthWorldHeight), 0.65f);
			break;
		case 2:
			temp->pos.Set((r_quad03Pos.x - 3 * m_thirtytwothWorldWidth), (r_quad03Pos.y + m_twelfthWorldHeight), 0.65f);
			break;
		case 3:
			temp->pos.Set((r_quad04Pos.x - m_thirtytwothWorldWidth), (r_quad04Pos.y + m_twelfthWorldHeight), 0.65f);
			break;
		default:
			break;
		}
		ButtonList.push_back(temp);
	}
	// - M buttons
	for (unsigned int i = 0; i < 4; i++)
	{
		ResultObject* temp = new ResultObject(ResultObject::GO_NONE);
		temp->objType = ResultObject::GO_MINUS;
		temp->belong = (ResultObject::WHICH_CHARACTER)(i + 1);
		temp->stat = ResultObject::S_MOTIVATION;
		temp->scale.Set(11.25f, 17.f, 1);
		switch (i)
		{
		case 0:
			temp->pos.Set((r_quad01Pos.x - m_thirtytwothWorldWidth), (r_quad01Pos.y + m_twelfthWorldHeight), 0.65f);
			break;
		case 1:
			temp->pos.Set((r_quad02Pos.x + m_thirtytwothWorldWidth), (r_quad02Pos.y + m_twelfthWorldHeight), 0.65f);
			break;
		case 2:
			temp->pos.Set((r_quad03Pos.x - m_thirtytwothWorldWidth), (r_quad03Pos.y + m_twelfthWorldHeight), 0.65f);
			break;
		case 3:
			temp->pos.Set((r_quad04Pos.x + m_thirtytwothWorldWidth), (r_quad04Pos.y + m_twelfthWorldHeight), 0.65f);
			break;
		default:
			break;
		}
		ButtonList.push_back(temp);
	}
	// + F Buttons
	for (unsigned int i = 0; i < 4; i++)
	{
		ResultObject* temp = new ResultObject(ResultObject::GO_NONE);
		temp->objType = ResultObject::GO_PLUS;
		temp->belong = (ResultObject::WHICH_CHARACTER)(i + 1);
		temp->stat = ResultObject::S_FRUSTRATION;
		temp->scale.Set(11.25f, 17.f, 1);
		switch (i)
		{
		case 0:
			temp->pos.Set((r_quad01Pos.x - 3 * m_thirtytwothWorldWidth), (r_quad01Pos.y - m_twelfthWorldHeight), 0.65f);
			break;
		case 1:
			temp->pos.Set((r_quad02Pos.x - m_thirtytwothWorldWidth), (r_quad02Pos.y - m_twelfthWorldHeight), 0.65f);
			break;
		case 2:
			temp->pos.Set((r_quad03Pos.x - 3 * m_thirtytwothWorldWidth), (r_quad03Pos.y - m_twelfthWorldHeight), 0.65f);
			break;
		case 3:
			temp->pos.Set((r_quad04Pos.x - m_thirtytwothWorldWidth), (r_quad04Pos.y - m_twelfthWorldHeight), 0.65f);
			break;
		default:
			break;
		}
		ButtonList.push_back(temp);
	}
	// - F Buttons
	for (unsigned int i = 0; i < 4; i++)
	{
		ResultObject* temp = new ResultObject(ResultObject::GO_NONE);
		temp->objType = ResultObject::GO_MINUS;
		temp->belong = (ResultObject::WHICH_CHARACTER)(i + 1);
		temp->stat = ResultObject::S_FRUSTRATION;
		temp->scale.Set(11.25f, 17.f, 1);
		switch (i)
		{
		case 0:
			temp->pos.Set((r_quad01Pos.x - m_thirtytwothWorldWidth), (r_quad01Pos.y - m_twelfthWorldHeight), 0.65f);
			break;
		case 1:
			temp->pos.Set((r_quad02Pos.x + m_thirtytwothWorldWidth), (r_quad02Pos.y - m_twelfthWorldHeight), 0.65f);
			break;
		case 2:
			temp->pos.Set((r_quad03Pos.x - m_thirtytwothWorldWidth), (r_quad03Pos.y - m_twelfthWorldHeight), 0.65f);
			break;
		case 3:
			temp->pos.Set((r_quad04Pos.x + m_thirtytwothWorldWidth), (r_quad04Pos.y - m_twelfthWorldHeight), 0.65f);
			break;
		default:
			break;
		}
		ButtonList.push_back(temp);
	}
	// Objects C01
	//c01PlusM = new ResultObject(ResultObject::GO_NONE);
	//c01PlusM->objType = ResultObject::GO_PLUS;
	//c01PlusM->belong = (ResultObject::WHICH_CHARACTER)1;
	//c01PlusM->active = false;
	//c01PlusM->pos.Set((r_quad01Pos.x - 3 * m_thirtytwothWorldWidth), (r_quad01Pos.y + m_twelfthWorldHeight), 0.65f);
	//c01PlusM->scale.Set(11.25f, 17.f, 1);
	//c01MinusM = new ResultObject(ResultObject::GO_NONE);
	//c01MinusM->objType = ResultObject::GO_MINUS;
	//c01MinusM->belong = (ResultObject::WHICH_CHARACTER)1;
	//c01MinusM->active = false;
	//c01MinusM->pos.Set((r_quad01Pos.x - m_thirtytwothWorldWidth), (r_quad01Pos.y + m_twelfthWorldHeight), 0.65f);
	//c01MinusM->scale.Set(11.25f, 17.f, 1);

	//c01PlusF = new ResultObject(ResultObject::GO_NONE);
	//c01PlusF->objType = ResultObject::GO_PLUS;
	//c01PlusF->belong = (ResultObject::WHICH_CHARACTER)1;
	//c01PlusF->active = false;
	//c01PlusF->pos.Set((r_quad01Pos.x - 3 * m_thirtytwothWorldWidth), (r_quad01Pos.y - m_twelfthWorldHeight), 0.65f);
	//c01PlusF->scale.Set(11.25f, 17.f, 1);
	//c01MinusF = new ResultObject(ResultObject::GO_NONE);
	//c01MinusF->objType = ResultObject::GO_MINUS;
	//c01MinusF->belong = (ResultObject::WHICH_CHARACTER)1;
	//c01MinusF->active = false;
	//c01MinusF->pos.Set((r_quad01Pos.x - m_thirtytwothWorldWidth), (r_quad01Pos.y - m_twelfthWorldHeight), 0.65f);
	//c01MinusF->scale.Set(11.25f, 17.f, 1);

}

void Results::InitStatsToDist(int stats)
{
	m_statsToDistribute = stats;
	m_originStatsToDistribute = stats;
}

void Results::RenderButtons()
{
	//RenderGO(c01PlusM);
	//RenderGO(c01MinusM);
	//RenderGO(c01PlusF);
	//RenderGO(c01MinusF);

	for (unsigned int i = 0; i < ButtonList.size(); i++)
	{
		RenderGO(ButtonList[i]);
	}
}

bool Results::ButtonMouseCollision()
{
	for (unsigned int i = 0; i < ButtonList.size(); i++)
	{
		if (MousePos.x < ButtonList[i]->pos.x + ButtonList[i]->scale.x / 2
			&& MousePos.x > ButtonList[i]->pos.x - ButtonList[i]->scale.x / 2)
		{
			if (MousePos.y < ButtonList[i]->pos.y + ButtonList[i]->scale.y / 2
				&& MousePos.y > ButtonList[i]->pos.y - ButtonList[i]->scale.y / 2)
			{
				switch (ButtonList[i]->belong)
				{
				case ResultObject::WHICH_CHARACTER::C_01:
					cout << "Character 01, ";
					switch (ButtonList[i]->stat)
					{
					case ResultObject::WHICH_STAT::S_MOTIVATION:
						cout << "Motivation stat, ";
						if (ButtonList[i]->objType == ResultObject::GO_PLUS)
						{
							cout << "Plus button";
							if ((StatManager::GetInstance()->GetChar01().m_motivation + 1) <= 100.f && m_statsToDistribute != 0)
							{
								StatManager::GetInstance()->UpdateChar01M(1);
								m_statsToDistribute--;
								return true;
							}
							else
							{
								cout << " ....Sike bitch you thought";
								return false;
								// REJECT SFX outside
							}
						}
						else if (ButtonList[i]->objType == ResultObject::GO_MINUS)
						{
							cout << "Minus button";
							if ((StatManager::GetInstance()->GetChar01().m_motivation - 1) >= StatManager::GetInstance()->GetChar01().m_originMotivation)
							{
								StatManager::GetInstance()->UpdateChar01M(-1);
								m_statsToDistribute++;
								return true;
							}
							else
							{
								cout << " ....Sike bitch you thought";
								return false;
							}
						}
						break;
					case ResultObject::WHICH_STAT::S_FRUSTRATION:
						cout << "Frustration stat, ";
						if (ButtonList[i]->objType == ResultObject::GO_PLUS)
						{
							cout << "Plus button";
							if ((StatManager::GetInstance()->GetChar01().m_frustration + 1) <= StatManager::GetInstance()->GetChar01().m_originFrustration)
							{
								StatManager::GetInstance()->UpdateChar01F(1);
								m_statsToDistribute++;
								return true;
							}
							else
							{
								cout << " ....Sike bitch you thought";
								return false;
							}
						}
						else if (ButtonList[i]->objType == ResultObject::GO_MINUS)
						{
							cout << "Minus button";
							if ((StatManager::GetInstance()->GetChar01().m_frustration - 1) >= 0.f && m_statsToDistribute != 0)
							{
								StatManager::GetInstance()->UpdateChar01F(-1);
								m_statsToDistribute--;
								return true;
							}
							else
							{
								cout << " ....Sike bitch you thought";
								return false;
							}
						}
						break;
					default:
						break;
					}
					break;
				case ResultObject::WHICH_CHARACTER::C_02:
					cout << "Character 02 Button: ";
					switch (ButtonList[i]->stat)
					{
					case ResultObject::WHICH_STAT::S_MOTIVATION:
						cout << "Motivation stat, ";
						if (ButtonList[i]->objType == ResultObject::GO_PLUS)
						{
							cout << "Plus button";
							if ((StatManager::GetInstance()->GetChar02().m_motivation + 1) <= 100.f && m_statsToDistribute != 0)
							{
								StatManager::GetInstance()->UpdateChar02M(1);
								m_statsToDistribute--;
								return true;
							}
							else
							{
								cout << " ....Sike bitch you thought";
								return false;
							}
						}
						else if (ButtonList[i]->objType == ResultObject::GO_MINUS)
						{
							cout << "Minus button";
							if ((StatManager::GetInstance()->GetChar02().m_motivation - 1) >= StatManager::GetInstance()->GetChar02().m_originMotivation)
							{
								StatManager::GetInstance()->UpdateChar02M(-1);
								m_statsToDistribute++;
								return true;
							}
							else
							{
								return false;
							}
						}
						break;
					case ResultObject::WHICH_STAT::S_FRUSTRATION:
						cout << "Frustration stat, ";
						if (ButtonList[i]->objType == ResultObject::GO_PLUS)
						{
							cout << "Plus button";
							if ((StatManager::GetInstance()->GetChar02().m_frustration + 1) <= StatManager::GetInstance()->GetChar02().m_originFrustration)
							{
								StatManager::GetInstance()->UpdateChar02F(1);
								m_statsToDistribute++;
								return true;
							}
							else
							{
								return false;
							}
						}
						else if (ButtonList[i]->objType == ResultObject::GO_MINUS)
						{
							cout << "Minus button";
							if ((StatManager::GetInstance()->GetChar02().m_frustration - 1) >= 0.f && m_statsToDistribute != 0)
							{
								StatManager::GetInstance()->UpdateChar02F(-1);
								m_statsToDistribute--;
								return true;
							}
							else
							{
								return false;
							}
						}
						break;
					default:
						break;
					}
					break;
				case ResultObject::WHICH_CHARACTER::C_03:
					cout << "Character 03 Button: ";
					switch (ButtonList[i]->stat)
					{
					case ResultObject::WHICH_STAT::S_MOTIVATION:
						cout << "Motivation stat, ";
						if (ButtonList[i]->objType == ResultObject::GO_PLUS)
						{
							cout << "Plus button";
							if ((StatManager::GetInstance()->GetChar03().m_motivation + 1) <= 100.f && m_statsToDistribute != 0)
							{
								StatManager::GetInstance()->UpdateChar03M(1);
								m_statsToDistribute--;
								return true;
							}
							else
							{
								return false;
							}
						}
						else if (ButtonList[i]->objType == ResultObject::GO_MINUS)
						{
							cout << "Minus button";
							if ((StatManager::GetInstance()->GetChar03().m_motivation - 1) >= StatManager::GetInstance()->GetChar03().m_originMotivation)
							{
								StatManager::GetInstance()->UpdateChar03M(-1);
								m_statsToDistribute++;
								return true;
							}
							else
							{
								return false;
							}
						}
						break;
					case ResultObject::WHICH_STAT::S_FRUSTRATION:
						cout << "Frustration stat, ";
						if (ButtonList[i]->objType == ResultObject::GO_PLUS)
						{
							cout << "Plus button";
							if ((StatManager::GetInstance()->GetChar03().m_frustration + 1) <= StatManager::GetInstance()->GetChar03().m_originFrustration)
							{
								StatManager::GetInstance()->UpdateChar03F(1);
								m_statsToDistribute++;
								return true;
							}
						}
						else if (ButtonList[i]->objType == ResultObject::GO_MINUS)
						{
							cout << "Minus button";
							if ((StatManager::GetInstance()->GetChar03().m_frustration - 1) >= 0.f && m_statsToDistribute != 0)
							{
								StatManager::GetInstance()->UpdateChar03F(-1);
								m_statsToDistribute--;
								return true;
							}
							else
							{
								return false;
							}
						}
						break;
					default:
						break;
					}
					break;
				case ResultObject::WHICH_CHARACTER::C_04:
					cout << "Character 04 Button: ";
					switch (ButtonList[i]->stat)
					{
					case ResultObject::WHICH_STAT::S_MOTIVATION:
						cout << "Motivation stat, ";
						if (ButtonList[i]->objType == ResultObject::GO_PLUS)
						{
							cout << "Plus button";
							if ((StatManager::GetInstance()->GetChar04().m_motivation + 1) <= 100.f && m_statsToDistribute != 0)
							{
								StatManager::GetInstance()->UpdateChar04M(1);
								m_statsToDistribute--;
								return true;
							}
							else
							{
								return false;
							}
						}
						else if (ButtonList[i]->objType == ResultObject::GO_MINUS)
						{
							cout << "Minus button";
							if ((StatManager::GetInstance()->GetChar04().m_motivation - 1) >= StatManager::GetInstance()->GetChar04().m_originMotivation)
							{
								StatManager::GetInstance()->UpdateChar04M(-1);
								m_statsToDistribute++;
								return true;
							}
							else
							{
								return false;
							}
						}
						break;
					case ResultObject::WHICH_STAT::S_FRUSTRATION:
						cout << "Frustration stat, ";
						if (ButtonList[i]->objType == ResultObject::GO_PLUS)
						{
							cout << "Plus button";
							if ((StatManager::GetInstance()->GetChar04().m_frustration + 1) <= StatManager::GetInstance()->GetChar04().m_originFrustration)
							{
								StatManager::GetInstance()->UpdateChar04F(1);
								m_statsToDistribute++;
								return true;
							}
							else
							{
								return false;
							}
						}
						else if (ButtonList[i]->objType == ResultObject::GO_MINUS)
						{
							cout << "Minus button ";
							if ((StatManager::GetInstance()->GetChar04().m_frustration - 1) >= 0.f && m_statsToDistribute != 0)
							{
								StatManager::GetInstance()->UpdateChar04F(-1);
								m_statsToDistribute--;
								return true;
							}
							else
							{
								return false;
							}
						}
						break;
					default:
						break;
					}
					break;
				case ResultObject::WHICH_CHARACTER::C_NONE:
					switch (ButtonList[i]->objType)
					{
					case ResultObject::GO_CONTINUE:
						if (m_statsToDistribute == 0)
						{
							//switch scene
							return true;
						}
						break;
					case ResultObject::GO_RESET:
						StatManager::GetInstance()->ResetValues();
						m_statsToDistribute = m_originStatsToDistribute;
						break;
					default:
						break;
					}
					break;
				default:
					break;
				}
				cout << endl;
			}
		}
	}
	return false;
}

void Results::RenderStats()
{

	// CHAR 01
	std::ostringstream s2;
	s2 << "Motivation";
	modelStack.PushMatrix();
	modelStack.Translate((r_quad01Pos.x + m_thirtytwothWorldWidth), (r_quad01Pos.y + m_twelfthWorldHeight + m_twentyfourthWorldHeight), 0.65f);
	modelStack.Scale(4.f, 4.f, 1);
	RenderText(meshList[GEO_GAMEFONT], s2.str(), Color(0, 0, 1));
	modelStack.PopMatrix();


	s2.clear();
	s2.str("");
	s2 << "%" << StatManager::GetInstance()->GetChar01().m_motivation;

	modelStack.PushMatrix();
	modelStack.Translate((r_quad01Pos.x + 3 * m_thirtytwothWorldWidth), (r_quad01Pos.y + m_twentyfourthWorldHeight), 0.65f);
	modelStack.Scale(8.5f, 8.5f, 1);
	RenderText(meshList[GEO_GAMEFONT], s2.str(), Color(0, 0, 1));
	modelStack.PopMatrix();

	s2.clear();
	s2.str("");
	s2 << "Frustration";
	modelStack.PushMatrix();
	modelStack.Translate((r_quad01Pos.x + m_thirtytwothWorldWidth), (r_quad01Pos.y - m_twentyfourthWorldHeight), 0.65f);
	modelStack.Scale(4.f, 4.f, 1);
	RenderText(meshList[GEO_GAMEFONT], s2.str(), Color(0, 0, 1));
	modelStack.PopMatrix();

	s2.clear();
	s2.str("");
	s2 << "%" << StatManager::GetInstance()->GetChar01().m_frustration;

	modelStack.PushMatrix();
	modelStack.Translate((r_quad01Pos.x + 3 * m_thirtytwothWorldWidth), (r_quad01Pos.y - m_twelfthWorldHeight - m_twentyfourthWorldHeight), 0.65f);
	modelStack.Scale(8.5f, 8.5f, 1);
	RenderText(meshList[GEO_GAMEFONT], s2.str(), Color(0, 0, 1));
	modelStack.PopMatrix();

	// CHAR 02
	s2.clear();
	s2.str("");
	s2 << "Motivation";

	modelStack.PushMatrix();
	modelStack.Translate((r_quad02Pos.x + m_thirtytwothWorldWidth), (r_quad02Pos.y + m_twelfthWorldHeight + m_twentyfourthWorldHeight), 0.65f);
	modelStack.Scale(4.f, 4.f, 1);
	RenderText(meshList[GEO_GAMEFONT], s2.str(), Color(0, 0, 1));
	modelStack.PopMatrix();

	s2.clear();
	s2.str("");
	s2 << "%" << StatManager::GetInstance()->GetChar02().m_motivation;

	modelStack.PushMatrix();
	modelStack.Translate((r_quad02Pos.x + 3 * m_thirtytwothWorldWidth), (r_quad02Pos.y + m_twentyfourthWorldHeight), 0.65f);
	modelStack.Scale(8.5f, 8.5f, 1);
	RenderText(meshList[GEO_GAMEFONT], s2.str(), Color(0, 0, 1));
	modelStack.PopMatrix();

	s2.clear();
	s2.str("");
	s2 << "Frustration";
	modelStack.PushMatrix();
	modelStack.Translate((r_quad02Pos.x + m_thirtytwothWorldWidth), (r_quad02Pos.y - m_twentyfourthWorldHeight), 0.65f);
	modelStack.Scale(4.f, 4.f, 1);
	RenderText(meshList[GEO_GAMEFONT], s2.str(), Color(0, 0, 1));
	modelStack.PopMatrix();

	s2.clear();
	s2.str("");
	s2 << "%" << StatManager::GetInstance()->GetChar02().m_frustration;

	modelStack.PushMatrix();
	modelStack.Translate((r_quad02Pos.x + 3 * m_thirtytwothWorldWidth), (r_quad02Pos.y - m_twelfthWorldHeight - m_twentyfourthWorldHeight), 0.65f);
	modelStack.Scale(8.5f, 8.5f, 1);
	RenderText(meshList[GEO_GAMEFONT], s2.str(), Color(0, 0, 1));
	modelStack.PopMatrix();

	// CHAR 03
	s2.clear();
	s2.str("");
	s2 << "Motivation";

	modelStack.PushMatrix();
	modelStack.Translate((r_quad03Pos.x + m_thirtytwothWorldWidth), (r_quad03Pos.y + m_twelfthWorldHeight + m_twentyfourthWorldHeight), 0.65f);
	modelStack.Scale(4.f, 4.f, 1);
	RenderText(meshList[GEO_GAMEFONT], s2.str(), Color(0, 0, 1));
	modelStack.PopMatrix();

	s2.clear();
	s2.str("");
	s2 << "%" << StatManager::GetInstance()->GetChar03().m_motivation;

	modelStack.PushMatrix();
	modelStack.Translate((r_quad03Pos.x + 3 * m_thirtytwothWorldWidth), (r_quad03Pos.y + m_twentyfourthWorldHeight), 0.65f);
	modelStack.Scale(8.5f, 8.5f, 1);
	RenderText(meshList[GEO_GAMEFONT], s2.str(), Color(0, 0, 1));
	modelStack.PopMatrix();

	s2.clear();
	s2.str("");
	s2 << "Frustration";
	modelStack.PushMatrix();
	modelStack.Translate((r_quad03Pos.x + m_thirtytwothWorldWidth), (r_quad03Pos.y - m_twentyfourthWorldHeight), 0.65f);
	modelStack.Scale(4.f, 4.f, 1);
	RenderText(meshList[GEO_GAMEFONT], s2.str(), Color(0, 0, 1));
	modelStack.PopMatrix();

	s2.clear();
	s2.str("");
	s2 << "%" << StatManager::GetInstance()->GetChar03().m_frustration;

	modelStack.PushMatrix();
	modelStack.Translate((r_quad03Pos.x + 3 * m_thirtytwothWorldWidth), (r_quad03Pos.y - m_twelfthWorldHeight - m_twentyfourthWorldHeight), 0.65f);
	modelStack.Scale(8.5f, 8.5f, 1);
	RenderText(meshList[GEO_GAMEFONT], s2.str(), Color(0, 0, 1));
	modelStack.PopMatrix();

	// CHAR 04
	s2.clear();
	s2.str("");
	s2 << "Motivation";

	modelStack.PushMatrix();
	modelStack.Translate((r_quad04Pos.x + m_thirtytwothWorldWidth), (r_quad04Pos.y + m_twelfthWorldHeight + m_twentyfourthWorldHeight), 0.65f);
	modelStack.Scale(4.f, 4.f, 1);
	RenderText(meshList[GEO_GAMEFONT], s2.str(), Color(0, 0, 1));
	modelStack.PopMatrix();

	s2.clear();
	s2.str("");
	s2 << "%" << StatManager::GetInstance()->GetChar04().m_motivation;

	modelStack.PushMatrix();
	modelStack.Translate((r_quad04Pos.x + 3 * m_thirtytwothWorldWidth), (r_quad04Pos.y + m_twentyfourthWorldHeight), 0.65f);
	modelStack.Scale(8.5f, 8.5f, 1);
	RenderText(meshList[GEO_GAMEFONT], s2.str(), Color(0, 0, 1));
	modelStack.PopMatrix();

	s2.clear();
	s2.str("");
	s2 << "Frustration";
	modelStack.PushMatrix();
	modelStack.Translate((r_quad04Pos.x + m_thirtytwothWorldWidth), (r_quad04Pos.y - m_twentyfourthWorldHeight), 0.65f);
	modelStack.Scale(4.f, 4.f, 1);
	RenderText(meshList[GEO_GAMEFONT], s2.str(), Color(0, 0, 1));
	modelStack.PopMatrix();

	s2.clear();
	s2.str("");
	s2 << "%" << StatManager::GetInstance()->GetChar04().m_frustration;

	modelStack.PushMatrix();
	modelStack.Translate((r_quad04Pos.x + 3 * m_thirtytwothWorldWidth), (r_quad04Pos.y - m_twelfthWorldHeight - m_twentyfourthWorldHeight), 0.65f);
	modelStack.Scale(8.5f, 8.5f, 1);
	RenderText(meshList[GEO_GAMEFONT], s2.str(), Color(0, 0, 1));
	modelStack.PopMatrix();
}
