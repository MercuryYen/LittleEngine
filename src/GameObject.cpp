#include "GameObject.h"

glm::mat4 GameObject::getMatrix()
{
	if (selfEdited) {
		matrix = glm::mat4(1);

		matrix = glm::translate(matrix, position);
		matrix = glm::rotate(matrix, glm::radians(rotation.z), glm::vec3(0, 0, 1));
		matrix = glm::rotate(matrix, glm::radians(rotation.y), glm::vec3(0, 1, 0));
		matrix = glm::rotate(matrix, glm::radians(rotation.x), glm::vec3(1, 0, 0));
		matrix = glm::scale(matrix, scale);

		selfEdited = false;
	}
	return matrix;
}

glm::mat4 GameObject::getLocalToGlobalMatrix()
{
	updateMatrix();
	return localToGlobalMatrix;
}

void GameObject::updateMatrix()
{
	//find all GameObject from self to root
	vector<GameObject*> parent_path;
	parent_path.push_back(parent);
	while (parent_path.back() != NULL) {
		parent_path.push_back(parent_path.back()->parent);
	}
	parent_path.pop_back();

	//find topest edited GameObject
	bool haveEdited = false;
	int editedIndex;
	for (int i = parent_path.size() - 1; i >= 0; --i) {
		if (parent_path[i]->edited) {
			haveEdited = true;
			editedIndex = i;
			break;
		}
	}
	
	//update matrix from topest edited GameObject to self
	if (haveEdited) {
		for (int i = editedIndex; i >= 0; --i) {
			parent_path[i]->updateMatrixFromParent();
		}
		updateMatrixFromParent();
	}
	else {
		if (edited) {
			updateMatrixFromParent();
		}
	}
}

GameObject::GameObject(GameObject* _parent)
{
	parent = _parent;
	setPosition(glm::vec3(0, 0, 0));
	setRotation(glm::vec3(0, 0, 0));
	setScale(glm::vec3(1, 1, 1));

	if (parent != NULL) {
		parent->children.push_back(this);
	}
	/*
	{
		Component* component = new Component(this);
		components.push_back(component);
	}
	{
		GameObject* child = new GameObject(this);
		children.push_back(child);
	}
	*/
}

GameObject::~GameObject()
{
	for (int i = children.size() - 1; i >= 0; --i) {
		delete children[i];
	}
	for (int i = components.size() - 1; i >= 0; --i) {
		delete components[i];
	}
}

void GameObject::awake()
{
	//self awake function

	updateMatrixFromParent();
	for (int i = 0; i< children.size(); ++i) {
		children[i]->awake();
	}

	updateMatrixFromParent();
}

void GameObject::start()
{
	//update matrix
	updateMatrixFromParent();

	for (int i = 0; i < components.size(); ++i) {
		components[i]->start();
	}

	//just for safe
	updateMatrixFromParent();

	for (int i = 0; i < children.size(); ++i) {
		children[i]->start();
	}
}

void GameObject::update()
{
	//update matrix
	updateMatrixFromParent();

	for (int i = 0; i < components.size(); ++i) {
		if(components[i]->enable)
			components[i]->update();
	}

	//component might edit transform
	updateMatrixFromParent();

	for (int i = 0; i < children.size(); ++i) {
		children[i]->update();
	}
}

void GameObject::draw(Camera* cam)
{
	//update matrix, localToGlobalMatrix
	updateMatrixFromParent();

	for (int i = 0; i < componentsByType["render"].size(); ++i) {
		if(componentsByType["render"][i]->enable)
			((RenderComponent*)componentsByType["render"][i])->render(cam);
	}
	
	for (int i = 0; i < children.size(); ++i) {
		children[i]->draw(cam);
	}
}

inline void GameObject::updateMatrixFromParent()
{
	if (parent)
		localToGlobalMatrix = parent->localToGlobalMatrix * getMatrix();
	else
		if(edited)
			localToGlobalMatrix = getMatrix();
	edited = false;
}
