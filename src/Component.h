#pragma once

class GameObject;
#include <string>
using namespace std;

class Component {
public:
	GameObject* gameObject;
	string type = "template";

	//only affect update function
	bool enable = true;

	Component(GameObject* _gameObject, string _type);
	virtual void start();
	virtual void update();

};


#include "GameObject.h"