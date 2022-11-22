#pragma once

#include "GameObject.h"
#include "Component.h"
#include "DLC/model.h"
#include "Shaders/Simple3DShader.h"
#include "DLC/Camera.h"

class RenderComponent :public Component{
public:

	RenderComponent(GameObject* _gameObject, Simple3DShader* _shader);
	RenderComponent(GameObject* _gameObject, Simple3DShader* _shader, const char* modelPath);
	//hmmm
	Model* model = nullptr;

	Simple3DShader* shader = nullptr;

	void render(Camera* cam);
};