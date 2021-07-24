#include <curses.h>
#include <string>
#include <math.h>

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
	SEND_DATA
};

/* ACTION readInput() {

}

WINDOW* drawMenuMain() {

}

WINDOW* drawMenuConfig() {

} */

int calcTextHeight(std::string msg, int maxLen) {
	const int msgLen = msg.length();
	const int lineWidth = std::min(msgLen, maxLen);

	return ceil(msgLen / lineWidth);
}

int wprintInLines(WINDOW* win, std::string msg, int maxLen, int y0, int x0, int align = 0, bool fillEmpty = false) { // align = 0: Left align, align = 1 - Center align, align = 2: Right align
	const int msgLen = msg.length();
	const int lineWidth = std::min(msgLen, maxLen);
	const int msgHeight = ceil(msgLen / lineWidth);

	for (int i = 0; i < msgHeight; i++) {
		std::string writeMsg = msg.substr(lineWidth * i, lineWidth);

		switch (align) {
		case 0:
			mvwaddstr(win, y0 + i, x0, writeMsg.c_str());
			break;
		case 1:
			{
				const int offset = (maxLen - writeMsg.length()) / 2;

				if (fillEmpty) {
					mvwaddstr(win, y0 + i, x0, std::string(offset, ' ').c_str());
					mvwaddstr(win, y0 + i, x0 + offset + writeMsg.length(), std::string(offset, ' ').c_str());
				}

				mvwaddstr(win, y0 + i, x0 + offset, writeMsg.c_str());
			}
			break;
		case 2:
			{
				const int offset = maxLen - writeMsg.length();

				if (fillEmpty) mvwaddstr(win, y0 + i, x0 + offset, std::string(offset, ' ').c_str());

				mvwaddstr(win, y0 + i, x0 + offset, writeMsg.c_str());
			}
			break;
		}
	}

	return msgHeight;
}

void drawButton(WINDOW* win, std::string text, int cy, int cx, int h, int w, int PADDING_H = 1, int PADDING_V = 0) {
	wattron(win, COLOR_PAIR(1)); // Set the button color scheme

	const int msgHeight = calcTextHeight(text, w - PADDING_H * 2);
	const int y0 = cy - h / 2;
	const int x0 = cx - w / 2;

	const int vertPadding = h - msgHeight + PADDING_V;

	// Print top padding
	for (int i = 0; i < vertPadding / 2; i++) {
		mvwaddstr(win, y0 + i, x0, std::string(w, ' ').c_str());
	}

	const int textY = y0 + vertPadding / 2;

	mvwaddstr(win, textY, x0, std::string(PADDING_H, ' ').c_str()); // Text padding
	wprintInLines(win, text, w - PADDING_H * 2, textY, x0 + PADDING_H, 1, true); // Print text
	mvwaddstr(win, textY, x0 + w - PADDING_H, std::string(PADDING_H, ' ').c_str()); // Text padding

	// Print bottom padding

	for (int i = 0; i < vertPadding / 2; i++) {
		mvwaddstr(win, y0 + vertPadding / 2 + msgHeight, x0, std::string(w, ' ').c_str());
	}

	wattroff(win, COLOR_PAIR(1));
}

WINDOW* openPopupInfo(std::string title, std::string msg) {
	const int POPUP_PADDING_H = 5; // How many characters is the horizontal padding
	const int POPUP_PADDING_V = 1; // How many characters is the vertical padding
	const float MAX_POPUP_SIZE = 0.5; // What portion of the terminal should the popup fit in

	WINDOW* win = newwin(0, 0, 0, 0); // Temporarily make the window fullscreen

	const int msgLen = msg.length();
	const int maxPopupWidth = getmaxx(stdscr) * MAX_POPUP_SIZE;
	const int lineWidth = std::min(msgLen, maxPopupWidth - POPUP_PADDING_H * 2);
	const int popupWidth = lineWidth + POPUP_PADDING_H * 2;

	wattron(win, A_BOLD);
	const int titleHeight = wprintInLines(win, title.c_str(), lineWidth, POPUP_PADDING_V, POPUP_PADDING_H, 1);
	wattroff(win, A_BOLD);

	const int msgHeight = wprintInLines(win, msg, lineWidth, POPUP_PADDING_V + titleHeight + 1, POPUP_PADDING_H + titleHeight + 1);
	const int btnY = POPUP_PADDING_V + titleHeight + msgHeight + 2; // Add 1 for padding, add 1 to get the center Y of the button

	drawButton(win, "OK", btnY, popupWidth / 2, 1, 10);

	const int popupHeight = POPUP_PADDING_V + titleHeight + msgHeight + btnY + POPUP_PADDING_V - 3;
	const int startX = (getmaxx(stdscr) - popupWidth) / 2;
	const int startY = (getmaxy(stdscr) - popupHeight) / 2;

	resize_window(win, popupHeight, popupWidth + 3);
	mvwin(win, startY, startX - 3);
	wborder(win, '|', '|', '-', '-', '+', '+', '+', '+');

	wrefresh(win);

	return win;
}

/* WINDOW* openPopupConfirm(std::string msg, void (*confirmCb)(), void (*cancelCb)()) {

} */

void update() {
	switch (progState) {
	case IDLE:
		break;
	case WORKING:
		break;
	case WAITING_FOR_USER:
		break;
	case WAITING_FOR_DEVICE:
		break;
	}
}

class DataList {
	DataList() {

	}
};

int main() {
	initscr();
	start_color();

	// Initialize the color scheme

	init_pair(1, COLOR_BLACK, COLOR_WHITE); // Button color

	refresh();
	openPopupInfo("Hey now", "Hello world! Hello world! Hello world! Hello world! Hello world! Hello world! Hello world! Hello world! Hello world! ");

	getch();
	endwin();

	return 0;
}