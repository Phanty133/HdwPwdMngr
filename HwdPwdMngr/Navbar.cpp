#include "Navbar.h"

NavBar::NavBar(WINDOW* parent, ButtonList buttons, int y, int x, int h, int w)
{
	m_buttons = buttons;
	m_parent = parent;
	m_y = y;
	m_x = x;
	m_h = h;
	m_w = w;
	m_win = derwin(parent, h, w, y, x);
}

void NavBar::setState(NavBarState newState)
{
	m_state = newState;
	wclear(m_win);
	draw();
}

void NavBar::draw()
{
	std::vector<Button> activeButtons = m_buttons[m_state];

	int totalButtonWidth = 0;

	for (auto& btn : activeButtons) {
		totalButtonWidth += btn.key.length() + btn.label.length() + 1;
	}

	int buttonPadding = round((m_w - 2 - totalButtonWidth) / (activeButtons.size() + 1));
	int xOffset = buttonPadding;

	for (auto& btn : activeButtons) {
		int btnWidth = drawButton(0, xOffset, btn);

		xOffset += btnWidth + buttonPadding;
	}

	wrefresh(m_win);
}

int NavBar::drawButton(int y, int x, Button button)
{
	wattron(m_win, A_REVERSE);
	mvwaddstr(m_win, y, x + 1,button.key.c_str());
	wattroff(m_win, A_REVERSE);

	wprintw(m_win, " %s", button.label.c_str());

	return button.key.length() + button.label.length() + 1;
}
