#pragma once

class GameManager;
class TestScene;
#include "GameManager.h"
#include "Scene.h"
#include "GameObject.h"
#include "DLC/Camera.h"
#include "Shaders/LightShader.h"
#include "ImageBox.h"
#include "Textbox.h"
#include "testAnimation.h"
#include "Animator.h"


class TestScene :public Scene {
public:

	//reference for callback function
	static TestScene* instance;

	//3D camera
	Camera* viewCamera = nullptr;

	//3D object
	GameObject* testObject = nullptr;
	TestAnimationManager* testAnimation = nullptr;


	//2D UI / GUI
	ImageBox* button = nullptr;
	ImageBox* simulateMouse = nullptr;

	//variable to control 3D object
	bool rotateRight = true;

	//variable to handle mouse event
	int lastLeftClick = 0;

	//functions of a scene
	void init();	//when creating scene
	void update();	//execute per frame
	void draw();	//execute after update
	void processKeyboard();	//handle mouse and keyboard

	//global CallBack function for GUI
	static void button_hover(Widget* t);
	static void start_button_click(Widget* t);
};