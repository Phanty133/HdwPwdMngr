#pragma once
#include <curses.h>
#include <string>
#include <math.h>

enum class TextAlign {
	LEFT,
	CENTER,
	RIGHT
};

int calcTextHeight(std::string msg, int maxLen);
int wprintInLines(WINDOW* win, std::string msg, int maxLen, int y0, int x0, TextAlign align = TextAlign::LEFT, bool fillEmpty = false);
void drawButton(WINDOW* win, std::string text, int cy, int cx, int h, int w, int PADDING_H = 1, int PADDING_V = 0);
