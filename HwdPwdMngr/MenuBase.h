#pragma once
#include "curses.h"
#include "Navbar.h"
#include <string>

class Menu {
public:
	Menu(int h, int w);
	~Menu();
	virtual void draw() = 0;
	virtual void inputHandler(int ch) = 0;

	const int& c_w = m_w;
	const int& c_h = m_h;
protected:
	void drawBase();

	std::string m_title = "";
	int m_w;
	int m_h;
	WINDOW* m_win;

	NavBar* m_navbar = nullptr;
};
