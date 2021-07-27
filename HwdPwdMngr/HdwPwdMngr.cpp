#include <curses.h>
#include <string>
#include <math.h>
#include "Popup.h"
#include "MenuMain.h"
#include "MenuConfig.h"

enum class STATE {
	IDLE,
	WORKING,
	WAITING_FOR_USER,
	WAITING_FOR_DEVICE
} progState;

enum class ACTION {
	NONE,
	GOTO_MAIN,
	GOTO_CONFIG,
	GET_DATA,
	SEND_DATA,
	QUIT
} progAction;

MenuMain* menuMain;
Menu* activeMenu = nullptr;

bool update() {
	switch (progAction) {
	case ACTION::NONE:
		break;
	case ACTION::GOTO_MAIN:
		menuMain->draw();
		activeMenu = menuMain;
		progState = STATE::WAITING_FOR_USER;
		break;
	case ACTION::GOTO_CONFIG:
		drawMenuConfig();
		break;
	case ACTION::QUIT:
		endwin();
		return false;
		break;
	}

	if (progAction != ACTION::NONE) {
		progAction = ACTION::NONE;
	}

	switch (progState) {
	case STATE::IDLE:
		break;
	case STATE::WORKING:
		break;
	case STATE::WAITING_FOR_USER:
		{
			int ch = getch();

			if (activeMenu != nullptr) {
				activeMenu->inputHandler(ch);
			}
		}
			
		break;
	case STATE::WAITING_FOR_DEVICE:
		break;
	}

	return true;
}

int main() {
	initscr();
	start_color();
	raw();
	noecho();
	curs_set(0);
	keypad(stdscr, TRUE);

	// Initialize the color scheme

	init_pair(1, COLOR_BLACK, COLOR_WHITE); // Button color
	init_pair(2, COLOR_RED, COLOR_WHITE); // Selected entry color

	menuMain = new MenuMain(getmaxy(stdscr), getmaxx(stdscr));
	progAction = ACTION::GOTO_MAIN;

	refresh();

	while (update()) {}

	delete menuMain;

	return 0;
}