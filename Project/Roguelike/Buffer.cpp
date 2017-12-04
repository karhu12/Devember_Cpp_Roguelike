#include "stdafx.h"
#include "Buffer.h"
#include "general.h"

void Buffer::drawBorders(WINDOW * status, WINDOW * text) {
	box(status, ACS_VLINE, ACS_HLINE);
	box(text, ACS_VLINE, ACS_HLINE);							/* draw borders to window buffers */
	wrefresh(status);
	wrefresh(text);												/* Refresh draws buffer to the actual screen */
}

void Buffer::drawGame(WINDOW * game, Map map, Tile tile[], character *player) {
	int x;
	for (int i = 0; i < AREA_MAX_HEIGHT; i++) {					/* Nestedloop to start from 0,0 and end at last coordinate*/
		for (int j = 0; j < AREA_MAX_WIDTH; j++) {
			if (i == player->yPos && j == player->xPos) {		/* If position is players position, draw player */
				x = returnColorPair(player->foregroundColor, tile[map.area[i][j]].backgroundColor);
				wattron(game, A_BOLD);
				wattron(game, COLOR_PAIR(x));
				mvwaddch(game, i, j, player->playerCharacter);
				wattroff(game, COLOR_PAIR(x));
				wattroff(game, A_BOLD);
			}
			else {												/* Else draw tile */
				x = returnColorPair(tile[map.area[i][j]].foregroundColor, tile[map.area[i][j]].backgroundColor);
				wattron(game, A_BOLD);
				wattron(game, COLOR_PAIR(x));
				mvwaddch(game, i, j, tile[map.area[i][j]].tileCharacter);
				wattroff(game, COLOR_PAIR(x));
				wattroff(game, A_BOLD);
			}
		}
	}
	wrefresh(game);												/* Refresh buffer */
}

void Buffer::listCommands(WINDOW * text) {
	noecho();
	attron(A_BOLD);
	mvwprintw(text, 1, 2, "COMMANDS | ");
	wColorOn(text, COLOR_GREEN, COLOR_BLACK);
	wprintw(text, "w / a / s / d ");
	wColorOff(text, COLOR_GREEN, COLOR_BLACK);
	wprintw(text, "for player movements | ");
	wColorOn(text, COLOR_RED, COLOR_BLACK);
	wprintw(text, "q"); 
	wColorOff(text, COLOR_RED, COLOR_BLACK);
	wprintw(text, " to quit | ");
	mvwprintw(text, 3, 2, "Press any key to return ");
	wgetch(text);
	wclear(text);
	echo();
}

void Buffer::drawStatus(WINDOW * status, character * player) {	/* Draw player status */
	wattron(status, A_BOLD);
	mvwprintw(status, 2, 2, "PLAYER");
	wColorOn(status, COLOR_RED, COLOR_BLACK);
	mvwprintw(status, 4, 2, "HP");
	wColorOff(status, COLOR_RED, COLOR_BLACK);
	wColorOn(status, COLOR_YELLOW, COLOR_BLACK);
	mvwprintw(status, 5, 2, "LEVEL");
	mvwprintw(status, 6, 2, "EXP");
	wColorOff(status, COLOR_YELLOW, COLOR_BLACK);
	mvwprintw(status, 4, 10, "%d", player->health);
	mvwprintw(status, 5, 10, "%d", player->level);
	mvwprintw(status, 6, 10, "%d", player->experience);
	mvwprintw(status, 8, 2, "ATTRIBUTES");
	wColorOn(status, COLOR_RED, COLOR_RED);
	mvwprintw(status, 10, 2, "STR");
	wColorOff(status, COLOR_RED, COLOR_RED);
	wColorOn(status, COLOR_GREEN, COLOR_GREEN);
	mvwprintw(status, 11, 2, "DEX");
	wColorOff(status, COLOR_GREEN, COLOR_GREEN);
	wColorOn(status, COLOR_BLUE, COLOR_BLUE);
	mvwprintw(status, 12, 2, "INT");
	wColorOff(status, COLOR_BLUE, COLOR_BLUE);
	mvwprintw(status, 10, 10, "%d", player->strength);
	mvwprintw(status, 11, 10, "%d", player->dexterity);
	mvwprintw(status, 12, 10, "%d", player->intelligence);
	wattroff(status, A_BOLD);
	wrefresh(status);
}