#pragma once

#include "GameObject.h"
#include "Component.h"
#include "Animation.h"
#include <map>
#include <string>
using namespace std;

class Animator :public Component {
public:
	Animator(GameObject* _gameObject) :Component(_gameObject, "animator") {}

	static float deltaTime;

	//if animation, set all transform of GameObject in mapping
	//must call setDeltaTime() first
	static void setDeltaTime(float _deltaTime);
	void update();

	//loop animation?
	//time of animation
	bool loop = false;
	float time = 0;
	
	//now animation
	Animation* animation = nullptr;
	//store original value, set mapping
	void setAnimation(Animation*);
	//set original value, clear mapping
	void clearAnimation();
	//clear and set animation
	void switchAnimation(Animation*);

	//store original transform of GameObject that would be affected by animation
	map<GameObject*, map<AnimationType, glm::vec3>> originalValue;

	//mapping of name and GameObject
	map<string, GameObject*> mapping;

};