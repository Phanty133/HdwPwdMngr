#pragma once
#include "curses.h"
#include <string>
#include <math.h>

class Scrollbar {
public:
	Scrollbar(WINDOW* orig, int y, int x, int h, int w, int steps);
	void moveDown();
	void moveUp();
	void setPos(int pos);
	void draw();
	void setSteps(int steps); // Set the number of steps the scrollbar should have

	const int& c_steps = m_steps;
	const int& c_pos = m_pos;
	WINDOW* m_win;
private:
	void drawHandle(int handlePos = 0);
	void clearHandle();
	void updateHandle();

	int m_pos = 0;
	int m_steps;
	int m_w;
	int m_h;
	int m_x;
	int m_y;
	WINDOW* m_origWin;
};
