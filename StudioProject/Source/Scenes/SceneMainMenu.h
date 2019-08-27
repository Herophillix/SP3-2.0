#ifndef SCENE_MAIN_MENU_H
#define SCENE_MAIN_MENU_H
#include "SceneBase.h"
#include "GameObject.h"
#include "../Application.h"
#include "../SoundEngine.h"

class MainMenuObject : public GameObject
{
public:
	enum MAINMENU_OBJECTTYPE
	{
		GO_NONE,
		GO_NEWGAME,
		GO_INSTRUCTIONS,
		GO_CREDITS,
		GO_EXIT,
		GO_TOTAL,
	};
	MainMenuObject(MAINMENU_OBJECTTYPE = GO_NONE);
	~MainMenuObject();

	void setHighlighted(bool);
	void setxOffset(float, bool additive = false);
	void setFontColor(Color);
	void setText(string);

	bool getHighlighted();
	float getxOffset();
	Color getFontColor();
	string getText();

private:
	bool highlighted;
	float xOffset;
	Color fontColor;
	string Text;

};


class MainMenu : public SceneBase
{
public:
	MainMenu();
	~MainMenu();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();

	void RenderGO(MainMenuObject* go);
	void RenderOptions();
	void UpdateMousePos();
	void ButtonCollision(MainMenuObject::MAINMENU_OBJECTTYPE type);


private:

	float m_worldWidth;
	float m_worldHeight;
	CSoundEngine soundSystem;
	float m_halfWorldWidth;
	float m_halfWorldHeight;

	float m_thirdWorldHeight;
	float m_sixthWorldHeight;
	

	Vector3 m_mousePos;

	MainMenuObject* m_NewGameButton;
	MainMenuObject* m_InstructionsButton;
	MainMenuObject* m_CreditsButton;
	MainMenuObject* m_ExitButton;

	vector<MainMenuObject*> menuObjList;
	
};
#endif // !SCENE_MAIN_MENU_H
