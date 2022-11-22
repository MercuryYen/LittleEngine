#include "TestScene.h"

void TestScene::button_hover(Widget* t)
{
	//hover event is changing color

	//mouse in button
	if (((ImageBox*)t)->mouseIntersection)
		((ImageBox*)t)->hoverColor = glm::vec4(0.3, 0.3, 0.3, 1);
	//mouse isn't in button
	else
		((ImageBox*)t)->hoverColor = glm::vec4(0, 0, 0, 1);
}
void TestScene::start_button_click(Widget* t)
{
	//click event is changing rotating direction
	//TestScene::instance->rotateRight = !TestScene::instance->rotateRight;
	Animator* a = (Animator*)(TestScene::instance->testObject->componentsByType["animator"][0]);
	if (a->animation == NULL) {
		a->switchAnimation(TestScene::instance->testAnimation->animations["rotate"]);
	}
	else if (a->animation == TestScene::instance->testAnimation->animations["rotate"]) {
		a->switchAnimation(TestScene::instance->testAnimation->animations["double rotate"]);
	}
	else {
		a->clearAnimation();
	}
}

void TestScene::init() 
{
	//setup reference for callback function
	TestScene::instance = this;

	//view camera
	if (!viewCamera) {
		//camera's initialization
		viewCamera = new Camera;

		//camera's transform
		viewCamera->Front = glm::vec3(0, 0, -1);
		viewCamera->Position = glm::vec3(0, 0, 100);

		//aspect ratio
		viewCamera->width = GameWindow::SRC_WIDTH;
		viewCamera->height = GameWindow::SRC_HEIGHT;
	}



	//animation
	if (!testAnimation) {
		testAnimation = new TestAnimationManager;
	}

	//main object
	if (!testObject) {
		//object's initialization
		testObject = new GameObject(NULL);
		
		//shader for rendering model
		LightShader* lightShader = new LightShader;

		lightShader->setDirectionalLightDirection ( glm::normalize(glm::vec3(1, 0, 0)));
		lightShader->setDiffuseColor(glm::vec3(0.1, 0.1, 0.1));
		lightShader->setAmbientColor(glm::vec3(0.3, 0.3, 0.3));

		//create a child GameObject with model
		GameObject* laputaMan = new GameObject(testObject);
		RenderComponent* laputaManRC = new RenderComponent(laputaMan, lightShader, "model/laputarobot.obj");
		laputaMan->setScale(  glm::vec3(0.015, 0.015, 0.015));
		laputaMan->setPosition(glm::vec3(40,0,0)); 
		laputaMan->setRotation(glm::vec3(-90,0,0));


		//object's transform
		testObject->setPosition(  glm::vec3(0, -20, -10));

		//Add animator component
		Animator* animator = new Animator(testObject);
		animator->setAnimation(testAnimation->animations["rotate"]);
		animator->loop = true;
		
		//object's awake function
		testObject->awake();
	}

	//skybox
	if (!skyboxShader) {
		//skybox's initialization
		skyboxShader = new SkyBoxShader;
		skyboxShader->skyboxInitialize();
	}

	//rotation button
	if (!button) {
		//button's initialization
		//use a 2D imagebox to display
		button = new ImageBox(0.75, -0.75, 0.25, 0.25, TextureFromFile("white.png", "Image"));

		//setup imagebox's properties
		button->color = glm::vec4(1, 1, 1, 1);
		button->hoverColor = glm::vec4(0, 0, 0, 1);
		//setup callback function
		button->hoverEvent = button_hover;
		button->clickEvent = start_button_click;
		//let imagebox can detect mouse
		button->canBeIntersection = true;

		//text on button
		//textbox's initialization
		TextBox* rotateText = new TextBox(-0.8, 0.6, 0.8, 1.5, L"回転");

		//setup textbox's properties
		rotateText->setFont("rycsminStencily.ttf");
		rotateText->setResolution(256);
		rotateText->refreshFont();
		rotateText->setColor(glm::vec4(1, 1, 1, 1));

		//add textbox into button
		button->addChild(rotateText);
	}

	//a mouse image
	if (!simulateMouse) {
		//mouse imagebox's initialization
		simulateMouse = new ImageBox(-1, 1, 0.09, 0.16, TextureFromFile("mouse.png", "Image"));
	}
}

void TestScene::update() 
{
	Animator::setDeltaTime(GameManager::manager->deltaTime);
	testObject->update();
	////rotate object according to clicking button
	//if(rotateRight)
	//	testObject->rotation.y += 0.3;
	//else
	//	testObject->rotation.y -= 0.3;

}
void TestScene::draw() 
{
	//setup screen
	glViewport(0, 0, GameWindow::SRC_WIDTH, GameWindow::SRC_HEIGHT);
	glClearColor(0, 0, .3f, 0);
	glClearStencil(0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	//allow transparent
	glEnable(GL_BLEND);

	//enable depth test for 3D render
	glEnable(GL_DEPTH_TEST);

	//draw skybox
	skyboxShader->draw(viewCamera->GetViewMatrix(), viewCamera->GetProjectionMatrix());

	//draw 3D object
	testObject->draw(viewCamera);

	//disable depth test for 2D object's render
	glDepthFunc(GL_ALWAYS);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//draw 2D object
	//button and mouse
	((Widget*)button)->draw();
	simulateMouse->draw(GameWindow::toXScreenSpace(GameManager::manager->cursorSimuX), GameWindow::toYScreenSpace(GameManager::manager->cursorSimuY), 2, 2);
	
	//recover depth test
	glDepthFunc(GL_LESS);
}
void TestScene::processKeyboard()
{
	//handle if mouse is on button
	button->processMouseIntersection(GameWindow::toXScreenSpace(GameManager::manager->cursorSimuX), GameWindow::toYScreenSpace(GameManager::manager->cursorSimuY));

	//handle mouse's button
	if (GetKeyState(VK_LBUTTON) & 0x8000) { //Left Click
		if (!lastLeftClick) {
			button->processClick();
		}
		lastLeftClick = GetKeyState(VK_LBUTTON) & 0x8000;
	}
	else {
		lastLeftClick = 0;
	}
}
TestScene* TestScene::instance = nullptr;