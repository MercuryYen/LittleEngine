#include "GameWindow.h"
#include <winuser.h>


GameWindow::GameWindow(const int x, const int y)
	: Fl_Gl_Window(x, y, 800, 600, "Physics! Yeah! Physics! Yeah! ζ*(・ヮ・)*ζ")
{
	{
		int x = 0, y = 0, w = 0, h = 0, n = 0;
		Fl::screen_xywh(x, y, w, h, n);
		SRC_WIDTH = w;
		SRC_HEIGHT = h;
	}
	gm = new GameManager;
	GameManager::manager = gm;
	GameManager::manager->window = this;
	mode(FL_RGB | FL_ALPHA | FL_DOUBLE | FL_STENCIL);
	Fl::add_idle((void (*)(void*))GameWindow::update, this);
	fullscreen();
	while (ShowCursor(false) >= 0)ShowCursor(false);
	gladLoadGL();
}

int GameWindow::handle(int event)
{
	// remember what button was used
	static int last_push;
	
	switch (event) {
		// Mouse button being pushed event
	case FL_PUSH:
		last_push = Fl::event_button();
		/*// if the left button be pushed is left mouse button
		if (last_push == FL_LEFT_MOUSE) {
			doPick();
			damage(1);
			return 1;
		};*/
		break;

		// Mouse button release event
	case FL_RELEASE: // button release
		/*damage(1);
		last_push = 0;
		return 1;*/
		break;

		// Mouse button drag event
	case FL_DRAG:

		/*// Compute the new control point position
		if ((last_push == FL_LEFT_MOUSE) && (selectedCube >= 0)) {
			ControlPoint* cp = &m_pTrack->points[selectedCube];

			double r1x, r1y, r1z, r2x, r2y, r2z;
			getMouseLine(r1x, r1y, r1z, r2x, r2y, r2z);

			double rx, ry, rz;
			mousePoleGo(r1x, r1y, r1z, r2x, r2y, r2z,
				static_cast<double>(cp->pos.x),
				static_cast<double>(cp->pos.y),
				static_cast<double>(cp->pos.z),
				rx, ry, rz,
				(Fl::event_state() & FL_CTRL) != 0);

			cp->pos.x = (float)rx;
			cp->pos.y = (float)ry;
			cp->pos.z = (float)rz;
			damage(1);
		}*/
		break;

		// in order to get keyboard events, we need to accept focus
	case FL_FOCUS:
		//return 1;
		break;

		// every time the mouse enters this window, aggressively take focus
	case FL_ENTER:
		//focus(this);
		break;

	case FL_KEYBOARD:
		int k = Fl::event_key();
		int ks = Fl::event_state();
		
	}
	return Fl_Gl_Window::handle(event);
}

void GameWindow::draw()
{
	GameManager::manager->draw();
	/*if (gladLoadGL()) {

	}
	else
		throw std::runtime_error("Could not initialize GLAD!");*/



}

void GameWindow::update(GameWindow* gw)
{
	static vector<int> clockHistory;
	int t = clock();
	static int lastClock = 0;
	static int clockSum = 0;
	if (t - lastClock > 1000.0 / gw->fps)
	{
		gw->deltaTime = (t - lastClock) / 1000.0;
		gw->damage(1);
		clockHistory.push_back(t - lastClock);
		clockSum += clockHistory.back();
		if (clockHistory.size() > 30)
		{
			clockSum -= clockHistory[0];
			clockHistory.erase(clockHistory.begin());
		}
		//cout << 30.0*1000 / clockSum << endl;
		lastClock = t;
	}


}

float GameWindow::toXScreenSpace(float position)
{
	return position / (double)GameWindow::SRC_WIDTH * 2 - 1;
}
float GameWindow::toYScreenSpace(float position)
{
	return -position / (double)GameWindow::SRC_HEIGHT * 2 + 1;
}

int GameWindow::SRC_WIDTH = 0;
int GameWindow::SRC_HEIGHT = 0;