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

void initializeColors() {
	int ind = 1;
	if (has_colors() == TRUE) {						/* Initialize all possible color pairs */
		start_color();
		for (int i = 0; i <= 8; i++) {
			for (int j = 0; j <= 8; j++) {
				init_pair(ind, i, j);
				ind++;
			}
		}
	}
}

int randomNumber(int minValue, int maxValue) {
	int number = rand() % maxValue + minValue;
	return number;
}