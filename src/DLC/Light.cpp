#include "Light.h"

void DirectLight::setDefault()
{
	direction = glm::vec3(-0.2, -1.0, 0.3);
	ambient = 0.05;
	diffuse = 0.4;
	specular = 0.5;
}

void PointLight::setDefault()
{
	position = glm::vec3(10, 5, 10);
	ambient = 0.05;
	diffuse = 0.8;
	specular = 1;
	constant = 1.0;
	linear = 0.09;
	quadratic = 0.032;
}

void SpotLight::setDefault()
{
	position = glm::vec3(-10, 5, -10);
	direction = glm::vec3(1, 0, 0);
	ambient = 0;
	diffuse = 1;
	specular = 1;
	constant = 1.0;
	linear = 0.09;
	quadratic = 0.032;
	cutOff = glm::cos(glm::radians(12.5));
	outerCutOff = glm::cos(glm::radians(15.0));
}
