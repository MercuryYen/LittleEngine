#pragma once
#include "Shader.h"
#include <iostream>
#include <string>

class ModelShader :public Shader
{
public:
	ModelShader() : Shader("ModelShader","GLSL/model.vert", "GLSL/model.frag") {
		Use();
		this->setInt(uniformPointLightNum, 0);
		this->setInt(uniformSpotLightNum, 0);
		this->setShininess(32);
		glUseProgram(0);
	}
	void setViewMatrix(glm::mat4 viewMatrix) {
		this->setMat4(uniformViewMatrix, viewMatrix);
	}
	void setProjectionMatrix(glm::mat4 projectionMatrix) {
		this->setMat4(uniformProjectionMatrix, projectionMatrix);
	}
	void setModelMatrix(glm::mat4 modelMatrix) {
		this->setMat4(uniformModelMatrix, modelMatrix);
	}


	void setViewPosition(glm::vec3 position) {
		this->setVec3(uniformViewPosition, position);
	}
	void setDirectLight(DirectLight dirLight) {
		setDirectLight_(uniformDirectLight, dirLight);
	}
	void setPointLight(PointLight* pointLights, int number) {
		this->setInt(uniformPointLightNum, number);
		setPointLight_(uniformPointLight, pointLights, number);
	}

	void setSpotLight(SpotLight* spotLights, int number) {
		this->setInt(uniformSpotLightNum, number);
		setSpotLight_(uniformSpotLight, spotLights, number);
	}

	void setShininess(float v) {
		this->setFloat(uniformShininess, v);
	}

private:
	//GLchar* vertPath = "../AkukinKensetsu/src/GLSL/model.vert";
	//GLchar* fragPath = "../AkukinKensetsu/src/GLSL/model.frag";

	std::string uniformViewMatrix = "viewMatrix";
	std::string uniformProjectionMatrix = "projectionMatrix";
	std::string uniformModelMatrix = "modelMatrix";
	std::string uniformViewPosition = "viewPos";
	std::string uniformDirectLight = "dirLight";
	std::string uniformPointLight = "pointLights";
	std::string uniformSpotLight = "spotLights";
	std::string uniformPointLightNum = "pointLightNum";
	std::string uniformSpotLightNum = "spotLightNum";
	std::string uniformShininess = "material.shininess";
};