#include "Results.h"

Results* Results::r_instance = nullptr;

Results * Results::getInstance()
{
	if (r_instance == nullptr)
	{
		r_instance = new Results();
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
	meshList[GEO_C01_RESULT_QUAD]->textureID = LoadTGA("Image//resultTest.tga");
	meshList[GEO_C02_RESULT_QUAD] = MeshBuilder::GenerateQuad("c01result", Color(1, 1, 1), 1.f);
	meshList[GEO_C03_RESULT_QUAD] = MeshBuilder::GenerateQuad("c01result", Color(1, 1, 1), 1.f);
	meshList[GEO_C04_RESULT_QUAD] = MeshBuilder::GenerateQuad("c01result", Color(1, 1, 1), 1.f);

	meshList[GEO_RESULT_PLUS] = MeshBuilder::GenerateQuad("plusButton", Color(0, 0, 1), 1.f);


	meshList[GEO_GAMEFONT] = MeshBuilder::GenerateText("teko", 16, 16);
	meshList[GEO_GAMEFONT]->textureID = LoadTGA("Image//KidsZone.tga");

	// THE VARS
	m_worldHeight = 100.f;
	m_worldWidth = m_worldHeight * (float)Application::GetWindowWidth() / Application::GetWindowHeight();
	m_halfWorldHeight = m_worldHeight / 2;
	m_halfWorldWidth = m_worldWidth / 2;

	m_quarterWorldWidth = m_worldWidth / 4;
	m_eightWorldWidth = m_worldWidth / 8;

	m_sixthWorldHeight = m_worldHeight / 6;
	m_quarterWorldHeight = m_worldHeight / 4;

	r_quad01Pos.Set(m_quarterWorldWidth, m_sixthWorldHeight * 3, 0.5f);
	r_quad02Pos.Set(m_quarterWorldWidth * 3, m_sixthWorldHeight * 3, 0.5f);
	r_quad03Pos.Set(m_quarterWorldWidth, m_sixthWorldHeight, 0.5f);
	r_quad04Pos.Set(m_quarterWorldWidth * 3, m_sixthWorldHeight, 0.5f);


	// Objects
	c01Plus = new ResultObject(ResultObject::GO_NONE);
	c01Plus->objType = ResultObject::GO_PLUS;
	c01Plus->belong = (ResultObject::WHICH_CHARACTER)1;
	c01Plus->active = false;
	c01Plus->pos.Set(r_quad01Pos.x, r_quad01Pos.y , 0.65f);
	//c01Plus->pos.Set(30, 30, 0.5f);
	c01Plus->scale.Set(11.25f, 15, 1);


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

	m_sixthWorldHeight = m_worldHeight / 6;
	m_quarterWorldHeight = m_worldHeight / 4;

	r_quad01Pos.Set(m_quarterWorldWidth, m_sixthWorldHeight * 3, 0.5f);
	r_quad02Pos.Set(m_quarterWorldWidth * 3, m_sixthWorldHeight * 3, 0.5f);
	r_quad03Pos.Set(m_quarterWorldWidth, m_sixthWorldHeight, 0.5f);
	r_quad04Pos.Set(m_quarterWorldWidth * 3, m_sixthWorldHeight, 0.5f);
}

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
	RenderTextOnScreen(meshList[GEO_GAMEFONT], ss.str(), Color(1, 1, 1), 2, 30, 45);
	// get instance of player stats

	// Render Character Quad -> stats
	// C01 Quad
	modelStack.PushMatrix();
	modelStack.Translate(r_quad01Pos);
	modelStack.Scale(90, 30, 1);
	RenderMesh(meshList[GEO_C01_RESULT_QUAD], false);
	modelStack.PopMatrix();

	// C01 Stats
	RenderGO(c01Plus);


	// C02 Quad
	modelStack.PushMatrix();
	modelStack.Translate(r_quad02Pos);
	modelStack.Scale(90, 30, 1);
	RenderMesh(meshList[GEO_C02_RESULT_QUAD], false);
	modelStack.PopMatrix();

	// C01 Stats

	// C03 Quad
	modelStack.PushMatrix();
	modelStack.Translate(r_quad03Pos);
	modelStack.Scale(90, 30, 1);
	RenderMesh(meshList[GEO_C03_RESULT_QUAD], false);
	modelStack.PopMatrix();

	// C01 Stats

	// C04 Quad
	modelStack.PushMatrix();
	modelStack.Translate(r_quad04Pos);
	modelStack.Scale(90, 30, 1);
	RenderMesh(meshList[GEO_C04_RESULT_QUAD], false);
	modelStack.PopMatrix();

	// C04 Stats


	// Collision check for mouse position and quad for rObjects



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
	default:
		break;
	}
}
