#pragma once

class Component;
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include <string>
#include <map>
#include "DLC/Camera.h"
using namespace std;

class GameObject {
public:
	//get and set function for transform....
	//to know if the properties is edited
	void setPosition(const glm::vec3 _position) { position = _position; edited = selfEdited = true; }
	void translate(float x, float y, float z) { setPosition(position + glm::vec3(x, y, z)); }
	void translate(glm::vec3 _translation) { setPosition(position + _translation); }
	glm::vec3 getPosition() { return position; }

	void setRotation(const glm::vec3 _rotation) { rotation = _rotation; edited = selfEdited = true; }
	void rotate(float x, float y, float z) { setRotation(rotation + glm::vec3(x, y, z)); }
	void rotate(glm::vec3 _rotation) { setRotation(rotation + _rotation); }
	glm::vec3 getRotation() { return rotation; }

	void setScale(const glm::vec3 _scale) { scale = _scale; edited = selfEdited = true; }
	glm::vec3 getScale() { return scale; }

	//matrix function
	glm::mat4 getMatrix();
	glm::mat4 getLocalToGlobalMatrix();
	void updateMatrix();

	//GameObject Hierarchy
	GameObject* parent = NULL;
	vector<GameObject*> children;

	//Components
	vector<Component*> components;
	map<string, vector<Component*>> componentsByType;

	//setup children, components
	GameObject(GameObject* _parent);

	//delete children, components
	~GameObject();

	//execute before creating all objects
	//setup self properties
	virtual void awake();

	//execute after creating all objects
	//setup properties that relative to other object
	virtual void start();

	//execute per frame
	//update transform and control system
	virtual void update();

	//execute per frame after update
	//render object
	virtual void draw(Camera* cam);
private:
	//transform
	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;

	glm::mat4 matrix;
	glm::mat4 localToGlobalMatrix;

	//set self's localToGlobalMatrix
	//only if parent isn't edited
	inline void updateMatrixFromParent();
	bool edited = true;
	bool selfEdited = true;
};

#include "Component.h"
#include "RenderComponent.h"