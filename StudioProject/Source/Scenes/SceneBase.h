#ifndef SCENE_BASE_H
#define SCENE_BASE_H

#include "Scene.h"
#include "Mtx44.h"
#include "../Camera/Camera.h"
#include "../Rendering/Mesh.h"
#include "MatrixStack.h"
#include "../Light.h"
#include "GameObject.h"
#include "../Rendering/Particles.h"
#include <vector>
#include "../SpriteAnimation.h"
class SceneBase : public Scene
{
	enum UNIFORM_TYPE
	{
		U_MVP = 0,
		U_MODELVIEW,
		U_MODELVIEW_INVERSE_TRANSPOSE,
		U_MATERIAL_AMBIENT,
		U_MATERIAL_DIFFUSE,
		U_MATERIAL_SPECULAR,
		U_MATERIAL_SHININESS,
		U_LIGHTENABLED,
		U_NUMLIGHTS,
		U_LIGHT0_TYPE,
		U_LIGHT0_POSITION,
		U_LIGHT0_COLOR,
		U_LIGHT0_POWER,
		U_LIGHT0_KC,
		U_LIGHT0_KL,
		U_LIGHT0_KQ,
		U_LIGHT0_SPOTDIRECTION,
		U_LIGHT0_COSCUTOFF,
		U_LIGHT0_COSINNER,
		U_LIGHT0_EXPONENT,
		U_COLOR_TEXTURE_ENABLED,
		U_COLOR_TEXTURE,
		U_TEXT_ENABLED,
		U_TEXT_COLOR,
		U_TOTAL,
	};
public:
	enum GEOMETRY_TYPE
	{
		GEO_AXES,
		GEO_TEXT,
		// TYPICAL OBJECTS
		GEO_BALL,
		GEO_CUBE,
		GEO_WALL,
		GEO_PILLAR,
		GEO_QUAD,
		
		// SCENE MAZE
		GEO_LIGHT,

		// STUDIO PROJECT SCENE
		GEO_BACKGROUND,
		//Sheep BG
		GEO_SHEEPBG,
		GEO_SHEEP,
		GEO_SHEEPKING,
		GEO_EVILSHEEPKING,
		GEO_SHEEPFLIPPED,
		GEO_FIREBALL,
		GEO_LIVES,
		GEO_LIFEBAR,
		GEO_MANABAR,
		GEO_CROSSHAIR,
		GEO_MAGICCIRCLE,
		GEO_WARNING,
		GEO_LINUX,
		GEO_LIGHTNING,
		// GEOs for stats
		GEO_FRUSTRATION,
		GEO_CHARONEFRUST,
		GEO_CHARONEMOTIVE,
		GEO_CHARONEREST,
		GEO_CHARONEWD,
		GEO_CHARTWOFRUST,
		GEO_CHARTWOMOTIVE,
		GEO_CHARTWOREST,
		GEO_CHARTWOWD,
		GEO_CHARTHREEFRUST,
		GEO_CHARTHREEMOTIVE,
		GEO_CHARTHREEREST,
		GEO_CHARTHREEWD,
		GEO_CHARFOURFRUST,
		GEO_CHARFOURMOTIVE,
		GEO_CHARFOURREST,
		GEO_CHARFOURWD,
		GEO_MOTIVATION,
		GEO_PARTICLE_TEST,
		GEO_SPRITE_ANIMATION,
		GEO_SPRITE_TEST2,
		GEO_FROG_JUMP,
		GEO_WALKRIGHT,
		GEO_WALKLEFT,
		GEO_ARROW, 
		// SCENE FROG
		GEO_FROG,
		GEO_FROG_ROCK,
		GEO_FROG_HEARTS,
		GEO_FROG_MAP,
		GEO_FROG_PLATFORM,
		GEO_COIN,
		GEO_FROG_INSTRUCTIONS,
		GEO_FROG_BORDER,
		// SCENE MOLE
		// Props
		GEO_HAMMER,
		GEO_MOLE,
		GEO_BACKPANEL,
		GEO_MIDPANEL,
		GEO_FRONTPANEL,
		GEO_MOLERESULTS,
		GEO_MOLESTATS,
		GEO_MOLE_BRONZE,
		GEO_MOLE_SILVER,
		GEO_MOLE_GOLD,
		GEO_MOLE_BOMB,
		GEO_MOLE_FROST,


		// RESULT QUADS FOR THE RESULT SCREEN
		GEO_RESULTSCREEN_QUAD,
		GEO_C01_RESULT_QUAD,
		GEO_C02_RESULT_QUAD,
		GEO_C03_RESULT_QUAD,
		GEO_C04_RESULT_QUAD,
		GEO_RESULT_PLUS,
		GEO_RESULT_MINUS,
		GEO_RESULT_PLUS_HIGHLIGHT,
		GEO_RESULT_MINUS_HIGHLIGHT,
		GEO_RESULT_CONTINUE,
		GEO_RESULT_RESET,
		GEO_GAMEFONT,
		GEO_CURSOR,

		// SCENETANK
		GEO_TANK_HEAD_1,
		GEO_TANK_HEAD_2,
		GEO_TANK_HEAD_3,
		GEO_TANK_HEAD_4,
		GEO_BORDER,
		GEO_TANK_FORMATION_1,
		GEO_TANK_FORMATION_2,
		GEO_TANK_FORMATION_3,
		GEO_TANK_FORMATION_4,
		GEO_TANK_FORMATION_5,
		GEO_TANK_FORMATION_6,

		// Animations
		GEO_HAMMER_SPRITE,
		
		NUM_GEOMETRY,
	};
public:
	SceneBase();
	~SceneBase();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();

	void RenderText(Mesh* mesh, std::string text, Color color);
	void RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y);
	void RenderMesh(Mesh *mesh, bool enableLight);
	//void RenderGO(GameObject *go);
	//Particles* getParticle();
	//void UpdateParticles(double dt);
	//void RenderParticles(Particles *particle);
//	void RenderAnimation();

	//GameObject* FetchGO();
protected:
	unsigned m_vertexArrayID;
	Mesh* meshList[NUM_GEOMETRY];
	unsigned m_programID;
	unsigned m_parameters[U_TOTAL];

	Camera camera;

	MS modelStack;
	MS viewStack;
	MS projectionStack;

	Light lights[1];

	bool bLightEnabled;

	float fps;
};

#endif