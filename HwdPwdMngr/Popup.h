#pragma once
#include "DrawUtil.h"
#include <curses.h>
#include <string>
#include <math.h>

WINDOW* openPopupInfo(std::string title, std::string msg);
//WINDOW* openPopupConfirm(std::string msg, void (*confirmCb)(), void (*cancelCb)());
