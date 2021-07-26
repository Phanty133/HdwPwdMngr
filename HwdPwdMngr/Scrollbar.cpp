#include "Scrollbar.h"

Scrollbar::Scrollbar(WINDOW* orig, int y, int x, int h, int w, int steps)
{
	m_y = y;
	m_x = x;
	m_h = h;
	m_w = w;
	m_steps = std::min(steps, h - 2); // Limit the number of steps to the height of the scrollbar
	m_origWin = orig;
	m_win = derwin(orig, m_h, m_w, m_y, m_x);
}

void Scrollbar::moveDown()
{
	m_pos = std::min(m_steps, m_pos + 1);
	printw(std::to_string(m_pos).c_str());
	updateHandle();
}

void Scrollbar::moveUp()
{
	m_pos = std::max(0, m_pos - 2); // I have no idea why it has to be -2
	updateHandle();
}

void Scrollbar::setPos(int pos)
{
	m_pos = std::min(std::max(pos, 0), m_steps); // Clamp the position
	updateHandle();
}

void Scrollbar::drawHandle(int handlePos)
{
	std::string lineText(m_w - 2, '#');

	for (int i = 1; i < m_h - m_steps; i++) {
		mvwprintw(m_win, handlePos + i, 1, lineText.c_str());
	}
}

void Scrollbar::updateHandle()
{
	clearHandle();
	drawHandle(m_pos);
	wrefresh(m_win);
	wsyncup(m_win);
}

void Scrollbar::clearHandle()
{
	std::string lineText(m_w - 2, ' ');

	for (int i = 1; i < m_h - 1; i++) {
		mvwprintw(m_win, i, 1, lineText.c_str());
	}
}

void Scrollbar::draw()
{
	drawHandle();

	wborder(m_win, '|', '|', '-', '-', '+', '+', '+', '+');
	wrefresh(m_win);
	wsyncup(m_win);
}

void Scrollbar::setSteps(int steps)
{
	m_steps = std::min(steps, m_h - 2); // Limit the number of steps to the height of the scrollbar
	setPos(0); // After updating the step count, reset handle position
}
