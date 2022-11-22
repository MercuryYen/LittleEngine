#pragma once
#include <Fl/fl.h>
#include "glm/glm.hpp"
#include <glm/gtx/transform.hpp>
#include "Shaders/ParticleShader.h"
#include <ft2build.h>
#include <algorithm>
#include <functional>


#include FT_FREETYPE_H
using namespace std;

struct StandardParticle {
	float time;
	glm::vec3 position;
	glm::vec3 velocity;

	static glm::vec3 camPos;
	static bool comp(const StandardParticle& a, const StandardParticle& b);
};

class ParticleSystem {
public:
	ParticleSystem(int _maxAmount, float _size, float _interval, float _liveTime, glm::vec3 _pos, glm::vec3 _dir, float rnd_r, bool _loop);

	virtual void reset();
	virtual void addParticle(int amount);
	virtual void updateParticle(int index, float deltaTime);
	virtual void deleteParticle(int index);
	void sortParticle(glm::vec3 camPos);
	void update(float deltaTime);
	virtual void draw(ParticleShader&);

	//particle center
	glm::vec3 position;

	//particle direction
	glm::vec3 direction;

	//particle color
	glm::vec4 color;
	float positionRandomRadius;

	//loop?
	bool loop;

	//particle size
	float size;

	//particle generating speed: interval/s
	float interval;

	//particle's live time
	float liveTime;

	int maxAmount;
	StandardParticle* particles;

	

	GLuint quadVAO = 0;
	GLuint timeVBO = 0;
	GLuint positionVBO = 0;
	GLuint velocityVBO = 0;

	unsigned int particleAmount = 0;
	float sumOfDeltaTime = 0;

};