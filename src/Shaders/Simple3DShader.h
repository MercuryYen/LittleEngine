#pragma once
#include "Shader.h"
#include <iostream>
#include <string>

class Simple3DShader :public Shader
{
public:
	Simple3DShader() : Shader("Simple3DShader","GLSL/simple3D.vert", "GLSL/simple3D.frag") {
		Shader::Use();
		glUseProgram(0);
	}
	Simple3DShader(const string _ShaderName, const GLchar* vert, const GLchar* frag, const GLchar* tesc = nullptr, const GLchar* tese = nullptr, const GLchar* geom = nullptr) : Shader(_ShaderName,vert,frag,tesc,tese,geom) {
		Shader::Use();
		glUseProgram(0);
	}
	virtual void Use() {
		Shader::Use();
		this->setMat4(uniformViewMatrix, viewMatrix);
		this->setMat4(uniformProjectionMatrix, projectionMatrix);
		this->setMat4(uniformModelMatrix, modelMatrix);
	}
	void setViewMatrix(glm::mat4 _viewMatrix) {
		viewMatrix = _viewMatrix;
	}
	void setProjectionMatrix(glm::mat4 _projectionMatrix) {
		projectionMatrix = _projectionMatrix;
	}
	void setModelMatrix(glm::mat4 _modelMatrix) {
		modelMatrix = _modelMatrix;
	}
	glm::mat4 viewMatrix;
	glm::mat4 projectionMatrix;
	glm::mat4 modelMatrix;
private:
	std::string uniformViewMatrix = "viewMatrix";
	std::string uniformProjectionMatrix = "projectionMatrix";
	std::string uniformModelMatrix = "modelMatrix";
};