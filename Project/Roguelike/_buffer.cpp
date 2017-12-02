#include "stdafx.h"
#include "_buffer.h"

void _buffer::drawBorders(WINDOW * status, WINDOW * text) {
	box(status, ACS_VLINE, ACS_HLINE);
	box(text, ACS_VLINE, ACS_HLINE);				/* draw borders to window buffers */
	wrefresh(status);
	wrefresh(text);									/* Refresh draws buffer to the actual screen */
}

void _buffer::drawGame(WINDOW * game, int map[][AREA_MAX_WIDTH], character *player) {
	for (int i = 0; i < AREA_MAX_HEIGHT + 1; i++) {					/* Example of game field drawn from 0,0 coordinate */
		for (int j = 0; j < AREA_MAX_WIDTH + 1; j++) {
			if (i == player->yPos && j == player->xPos) {
				wattron(game, A_BOLD);
				wattron(game, COLOR_PAIR(6));
				mvwaddch(game, i, j, '@');
				wattroff(game, COLOR_PAIR(6));
				wattroff(game, A_BOLD);
			}
			else {
				wattron(game, A_BOLD);
				wattron(game, COLOR_PAIR(2));
				mvwaddch(game, i, j, '.');
				wattroff(game, COLOR_PAIR(2));
				wattroff(game, A_BOLD);
			}
		}
	}
	wrefresh(game);
}

void _buffer::drawStatus(WINDOW * status, character * player) {			/* Draw text on status bar (later on add actual variables) */
	wattron(status, A_BOLD);
	mvwprintw(status, 2, 2, "PLAYER");
	wattroff(status, A_BOLD);

	wattron(status, A_BOLD);
	wattron(status, COLOR_PAIR(5));
	mvwprintw(status, 4, 2, "HP");
	wattroff(status, COLOR_PAIR(5));
	wattroff(status, A_BOLD);

	wattron(status, A_BOLD);
	mvwprintw(status, 4, 10, "%d", player->health);
	wattroff(status, A_BOLD);

	wattron(status, A_BOLD);
	wattron(status, COLOR_PAIR(4));
	mvwprintw(status, 5, 2, "LEVEL");
	mvwprintw(status, 6, 2, "EXP");
	wattroff(status, COLOR_PAIR(4));
	wattroff(status, A_BOLD);

	wattron(status, A_BOLD);
	mvwprintw(status, 5, 10, "%d", player->level);
	mvwprintw(status, 6, 10, "%d", player->experience);
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

void _buffer::bufferRelease(state *game) {
	delwin(game->statusWindow);
	delwin(game->gameWindow);
	delwin(game->textWindow);
	endwin();									/* free every windows buffer memory */
}
