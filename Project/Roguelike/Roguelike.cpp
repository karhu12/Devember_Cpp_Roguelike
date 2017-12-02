#include "stdafx.h"
#include "curses.h"
#include <string>

class _buffer {
public:
	WINDOW *statusWindow, *gameWindow, *textWindow;										/* Initialize 3 windows for status,text and game */	
	void drawBorders(WINDOW * status, WINDOW * textBar);								/* draw borders */
	void bufferRelease(WINDOW * first, WINDOW * second, WINDOW * third);				/* Release buffer memory */
	void drawStatus(WINDOW * status);													/* Draw status window specific */
};

int main() {
	_buffer buffer;									/* Initialize buffer object */
	initscr();										/* Start curses */
	if (has_colors) {								/* Initialize basic colors */
		start_color();
		init_pair(1, COLOR_CYAN, COLOR_BLACK);
		init_pair(2, COLOR_MAGENTA, COLOR_BLACK);
		init_pair(3, COLOR_BLUE, COLOR_BLACK);
		init_pair(4, COLOR_GREEN, COLOR_BLACK);
		init_pair(5, COLOR_RED, COLOR_BLACK);
		init_pair(6, COLOR_YELLOW, COLOR_BLACK);
		init_pair(7, COLOR_WHITE, COLOR_BLACK);
	}
	resize_term(37, 91);							/* Set initial window size */
	buffer.statusWindow = newwin(20, 20, 5, 0);
	buffer.gameWindow = newwin(18, 60, 6, 23);
	buffer.textWindow = newwin(5, 85, 0, 0);		/* Create game windows of approppriate size */
	buffer.drawBorders(buffer.statusWindow, buffer.textWindow);
	buffer.drawStatus(buffer.statusWindow);
	for (int i = 0; i < 18; i++) {
		for (int j = 0; j < 60; j++) {
			wattron(buffer.gameWindow, COLOR_PAIR(4));
			mvwaddch(buffer.gameWindow, i, j, ACS_CKBOARD);
			wattroff(buffer.gameWindow, COLOR_PAIR(4));
		}
	}
	wrefresh(buffer.gameWindow);
	wmove(buffer.textWindow, 3, 1);
	wgetch(buffer.textWindow);
	buffer.bufferRelease(buffer.statusWindow, buffer.gameWindow, buffer.textWindow);
	return 0;
}

void _buffer::drawBorders(WINDOW * status, WINDOW * text) {
	box(status, ACS_VLINE, ACS_HLINE);
	box(text, ACS_VLINE, ACS_HLINE);						/* draw borders to window buffers */
	wrefresh(status);
	wrefresh(text);								/* Refresh draws buffer to the actual screen */
}

void _buffer::drawStatus(WINDOW * status) {
	wattron(status, A_BOLD);
	mvwprintw(status, 2, 2, "PLAYER");
	wattroff(status, A_BOLD);

	wattron(status, A_BOLD);
	wattron(status, COLOR_PAIR(5));
	mvwprintw(status, 4, 2, "HP");
	wattroff(status, COLOR_PAIR(5));
	wattroff(status, A_BOLD);

	wattron(status, A_BOLD);
	wattron(status, COLOR_PAIR(6));
	mvwprintw(status, 5, 2, "LEVEL");
	mvwprintw(status, 6, 2, "EXP");
	wattroff(status, COLOR_PAIR(6));
	wattroff(status, A_BOLD);

	wattron(status, A_BOLD);
	mvwprintw(status, 8, 2, "ATTRIBUTES");
	wattroff(status, A_BOLD);

	wattron(status, A_BOLD);
	wattron(status, COLOR_PAIR(5));
	mvwprintw(status, 10, 2, "STR");
	wattroff(status, COLOR_PAIR(5));
	wattroff(status, A_BOLD);

	wattron(status, A_BOLD);
	wattron(status, COLOR_PAIR(4));
	mvwprintw(status, 11, 2, "DEX");
	wattroff(status, COLOR_PAIR(4));
	wattroff(status, A_BOLD);

	wattron(status, A_BOLD);
	wattron(status, COLOR_PAIR(3));
	mvwprintw(status, 12, 2, "INT");
	wattroff(status, COLOR_PAIR(3));
	wattroff(status, A_BOLD);
	

	wrefresh(status);
}

void _buffer::bufferRelease(WINDOW * first, WINDOW * second, WINDOW * third) {
	delwin(first);
	delwin(second);
	delwin(third);
	endwin();									/* free all window buffer memory */
}