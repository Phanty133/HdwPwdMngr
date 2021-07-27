#pragma once
#include "curses.h"
#include "MenuBase.h"
#include "ListElement.h"

class MenuMain: public Menu {
public:
	MenuMain(int h, int w);
	~MenuMain();
	void draw();
	void inputHandler(int ch);
private:
	ListElement* m_list;
};
