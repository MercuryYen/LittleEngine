#pragma once
#include "Shader.h"
#include <iostream>
#include <string>
#include <vector>
#include "../DLC/stb_image.h"
using namespace std;


class SkyBoxShader :public Shader
{
public:
	SkyBoxShader() : Shader("SkyboxShader","GLSL/skybox.vert", "GLSL/skybox.frag") {

	}
	void setViewMatrix(glm::mat4 viewMatrix) {
		this->setMat4(uniformViewMatrix, viewMatrix);
	}
	void setProjectionMatrix(glm::mat4 projectionMatrix) {
		this->setMat4(uniformProjectionMatrix, projectionMatrix);
	}
	void setSkyBox(GLuint cubemapTexture) {
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
	}

	void skyboxInitialize();

	GLuint cubemapTexture;
	GLuint VAO,VBO;

	void draw(glm::mat4 view, glm::mat4 project);

private:
	//GLchar* vertPath = "../AkukinKensetsu/src/GLSL/model.vert";
	//GLchar* fragPath = "../AkukinKensetsu/src/GLSL/model.frag";

	std::string uniformViewMatrix = "viewMatrix";
	std::string uniformProjectionMatrix = "projectionMatrix";
	std::string uniformSkyBox = "skybox";
};