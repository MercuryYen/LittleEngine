#pragma once
#include<vector>
#include<string>
using namespace std;
//#include "GameWindow.h"

class Widget {
public :
	string name;
	float left;
	float top;
	float width;
	float height;
	bool canBeIntersection = false;
	bool mouseIntersection = false;

	Widget(float, float, float, float);

	vector<Widget*> childs;

	virtual void draw();
	virtual void draw(float _left, float _top, float _width, float _height);
	void addChild(Widget* child);
	bool processMouseIntersection(float mouseX, float mouseY);
	void processClick();

	void (*clickEvent)(Widget*);
	void (*hoverEvent)(Widget*);

	static void Widget::clickEvent_temp(Widget*);
	static void Widget::hoverEvent_temp(Widget*);

	//virtual void clickEvent();
	//void processHover();
	//virtual void hoverEvent();

	/*static float toXScreenSpace(float position);
	static float toYScreenSpace(float position);*/
};