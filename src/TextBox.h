#pragma once

#include <Fl/fl.h>
#include "UI.h"
#include "glm/glm.hpp"
#include <glm/gtx/transform.hpp>
#include "Shaders/FontShader.h"
#include <ft2build.h>
#include<map>
#include<string>
#include FT_FREETYPE_H
using namespace std;

class TextBox :public Widget {
public:
	TextBox(float, float, float, float);
	TextBox(float, float, float, float, const wstring&);
	void draw(float _left, float _top, float _width, float _height);

	void setFont(string fontFileName);
	void refreshFont();

	void setResolution(int resolution);
	void setColor(glm::vec4 _color);

	string font;
	wstring text;
	glm::vec4 color;
	int fontResolution = 32;
	FT_Face ft_face;

	static GLuint fontTexture;
	static FontShader* fontShader;
	static GLuint quadVAO;
	static FT_Library ft_library;
};