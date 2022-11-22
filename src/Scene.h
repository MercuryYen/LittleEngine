#pragma once

class Scene {
public:
	virtual void init();
	virtual void update();
	virtual void draw();
	virtual void processKeyboard();
};