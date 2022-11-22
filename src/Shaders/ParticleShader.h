#pragma once
#include "Shader.h"
#include <iostream>
#include <string>


class ParticleShader :public Shader
{
public:
	ParticleShader() : Shader("ParticleShader","GLSL/particle.vert", "GLSL/particle.frag") {

	}
	void setIndividualMatrix(glm::mat4 individualMatrix) {
		this->setMat4(uniformIndividualMatrix, individualMatrix);
	}
	void setModelMatrix(glm::mat4 modelMatrix) {
		this->setMat4(uniformModelMatrix, modelMatrix);
	}
	void setViewMatrix(glm::mat4 viewMatrix) {
		this->setMat4(uniformViewMatrix, viewMatrix);
	}
	void setProjectionMatrix(glm::mat4 projectionMatrix) {
		this->setMat4(uniformProjectionMatrix, projectionMatrix);
	}
	void setTexture(GLuint texture) {
		this->setInt(uniformImageTexture, texture);
	}
	void setColor(glm::vec4 color) {
		this->setVec4(uniformColor, color);
	}
private:
	//GLchar* vertPath = "../AkukinKensetsu/src/GLSL/model.vert";
	//GLchar* fragPath = "../AkukinKensetsu/src/GLSL/model.frag";

	std::string uniformIndividualMatrix = "individualMatrix";
	std::string uniformModelMatrix = "modelMatrix";
	std::string uniformViewMatrix = "viewMatrix";
	std::string uniformProjectionMatrix = "projectionMatrix";
	std::string uniformImageTexture = "texture_image";
	std::string uniformColor = "color";
};