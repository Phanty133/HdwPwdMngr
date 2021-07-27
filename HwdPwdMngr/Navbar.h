#pragma once
#include "curses.h"
#include <string>
#include <vector>
#include <map>
#include <math.h>

enum class NavBarState {
	MENU_MAIN,
	MENU_SETTINGS,
	ACCOUNT_SELECTED
};

struct Button {
	std::string label;
	std::string key;

	Button(std::string key, std::string label) {
		this->label = label;
		this->key = key;
	};
};

typedef std::map<NavBarState, std::vector<Button>> ButtonList;

class NavBar {
public:
	NavBar(WINDOW* parent, ButtonList buttons, int y, int x, int h, int w);
	void setState(NavBarState newState);
	void draw();

	const NavBarState& c_state = m_state;
	const int& c_x = m_x;
	const int& c_y = m_y;
	const int& c_w = m_w;
	const int& c_h = m_h;
private:
	int drawButton(int y, int x, Button button); // Returns button width

	ButtonList m_buttons;
	NavBarState m_state = NavBarState::MENU_MAIN;
	WINDOW* m_parent;
	WINDOW* m_win;

	int m_x;
	int m_y;
	int m_w;
	int m_h;
};