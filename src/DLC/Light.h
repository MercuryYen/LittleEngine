#pragma once
#include <iostream>
#include "glm/glm.hpp"


class DirectLight {
public:
	void setDefault();
	
	glm::vec3 direction;

	float ambient;
	float diffuse;
	float specular;
};

class PointLight {
public:
	void setDefault();

	glm::vec3 position;

	float constant;
	float linear;
	float quadratic;

	float ambient;
	float diffuse;
	float specular;
};

class SpotLight {
public:
	void setDefault();

	glm::vec3 position;
	glm::vec3 direction;
	float cutOff;
	float outerCutOff;

	float constant;
	float linear;
	float quadratic;

	float ambient;
	float diffuse;
	float specular;
};