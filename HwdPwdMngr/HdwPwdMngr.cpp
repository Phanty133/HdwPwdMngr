#include <curses.h>
#include <string>
#include <math.h>
#include "Popup.h"
#include "MenuMain.h"
#include "MenuConfig.h"
#include "ListElement.h"

enum STATE {
	IDLE,
	WORKING,
	WAITING_FOR_USER,
	WAITING_FOR_DEVICE
} progState;

enum ACTION {
	NONE,
	GOTO_MAIN,
	GOTO_CONFIG,
	GET_DATA,
	SEND_DATA,
	QUIT
} progAction;

/* ACTION readInput() {

} */

//WINDOW* drawMenuConfig() {
//
//}

bool update() {
	switch (progState) {
		case IDLE:
			break;
		case WORKING:
			break;
		case WAITING_FOR_USER:
			{
				int ch = getch();

				switch (ch) {
				case KEY_DOWN:
					// list.moveDown();
					break;
				case KEY_UP:
					// list.moveUp();
					break;
				}
			}
			
			break;
		case WAITING_FOR_DEVICE:
			break;
		}

	switch (progAction) {
		case NONE:
			break;
		case GOTO_MAIN:
			drawMenuMain();
			break;
		case GOTO_CONFIG:
			drawMenuConfig();
			break;
		case QUIT:
			endwin();
			return false;
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

	refresh();
	//openPopupInfo("Hey now", "Hello world! Hello world! Hello world! Hello world! Hello world! Hello world! Hello world! Hello world! Hello world! ");

	ListColumn col1("Label", "label");
	ListColumn col2("Username", "username", 50);

	std::vector<ListColumn> cols;
	cols.push_back(col1);
	cols.push_back(col2);

	std::vector<DataEntry> data;
	
	for (int i = 0; i < 420; i++) {
		DataEntry entry;
		entry["label"] = "ThisIsLabel" + std::to_string(i);
		entry["username"] = "ThisIsUsername" + std::to_string(i);

		data.push_back(entry);

	}

	ListElement list = ListElement(0, 0, 20, 100, cols, data);

	while (update()) {}

	return 0;
}