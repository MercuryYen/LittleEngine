#pragma once
#include "Shader.h"
#include <iostream>
#include <string>


class ImageShader :public Shader
{
public:
	ImageShader() : Shader("ImageShader","GLSL/image.vert", "GLSL/image.frag") {

	}
	void setPositionMatrix(glm::mat3 positionMatrix) {
		this->setMat3(uniformPositionMatrix, positionMatrix);
	}
	void setTexture(GLuint texture) {
		this->setInt(uniformImageTexture, texture);
	}
	void setColor(glm::vec4 color) {
		this->setVec4(uniformColor, color);
	}
	void setHoverColor(glm::vec4 hover) {
		this->setVec4(uniformHoverColor, hover);
	}
private:
	std::string uniformPositionMatrix = "positionMatrix";
	std::string uniformImageTexture = "image";
	std::string uniformColor = "color";
	std::string uniformHoverColor = "hoverColor";
};