#include "MenuBase.h"

Menu::Menu(int h, int w) {
	m_h = h;
	m_w = w;
	m_win = newwin(h, w, 0, 0);
}

Menu::~Menu()
{
	delete m_navbar;
}

void Menu::draw() {}
void Menu::inputHandler(int ch) {}

void Menu::drawBase()
{
	wborder(m_win, '|', '|', '-', '-', '+', '+', '+', '+');

	// Expect that the title and navbar will be 1 line in height 
	// Title

	int titleOffset = round((m_w - m_title.length()) / 2);
	mvwprintw(m_win, 1, titleOffset, m_title.c_str());

	// Navbar

	ButtonList buttons;

	std::vector<Button> mainButtons;
	mainButtons.push_back(Button("Enter", "Select"));
	mainButtons.push_back(Button("F1", "Accounts"));
	mainButtons.push_back(Button("F2", "Settings"));
	mainButtons.push_back(Button("F3", "Add account"));
	mainButtons.push_back(Button("F10", "Exit"));

	std::vector<Button> accButtons;
	accButtons.push_back(Button("Esc", "Deselect"));
	accButtons.push_back(Button("F1", "Edit"));
	accButtons.push_back(Button("F2", "Delete"));

	buttons[NavBarState::MENU_MAIN] = mainButtons;
	buttons[NavBarState::ACCOUNT_SELECTED] = accButtons;

	m_navbar = new NavBar(m_win, buttons, m_h - 2, 1, 1, m_w - 2);
	m_navbar->draw();
	wrefresh(m_win);
}
