#include "stdafx.h"
#include "curses.h"
#include <string>
#include <iostream>

class _buffer {
public:
	WINDOW *statusWindow, *gameWindow, *textWindow;								/* Initialize 3 windows for status,text and game */	
	void drawBorders(WINDOW * status, WINDOW * textBar);						/* draw borders */
	void bufferRelease(WINDOW * first, WINDOW * second, WINDOW * third);		/* Release buffer memory */
	void drawGame(WINDOW * game);												/* Draw game state */
	void drawStatus(WINDOW * status);											/* Draw status window specific */
};

class character {
public:
	short health, xPos, yPos;
};

class state: public _buffer {
public:
	bool status;
};

int main() {
	state game;										/* Initialize game state object */
	character player;
	initscr();										/* Start curses */
	curs_set(0);									/* Hide cursor */
	resize_term(37, 91);							/* Set initial window size */
	if (has_colors() == TRUE) {						/* Initialize basic colors */
		start_color();
		init_pair(1, COLOR_BLUE, COLOR_BLUE);		/* First color character color and second for background */
		init_pair(2, COLOR_GREEN, COLOR_GREEN);
		init_pair(3, COLOR_RED, COLOR_RED);
		init_pair(4, COLOR_YELLOW, COLOR_BLACK);
		init_pair(5, COLOR_RED, COLOR_BLACK);
	}

	game.status = true;

	game.statusWindow = newwin(20, 20, 5, 0);
	game.gameWindow = newwin(18, 60, 6, 23);
	game.textWindow = newwin(5, 85, 0, 0);			/* Create game windows of approppriate size */

	while (game.status == true) {
		game.drawBorders(game.statusWindow, game.textWindow);
		game.drawStatus(game.statusWindow);
		game.drawGame(game.gameWindow);				/* Buffer draw functions */

		mvwprintw(game.textWindow, 1, 2, "Text log");
		if (mvwgetch(game.textWindow, 3, 2) == 'q')
			game.status = false;
	}
													/* Release window buffer memory */
	game.bufferRelease(game.statusWindow, game.gameWindow, game.textWindow);
	return 0;
}

void _buffer::drawBorders(WINDOW * status, WINDOW * text) {
	box(status, ACS_VLINE, ACS_HLINE);
	box(text, ACS_VLINE, ACS_HLINE);				/* draw borders to window buffers */
	wrefresh(status);
	wrefresh(text);									/* Refresh draws buffer to the actual screen */
}

void _buffer::drawGame(WINDOW * game) {
	for (int i = 0; i < 18; i++) {					/* Example of game field drawn from 0,0 coordinate */
		for (int j = 0; j < 60; j++) {
			wattron(game, COLOR_PAIR(2));
			wattron(game, A_BOLD);
			mvwaddch(game, i, j, ' ');
			wattroff(game, A_BOLD);
			wattroff(game, COLOR_PAIR(2));
		}
	}
	for (int i = 2; i < 7; i++)
		for (int j = 2; j < 13; j++) {
			wattron(game, COLOR_PAIR(2));
			wattron(game, A_BOLD);
			mvwaddch(game, i, j, ACS_UARROW);
			wattroff(game, A_BOLD);
			wattroff(game, COLOR_PAIR(2));
		}
	for (int i = 10; i < 15; i++)
		for (int j = 2; j < 23; j++) {
			wattron(game, COLOR_PAIR(1));
			wattron(game, A_BOLD);
			mvwaddch(game, i, j, '~');
			wattroff(game, A_BOLD);
			wattroff(game, COLOR_PAIR(1));
		}
	wrefresh(game);
}

void _buffer::drawStatus(WINDOW * status) {			/* Draw text on status bar (later on add actual variables) */
	wattron(status, A_BOLD);
	mvwprintw(status, 2, 2, "PLAYER");
	wattroff(status, A_BOLD);

	wattron(status, A_BOLD);
	wattron(status, COLOR_PAIR(5));
	mvwprintw(status, 4, 2, "HP");
	wattroff(status, COLOR_PAIR(5));
	wattroff(status, A_BOLD);

	wattron(status, A_BOLD);
	wattron(status, COLOR_PAIR(4));
	mvwprintw(status, 5, 2, "LEVEL");
	mvwprintw(status, 6, 2, "EXP");
	wattroff(status, COLOR_PAIR(4));
	wattroff(status, A_BOLD);

	wattron(status, A_BOLD);
	mvwprintw(status, 8, 2, "ATTRIBUTES");
	wattroff(status, A_BOLD);

	wattron(status, A_BOLD);
	wattron(status, COLOR_PAIR(3));
	mvwprintw(status, 10, 2, "STR");
	wattroff(status, COLOR_PAIR(3));
	wattroff(status, A_BOLD);

	wattron(status, A_BOLD);
	wattron(status, COLOR_PAIR(2));
	mvwprintw(status, 11, 2, "DEX");
	wattroff(status, COLOR_PAIR(2));
	wattroff(status, A_BOLD);

	wattron(status, A_BOLD);
	wattron(status, COLOR_PAIR(1));
	mvwprintw(status, 12, 2, "INT");
	wattroff(status, COLOR_PAIR(1));
	wattroff(status, A_BOLD);
	
	wrefresh(status);							
}

void _buffer::bufferRelease(WINDOW * first, WINDOW * second, WINDOW * third) {
	delwin(first);
	delwin(second);
	delwin(third);
	endwin();									/* free every windows buffer memory */
}