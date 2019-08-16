
#ifndef APPLICATION_H
#define APPLICATION_H

#include "timer.h"

class Application
{
public:
	static Application& GetInstance()
	{
		static Application app;
		return app;
	}
	void Init();
	void Run();
	void Exit();
	static bool IsKeyPressed(unsigned short key);
	static bool IsMousePressed(unsigned short key);
	static void GetCursorPos(double *xpos, double *ypos);
	static void setScene(int i);
	static int GetWindowWidth();
	static int GetWindowHeight(); 

	enum SceneType
	{
		SCENEMAIN,
		SCENEMAZE,
		SCENEMOLE,
		SCENETANK,
		SCENEFROG,
		TOTALSCENES,
	};

private:
	Application();
	~Application();
	static int currentScene;
	//Declare a window object
	StopWatch m_timer;
};

#endif