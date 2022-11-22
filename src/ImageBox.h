#pragma once

#include <Fl/fl.h>
#include "UI.h"
#include "glm/glm.hpp"
#include <glm/gtx/transform.hpp>
#include "Shaders/ImageShader.h"
#include<map>
#include<string>
using namespace std;

class ImageBox :public Widget {
public:
	ImageBox(float, float, float, float);
	ImageBox(float, float, float, float, const GLuint&);
	void draw(float _left, float _top, float _width, float _height);
	static void clickEvent_ImageBox(Widget*);
	static void hoverEvent_ImageBox(Widget*);

	/*
		1: click event
		2: hover event
	*/
	int ImageBoxStatusFlag = 0;
	GLuint texture = 0;
	glm::vec4 color;
	glm::vec4 hoverColor;

	static GLuint quadVAO;
	static ImageShader* imageShader;
};