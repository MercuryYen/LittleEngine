#include "GameManager.h"

GameManager::GameManager() {
	manager = this;
	cursorMiddleX = GameWindow::SRC_WIDTH / 2;
	cursorMiddleY = GameWindow::SRC_HEIGHT / 2;
}

void GameManager::draw()
{
	if (gladLoadGL()) {

	}
	else
		throw std::runtime_error("Could not initialize GLAD!");
	{
		unsigned long long int c = clock();
		deltaTime = (c - lastTime)/1000.0;
		lastTime = c;
	}

	processCursorMove();

	if (gp != gpPre) {
		switch (gp)
		{
		case GameProcess::INTRO:
			if (!testScene) {
				testScene = new TestScene;
			}
			testScene->init();
							   
			break;
		case GameProcess::DUMMY:
			break;
		default:
			break;
		}

		gpPre = gp;
	}

	switch (gp) {
	case GameProcess::INTRO:
		if (GetActiveWindow()) {
			testScene->processKeyboard();
		}
		testScene->update();
		testScene->draw();
		break;
	default:
		break;
	}


}

void GameManager::processCursorMove() {
	if (GetActiveWindow()) {
		cursorDeltaX = Fl::event_x_root() - cursorMiddleX;
		cursorDeltaY = Fl::event_y_root() - cursorMiddleY;
		cursorSimuX += cursorDeltaX;
		cursorSimuY += cursorDeltaY;

		if (cursorSimuX >= window->SRC_WIDTH)cursorSimuX = window->SRC_WIDTH - 1;
		else if (cursorSimuX < 0)cursorSimuX = 0;
		if (cursorSimuY >= window->SRC_HEIGHT)cursorSimuY = window->SRC_HEIGHT - 1;
		else if (cursorSimuY < 0)cursorSimuY = 0;
		while (ShowCursor(false) >= 0) ShowCursor(false);
		//while (ShowCursor(true) <= 0) ShowCursor(true);
		SetCursorPos(cursorMiddleX, cursorMiddleY);
	}
	else {
		while (ShowCursor(true) <= 0) ShowCursor(true);
	}
}

GameManager* GameManager::manager = NULL;
GameWindow* GameManager::window = NULL;
