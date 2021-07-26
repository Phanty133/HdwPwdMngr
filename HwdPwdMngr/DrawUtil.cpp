#include "DrawUtil.h";

int calcTextHeight(std::string msg, int maxLen) {
	const int msgLen = msg.length();
	const int lineWidth = std::min(msgLen, maxLen);

	return ceil(msgLen / lineWidth);
}

int wprintInLines(WINDOW* win, std::string msg, int maxLen, int y0, int x0, TextAlign align, bool fillEmpty) {
	const int msgLen = msg.length();
	const int lineWidth = std::min(msgLen, maxLen);
	const int msgHeight = ceil(msgLen / lineWidth);

	for (int i = 0; i < msgHeight; i++) {
		std::string writeMsg = msg.substr(lineWidth * i, lineWidth);

		switch (align) {
		case LEFT:
			mvwaddstr(win, y0 + i, x0, writeMsg.c_str());
			break;
		case CENTER:
		{
			const int offset = (maxLen - writeMsg.length()) / 2;

			if (fillEmpty) {
				mvwaddstr(win, y0 + i, x0, std::string(offset, ' ').c_str());
				mvwaddstr(win, y0 + i, x0 + offset + writeMsg.length(), std::string(offset, ' ').c_str());
			}

			mvwaddstr(win, y0 + i, x0 + offset, writeMsg.c_str());
		}
		break;
		case RIGHT:
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

void drawButton(WINDOW* win, std::string text, int cy, int cx, int h, int w, int PADDING_H, int PADDING_V) {
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
	wprintInLines(win, text, w - PADDING_H * 2, textY, x0 + PADDING_H, CENTER, true); // Print text
	mvwaddstr(win, textY, x0 + w - PADDING_H, std::string(PADDING_H, ' ').c_str()); // Text padding

	// Print bottom padding

	for (int i = 0; i < vertPadding / 2; i++) {
		mvwaddstr(win, y0 + vertPadding / 2 + msgHeight, x0, std::string(w, ' ').c_str());
	}

	wattroff(win, COLOR_PAIR(1));
}
