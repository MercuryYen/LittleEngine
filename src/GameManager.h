#pragma once
#include <iostream>
//using namespace std;

class GameWindow;
class GameManager;
class TestScene;

#include <Fl/fl.h>
#include "GameWindow.h"
#include "DLC/Camera.h"
#include "Shaders/Shader.h"
#include "Shaders/ModelShader.h"
#include "Shaders/FontShader.h"
#include "glm/glm.hpp"
#include <glm/gtx/transform.hpp>
#include "DLC/Model.h"
#include "TextBox.h"
#include "ImageBox.h"
#include <string>
#include "DLC/Light.h"
#include <ctime>

#include "testScene.h"


enum class GameProcess {
	INTRO,
	DUMMY
};

class GameManager {
public:
	GameManager();

	static GameWindow* window;
	static GameManager* manager;

	//control game's process
	GameProcess gp = GameProcess::INTRO;

	//Scenes
	TestScene* testScene = nullptr;

	int cursorSimuX = 0;
	int cursorSimuY = 0;
	int cursorMiddleX = 0; // cursor screen middle position in window position
	int cursorMiddleY = 0; // cursor screen middle position in window position
	int cursorDeltaX = 0;
	int cursorDeltaY = 0;

	float deltaTime = 0;

	void processCursorMove();

	void draw();
private:
	unsigned long long int lastTime = 0;
	GameProcess gpPre = GameProcess::DUMMY;

};

