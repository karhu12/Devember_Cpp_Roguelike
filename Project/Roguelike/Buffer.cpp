#include "stdafx.h"
#include "Buffer.h"
#include "general.h"

void Buffer::drawBorders() {
	box(this->statusWindow, ACS_VLINE, ACS_HLINE);
	box(this->textWindow, ACS_VLINE, ACS_HLINE);				/* draw borders to window buffers */
	wrefresh(this->statusWindow);
	wrefresh(this->textWindow);									/* Refresh draws buffer to the actual screen */
}

void Buffer::drawGame(Map *map, Tile tile[], character *player) {
	int x;
	for (int i = 0; i < AREA_MAX_HEIGHT; i++) {					/* Nestedloop to start from 0,0 and end at last coordinate*/
		for (int j = 0; j < AREA_MAX_WIDTH; j++) {
			if (i == player->yPos && j == player->xPos) {		/* If position is players position, draw player */
				x = returnColorPair(player->foregroundColor, tile[map->area[i][j]].backgroundColor);
				wattron(this->gameWindow, A_BOLD);
				wattron(this->gameWindow, COLOR_PAIR(x));
				mvwaddch(this->gameWindow, i, j, player->playerCharacter);
				wattroff(this->gameWindow, COLOR_PAIR(x));
				wattroff(this->gameWindow, A_BOLD);
			}
			else {												/* Else draw tile */
				x = returnColorPair(tile[map->area[i][j]].foregroundColor, tile[map->area[i][j]].backgroundColor);
				wattron(this->gameWindow, A_BOLD);
				wattron(this->gameWindow, COLOR_PAIR(x));
				mvwaddch(this->gameWindow, i, j, tile[map->area[i][j]].tileCharacter);
				wattroff(this->gameWindow, COLOR_PAIR(x));
				wattroff(this->gameWindow, A_BOLD);
			}
		}
	}
	wrefresh(this->gameWindow);									/* Refresh buffer */
}

void Buffer::listCommands() {
	noecho();
	attron(A_BOLD);
	mvwprintw(this->textWindow, 1, 2, "COMMANDS | ");
	wColorOn(this->textWindow, COLOR_GREEN, COLOR_BLACK);
	wprintw(this->textWindow, "w / a / s / d ");
	wColorOff(this->textWindow, COLOR_GREEN, COLOR_BLACK);
	wprintw(this->textWindow, "for player movements | ");
	wColorOn(this->textWindow, COLOR_RED, COLOR_BLACK);
	wprintw(this->textWindow, "q");
	wColorOff(this->textWindow, COLOR_RED, COLOR_BLACK);
	wprintw(this->textWindow, " to quit | ");
	mvwprintw(this->textWindow, 3, 2, "Press any key to return ");
	wgetch(this->textWindow);
	wclear(this->textWindow);
	echo();
}

void Buffer::drawStatus(character * player) {	/* Draw player status */
	wattron(this->statusWindow, A_BOLD);
	mvwprintw(this->statusWindow, 2, 2, "PLAYER");
	wColorOn(this->statusWindow, COLOR_RED, COLOR_BLACK);
	mvwprintw(this->statusWindow, 4, 2, "HP");
	wColorOff(this->statusWindow, COLOR_RED, COLOR_BLACK);
	wColorOn(this->statusWindow, COLOR_YELLOW, COLOR_BLACK);
	mvwprintw(this->statusWindow, 5, 2, "LEVEL");
	mvwprintw(this->statusWindow, 6, 2, "EXP");
	wColorOff(this->statusWindow, COLOR_YELLOW, COLOR_BLACK);
	mvwprintw(this->statusWindow, 4, 10, "%d", player->health);
	mvwprintw(this->statusWindow, 5, 10, "%d", player->level);
	mvwprintw(this->statusWindow, 6, 10, "%d", player->experience);
	mvwprintw(this->statusWindow, 8, 2, "ATTRIBUTES");
	wColorOn(this->statusWindow, COLOR_RED, COLOR_RED);
	mvwprintw(this->statusWindow, 10, 2, "STR");
	wColorOff(this->statusWindow, COLOR_RED, COLOR_RED);
	wColorOn(this->statusWindow, COLOR_GREEN, COLOR_GREEN);
	mvwprintw(this->statusWindow, 11, 2, "DEX");
	wColorOff(this->statusWindow, COLOR_GREEN, COLOR_GREEN);
	wColorOn(this->statusWindow, COLOR_BLUE, COLOR_BLUE);
	mvwprintw(this->statusWindow, 12, 2, "INT");
	wColorOff(this->statusWindow, COLOR_BLUE, COLOR_BLUE);
	mvwprintw(this->statusWindow, 10, 10, "%d", player->strength);
	mvwprintw(this->statusWindow, 11, 10, "%d", player->dexterity);
	mvwprintw(this->statusWindow, 12, 10, "%d", player->intelligence);
	wattroff(this->statusWindow, A_BOLD);
	wrefresh(this->statusWindow);
}