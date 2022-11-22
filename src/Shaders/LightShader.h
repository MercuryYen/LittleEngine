#pragma once
#include "Simple3DShader.h"
#include <iostream>
#include <string>

class LightShader :public Simple3DShader
{
public:
	LightShader() : Simple3DShader("LightShader","GLSL/simple3D.vert", "GLSL/light.frag") {
		Shader::Use();
		glUseProgram(0);
	}
	virtual void Use() {
		Simple3DShader::Use();
		this->setVec3(uniformDLD, directionalLightDirection);
		this->setVec3(uniformDiffuseColor, diffuseColor);
		this->setVec3(uniformAmbientColor, ambientColor);
	}
	static void setDirectionalLightDirection(glm::vec3 _directionalLightDirection) {
		directionalLightDirection = _directionalLightDirection;
	}
	void setDiffuseColor(glm::vec3 _diffuseColor) {
		diffuseColor = _diffuseColor;
	}
	void setAmbientColor(glm::vec3 _ambientColor) {
		ambientColor = _ambientColor;
	}
private:
	std::string uniformDLD = "DirectionalLightDirection";
	std::string uniformDiffuseColor = "diffuseColor";
	std::string uniformAmbientColor = "ambientColor";
	static glm::vec3 directionalLightDirection;
	glm::vec3 diffuseColor;
	glm::vec3 ambientColor;
};