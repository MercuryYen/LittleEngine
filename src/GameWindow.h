#pragma once


#pragma warning(push)
#pragma warning(disable:4312)
#pragma warning(disable:4311)
#include <Fl/Fl_Gl_Window.h>
#include "GameManager.h"
#include "glm/glm.hpp"
#include <iostream>
#include <Fl/fl.h>
#include <glad/glad.h>
#include <GL/glu.h>
#include <ctime>
#include <vector>
using namespace std;

#pragma warning(pop)

class GameWindow;
class GameManager;

class GameWindow :public Fl_Gl_Window {
	public:
		static void update(GameWindow*);
		// note that we keep the "standard widget" constructor arguments
		GameWindow(const int x = 500, const int y = 200	);

		GameManager* gm;
		
		// overrides of important window things
		virtual int handle(int);
		virtual void draw();

		static float toXScreenSpace(float position);

		static float toYScreenSpace(float position);
		

		float deltaTime = 0;

		static int SRC_WIDTH;
		static int SRC_HEIGHT;
	private:
		int fps = 60;

		
		
};