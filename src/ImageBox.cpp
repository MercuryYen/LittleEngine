#include "ImageBox.h"

/*
left,top,width,height
*/
ImageBox::ImageBox(float left, float top, float width, float height):Widget(left, top, width, height)
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

	if (!imageShader) {
		imageShader = new ImageShader;
	}
	color = glm::vec4(1, 1, 1, 1);
	hoverColor = glm::vec4(1, 1, 1, 1);
	
	clickEvent = clickEvent_ImageBox;
	hoverEvent = hoverEvent_ImageBox;
}

/*
left,top,width,height
*/
ImageBox::ImageBox(float left, float top, float width, float height, const GLuint& _texture):ImageBox(left, top, width, height)
{
	texture = _texture;
}

void ImageBox::draw(float _left, float _top, float _width, float _height)
{

	imageShader->Use();

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	imageShader->setTexture(0);

	imageShader->setColor(color);

	imageShader->setHoverColor(hoverColor);

	glm::mat4 position(1.0);
	position = glm::translate(position, glm::vec3(
		_left + _width /2* (left+1),
		_top + _height /2* (top-1), 0));
	position = glm::scale(position, glm::vec3(_width * width/2, _height/2 * -height, 1));
	position[2][0] = position[3][0];
	position[2][1] = position[3][1];
	imageShader->setPositionMatrix(glm::mat3(position));
	
	glBindVertexArray(quadVAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

	glBindTexture(GL_TEXTURE_2D, 0);
	glUseProgram(0);
	Widget::draw(_left, _top, _width, _height);
}

void ImageBox::clickEvent_ImageBox(Widget* t)
{
	glm::vec4 changeColor = glm::vec4(0, 0.8, 0, 1);
	if(((ImageBox*)t)->color == changeColor)
		((ImageBox*)t)->color = glm::vec4(1, 1, 1, 1);
	else
		((ImageBox*)t)->color = changeColor;
}

void ImageBox::hoverEvent_ImageBox(Widget* t)
{
	if(((ImageBox*)t)->mouseIntersection)
		((ImageBox*)t)->hoverColor = glm::vec4(0.8, 0.8, 0.8, 1);
	else
		((ImageBox*)t)->hoverColor = glm::vec4(1, 1, 1, 1);
}



GLuint ImageBox::quadVAO = 0;
ImageShader* ImageBox::imageShader = NULL;
