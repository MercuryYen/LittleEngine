#pragma once
#include "Shader.h"
#include <iostream>
#include <string>


class FontShader :public Shader
{
public:
	FontShader() : Shader("FontShader","GLSL/font.vert", "GLSL/font.frag") {

	}
	void setPositionMatrix(glm::mat3 positionMatrix) {
		this->setMat3(uniformPositionMatrix, positionMatrix);
	}
	void setFontTexture(GLuint fontTexture) {
		this->setInt(uniformLetterTexture, fontTexture);
	}
	void setColor(glm::vec4 _color) {
		this->setVec4(uniformLetterColor, _color);
	}
	void setSize(GLuint width, GLuint height) {
		this->setVec2(uniformSize, width, height);
	}
private:
	//GLchar* vertPath = "../AkukinKensetsu/src/GLSL/model.vert";
	//GLchar* fragPath = "../AkukinKensetsu/src/GLSL/model.frag";

	std::string uniformPositionMatrix = "positionMatrix";
	std::string uniformLetterTexture = "letter";
	std::string uniformLetterColor = "color";
	std::string uniformSize = "size";
};