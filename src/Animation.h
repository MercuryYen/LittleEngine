#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/quaternion.hpp>
#include <vector>
#include <string>
#include <map>
using namespace std;

enum class AnimationType {
	POSITION, ROTATION, SCALE
};

struct AnimationFrame {
	AnimationFrame(float _time, glm::vec3 _value) {
		time = _time;
		value = _value;
	}
	float time;
	glm::vec3 value;
};

struct Animation;
struct AnimationMotion {
	AnimationMotion(AnimationType _type) {
		type = _type;
	}

	Animation* animation = nullptr;

	//hierarchical index to find target GameObject
	//gameObject->children[2]->children[1]->children[3]....
	vector<unsigned int> indeces;

	//Storing this motion will change which property
	//Used by Animator to make a copy of original tranform
	AnimationType type;

	//Storing all frames
	vector<AnimationFrame> frames;

	//A function
	glm::vec3 getValue(float time, bool loop);
};

//An animation that store a set of motion
struct Animation {
	Animation(float _time) {
		time = _time;
	}

	float time; //whole time of animation
	
	void addMotion(string name, AnimationMotion* AM);

	//all motions
	//a mapping from name to AnimationMotion
	//motions["left arm"].getValue(time, loop);
	//to travel all motions, use map<>::iterator
	map<string, AnimationMotion*> motions;
};

struct AnimationManager {
	map<string, Animation*> animations;
};