#include "Popup.h"

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
	const int titleHeight = wprintInLines(win, title.c_str(), lineWidth, POPUP_PADDING_V, POPUP_PADDING_H, TextAlign::CENTER);
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