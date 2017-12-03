#include "stdafx.h"
#include "tiles.h"

void wColorOn(WINDOW *win, int foreground, int background) {
	int x = returnColorPair(foreground, background);
	wattron(win, COLOR_PAIR(x)); 
}

void wColorOff(WINDOW *win, int foreground, int background) {
	int x = returnColorPair(foreground, background);
	wattroff(win, COLOR_PAIR(x));
}