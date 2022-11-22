#include "Component.h"

Component::Component(GameObject* _gameObject, string _type)
{
	type = _type;
	gameObject = _gameObject;
	gameObject->components.push_back(this);
	gameObject->componentsByType[type].push_back(this);
}

void Component::start()
{

}

void Component::update()
{
	if (!enable)return;
}
