#include "Animator.h"

void Animator::update()
{
	if (!enable) return;
	if (animation) {
		time += deltaTime;
		while (loop && time > animation->time) {
			time -= animation->time;
		}
		for (map<string, AnimationMotion*>::iterator i = animation->motions.begin(); i != animation->motions.end(); ++i) {
			if (mapping[i->first] != NULL) {
				switch (i->second->type) {
				case AnimationType::POSITION:
					mapping[i->first]->setPosition(i->second->getValue(time, loop));
					break;
				case AnimationType::SCALE:
					mapping[i->first]->setScale(  i->second->getValue(time, loop));
					break;
				case AnimationType::ROTATION:
					mapping[i->first]->setRotation(  i->second->getValue(time, loop));
					break;
				}
			}
		}
	}
}

void Animator::setDeltaTime(float _deltaTime)
{
	deltaTime = _deltaTime;
}

void Animator::setAnimation(Animation* newAnimation)
{
	animation = newAnimation;
	for (map<string, AnimationMotion*>::iterator i = animation->motions.begin(); i != animation->motions.end(); ++i) {
		//Find target GameObject
		GameObject* target = gameObject;
		for (int j = 0; j < i->second->indeces.size(); ++j) {
			if (target->children.size() > i->second->indeces[j]) {
				target = target->children[i->second->indeces[j]];
			}
			else {
				target = NULL;
				break;
			}
		}

		//setup mapping of name and GameObject
		if(mapping.find(i->first) == mapping.end())
			mapping[i->first] = target;

		//setup GameObject's original value
		if (target) {
			switch (i->second->type) {
			case AnimationType::POSITION:
				originalValue[target][i->second->type] = target->getPosition();
				break;
			case AnimationType::SCALE:
				originalValue[target][i->second->type] = target->getScale();
				break;
			case AnimationType::ROTATION:
				originalValue[target][i->second->type] = target->getRotation();
				break;
			}
		}
	}
}

void Animator::clearAnimation()
{
	animation = NULL;

	//set all affected GameObject to original transform
	for (map<GameObject*, map<AnimationType, glm::vec3>>::iterator i = originalValue.begin(); i != originalValue.end(); ++i) {
		for (map<AnimationType, glm::vec3>::iterator j = i->second.begin(); j != i->second.end(); ++j) {
			switch (j->first) {
			case AnimationType::POSITION:
				i->first->setPosition(  j->second);
				break;
			case AnimationType::SCALE:
				i->first->setScale(  j->second);
				break;
			case AnimationType::ROTATION:
				i->first->setRotation(  j->second);
				break;
			}
		}
	}
	originalValue.clear();
}

void Animator::switchAnimation(Animation* newAnimation)
{
	clearAnimation();
	setAnimation(newAnimation);
}

float Animator::deltaTime = 0;