#include "UI.h"

/*
left,top,width,height

window:
(-1, 1)            (1, 1)
--------------------
|                  |
|                  |
|                  |
--------------------
(-1, -1)           (1, -1)
*/
Widget::Widget(float _left, float _top, float _width, float _height)
{
	left = _left;
	top = _top;
	width = _width;
	height = _height;

	clickEvent = clickEvent_temp;
	hoverEvent = hoverEvent_temp;
}

void Widget::draw()
{
	draw(-1, 1, 2, 2);
}
void Widget::draw(float _left, float _top, float _width, float _height)
{
	for (int i = 0; i < childs.size(); ++i) {
		childs[i]->draw((left+1) * _width/2 + _left, (top-1) * _height/2 + _top, width * _width / 2, height * _height / 2);
	}
}

void Widget::addChild(Widget* child)
{
	this->childs.push_back(child);
}

bool Widget::processMouseIntersection(float mouseX, float mouseY)
{
	mouseX -= left + (width / 2);
	mouseY -= top - (height / 2);
	mouseX /= (width / 2);
	mouseY /= (height / 2);
	bool childIntersection = false;
	int childsNum = childs.size();
	if (mouseX >= -1 && mouseX <= 1 && mouseY >= -1 && mouseY <= 1)
	{
		if (childsNum == 0) {
			if (canBeIntersection) {
				if (!mouseIntersection) {
					mouseIntersection = true;
					hoverEvent(this);
				}
				else
					mouseIntersection = true;
				return true;
			}
			else {
				return false;
			}
		}
		else {
			for (int i = 0; i < childsNum; i++) {
				if (childs[i]->processMouseIntersection(mouseX, mouseY)) {
					childIntersection = true;
					break;
				}
			}
			if (!childIntersection) {
				if (canBeIntersection) {
					if (!mouseIntersection) {
						mouseIntersection = true;
						hoverEvent(this);
					}
					else
						mouseIntersection = true;
					return true;
				}
				else {
					return false;
				}
			}
			else {
				if (canBeIntersection) {
					if (mouseIntersection) {
						mouseIntersection = false;
						hoverEvent(this);
					}
					else
						mouseIntersection = false;
					return false;
				}
				else {
					return false;
				}
			}
		}
	}
	if (canBeIntersection) {
		if (mouseIntersection) {
			mouseIntersection = false;
			hoverEvent(this);
		}
		else
			mouseIntersection = false;
	}
	return false;
}

void Widget::processClick()
{
	int childsNum = childs.size();
	if (mouseIntersection && canBeIntersection)
		clickEvent(this);
	else {
		for (int i = 0; i < childsNum; i++) {
			childs[i]->processClick();
		}
	}
}
void Widget::clickEvent_temp(Widget*)
{

}
/*void Widget::processHover()
{
	int childsNum = childs.size();
	if (mouseIntersection)
		hoverEvent();
	else {
		for (int i = 0; i < childsNum; i++) {
			childs[i]->processHover();
		}
	}
}*/
void Widget::hoverEvent_temp(Widget*)
{

}
/*
float Widget::toXScreenSpace(float position)
{
	return position / (double)GameWindow::SRC_WIDTH * 2 - 1;
}

float Widget::toYScreenSpace(float position)
{
	return -position / (double)GameWindow::SRC_HEIGHT * 2 + 1;
}
*/