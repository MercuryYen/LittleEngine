#include "TextBox.h"

/*
left,top,width,height
*/
TextBox::TextBox(float left, float top, float width, float height):Widget(left, top, width, height)
{
	if (!quadVAO) {
		GLfloat quadVertices[] = {
					0,0,
					1,0,
					0,1,
					1,1
		};
		GLuint quadElement[] = {
			0,1,2,
			1,3,2
		};
		GLuint VBO;
		GLuint VEO;

		glGenVertexArrays(1, &quadVAO);

		glGenBuffers(1, &VBO);
		glGenBuffers(1, &VEO);

		glBindVertexArray(quadVAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), quadVertices, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 2, GL_FLOAT, false, 2 * sizeof(GLfloat), 0);
		glEnableVertexAttribArray(0);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VEO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(quadElement), quadElement, GL_STATIC_DRAW);
		glBindVertexArray(0);
	}

	if (!fontShader) {
		fontShader = new FontShader;
	}

	if (!fontTexture) {
		glGenTextures(1, &fontTexture);
		glBindTexture(GL_TEXTURE_RECTANGLE, fontTexture);
		glTexParameteri(GL_TEXTURE_RECTANGLE, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_RECTANGLE, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_RECTANGLE, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_RECTANGLE, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glBindTexture(GL_TEXTURE_RECTANGLE, 0);
	}

	color = glm::vec4(0, 0, 0, 1);
	setFont("YuGothic-Medium-01.ttf");
}

/*
left,top,width,height
text : L""
*/
TextBox::TextBox(float left, float top, float width, float height, const wstring& _text):TextBox(left, top, width, height)
{
	text = _text;
}

void TextBox::draw(float _left, float _top, float _width, float _height)
{

	fontShader->Use();

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_RECTANGLE, fontTexture);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	fontShader->setFontTexture(0);
	fontShader->setColor(color);

	for (int testCnt = 0; testCnt < text.size(); ++testCnt) {

		FT_UInt glyph_index = FT_Get_Char_Index(ft_face, text[testCnt]);
		unsigned int load_flags = 0;

		FT_Error error = FT_Load_Glyph(
			ft_face,          /* handle to face object */
			glyph_index,   /* glyph index           */
			load_flags);

		error = FT_Render_Glyph(ft_face->glyph,   /* glyph slot  */
			FT_RENDER_MODE_NORMAL); /* render mode */

		glm::mat4 position(1.0);
		position = glm::translate(position, glm::vec3(
			_left + _width / 2 * (left + 1) + (ft_face->glyph->bitmap_left / (double)fontResolution + testCnt * 0.92) * width * _width /2/ (text.size()-1),
			_top + _height / 2 * (top - 1) - (((int)ft_face->glyph->bitmap_top - (int)ft_face->glyph->bitmap.rows) / (double)fontResolution) * height * _height/2, 0));
		position = glm::scale(position, glm::vec3(_width*width/2 * (ft_face->glyph->bitmap.width / (double)fontResolution)/ (text.size()-1), -height * (ft_face->glyph->bitmap.rows / (double)fontResolution) * _height/2, 1));
		position[2][0] = position[3][0];
		position[2][1] = position[3][1];
		fontShader->setPositionMatrix(glm::mat3(position));
		fontShader->setSize(ft_face->glyph->bitmap.width, ft_face->glyph->bitmap.rows);

		glTexImage2D(GL_TEXTURE_RECTANGLE, 0, GL_RED, ft_face->glyph->bitmap.width, ft_face->glyph->bitmap.rows, 0, GL_RED, GL_UNSIGNED_BYTE, ft_face->glyph->bitmap.buffer);

		glBindVertexArray(quadVAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
	}
	glBindTexture(GL_TEXTURE_RECTANGLE, 0);
	glUseProgram(0);
	Widget::draw(_left, _top, _width, _height);
}

void TextBox::setFont(string fontFileName)
{
		FT_Error error = FT_Init_FreeType(&ft_library);
		if (error) {
			cout << "ft library error" << endl;
		}
		error = FT_New_Face(ft_library,
			((string)"Font/"+ fontFileName).c_str(),
			0,
			&ft_face);
		if (error == FT_Err_Unknown_File_Format)
		{
			cout << "Unknown fft" << endl;
		}
		else if (error)
		{
			cout << "face error" << endl;
		}

		error = FT_Set_Pixel_Sizes(
			ft_face,    /* handle to face object           */
			fontResolution,   /* pixel width */
			fontResolution);     /* pixel height    */
		if (error)
		{
			cout << "font size is wrong" << endl;
		}
		font = fontFileName;
}

void TextBox::refreshFont()
{
	setFont(font);
}

/*
need to call refreshFont() to update font
*/
void TextBox::setResolution(int resolution = 32)
{
	fontResolution = resolution;
}

void TextBox::setColor(glm::vec4 _color)
{
	color = _color;
}

GLuint TextBox::quadVAO = 0;
FT_Library TextBox::ft_library;
FontShader* TextBox::fontShader = NULL;
GLuint TextBox::fontTexture = 0;
