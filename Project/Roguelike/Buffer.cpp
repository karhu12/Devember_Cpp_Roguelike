#include "stdafx.h"
#include "buffer.h"

void Buffer::drawGame(Map *map, Tile tile[], Player *player) {
	int x;
	for (int i = 0; i < AREA_MAX_HEIGHT; i++) {					/* Nestedloop to start from 0,0 and end at last coordinate*/
		for (int j = 0; j < AREA_MAX_WIDTH; j++) {
			if (i == player->yPos && j == player->xPos) {		/* If position is players position, draw player */
				x = returnColorPair(player->foregroundColor, tile[map->area[i][j]].backgroundColor);
				wattron(gameWindow, A_BOLD);
				wattron(gameWindow, COLOR_PAIR(x));
				mvwaddch(gameWindow, i, j, player->playerCharacter);
				wattroff(gameWindow, COLOR_PAIR(x));
				wattroff(gameWindow, A_BOLD);
			}
			else {												/* Else draw tile */
				x = returnColorPair(tile[map->area[i][j]].foregroundColor, tile[map->area[i][j]].backgroundColor);
				wattron(gameWindow, A_BOLD);
				wattron(gameWindow, COLOR_PAIR(x));
				mvwaddch(gameWindow, i, j, tile[map->area[i][j]].tileCharacter);
				wattroff(gameWindow, COLOR_PAIR(x));
				wattroff(gameWindow, A_BOLD);
			}
		}
	}
	wrefresh(gameWindow);									/* Refresh buffer */
}

void Buffer::createBuffer() {
	statusWindow = newwin(STATUS_SCREEN_HEIGHT, STATUS_SCREEN_WIDTH, 0, 0);
	gameWindow = newwin(AREA_MAX_HEIGHT, AREA_MAX_WIDTH, 1, STATUS_SCREEN_WIDTH + 1);
	textWindow = newwin(TEXT_SCREEN_HEIGHT, TEXT_SCREEN_WIDTH, STATUS_SCREEN_HEIGHT, 0);
}

void Buffer::releaseBuffer() {
	delwin(statusWindow);
	delwin(gameWindow);
	delwin(textWindow);
	endwin();									/* free every windows buffer memory */
}

void Buffer::listCommands() {
	noecho();
	attron(A_BOLD);
	mvwprintw(textWindow, 1, 2, "COMMANDS | ");
	wColorOn(textWindow, COLOR_GREEN, COLOR_BLACK);
	wprintw(textWindow, "w / a / s / d ");
	wColorOff(textWindow, COLOR_GREEN, COLOR_BLACK);
	wprintw(textWindow, "for player movements | ");
	wColorOn(textWindow, COLOR_RED, COLOR_BLACK);
	wprintw(textWindow, "q");
	wColorOff(textWindow, COLOR_RED, COLOR_BLACK);
	wprintw(textWindow, " to quit | ");
	mvwprintw(textWindow, 3, 2, "Press any key to return ");
	wgetch(textWindow);
	wclear(textWindow);
	echo();
}

void Buffer::drawStatus(Player * player) {	/* Draw player status */
	wclear(statusWindow);
	box(statusWindow, ACS_VLINE, ACS_HLINE);
	wattron(statusWindow, A_BOLD);
	mvwprintw(statusWindow, 2, 2, "PLAYER");
	wColorOn(statusWindow, COLOR_RED, COLOR_BLACK);
	mvwprintw(statusWindow, 4, 2, "HP");
	wColorOff(statusWindow, COLOR_RED, COLOR_BLACK);
	wColorOn(statusWindow, COLOR_YELLOW, COLOR_BLACK);
	mvwprintw(statusWindow, 5, 2, "LEVEL");
	mvwprintw(statusWindow, 6, 2, "EXP");
	wColorOff(statusWindow, COLOR_YELLOW, COLOR_BLACK);
	mvwprintw(statusWindow, 4, 10, "%d", player->health);
	mvwprintw(statusWindow, 5, 10, "%d", player->level);
	mvwprintw(statusWindow, 6, 10, "%d", player->experience);
	mvwprintw(statusWindow, 8, 2, "ATTRIBUTES");
	wColorOn(statusWindow, COLOR_RED, COLOR_RED);
	mvwprintw(statusWindow, 10, 2, "STR");
	wColorOff(statusWindow, COLOR_RED, COLOR_RED);
	wColorOn(statusWindow, COLOR_GREEN, COLOR_GREEN);
	mvwprintw(statusWindow, 11, 2, "DEX");
	wColorOff(statusWindow, COLOR_GREEN, COLOR_GREEN);
	wColorOn(statusWindow, COLOR_BLUE, COLOR_BLUE);
	mvwprintw(statusWindow, 12, 2, "INT");
	wColorOff(statusWindow, COLOR_BLUE, COLOR_BLUE);
	mvwprintw(statusWindow, 10, 10, "%d", player->strength);
	mvwprintw(statusWindow, 11, 10, "%d", player->dexterity);
	mvwprintw(statusWindow, 12, 10, "%d", player->intelligence);
	wattroff(statusWindow, A_BOLD);
	wrefresh(statusWindow);
}

void Buffer::drawText() {
	wclear(textWindow);
	box(textWindow, ACS_VLINE, ACS_HLINE);
	wrefresh(textWindow);
}

void Buffer::drawEncounter() {
	wclear(gameWindow);
	box(gameWindow, ACS_VLINE, ACS_HLINE);
	wmove(gameWindow, 24, 1);
	whline(gameWindow, ACS_HLINE, AREA_MAX_WIDTH - 2);
	wrefresh(gameWindow);
}

void Buffer::listEnemies(Enemy *enemy, short enemys) {
	wmove(gameWindow, 2, 2);
	for (int i = 0; i < enemys; i++) {				/* List enemies */
		wprintw(gameWindow, "Enemy");
		wColorOn(gameWindow, COLOR_CYAN, COLOR_BLACK);
		wprintw(gameWindow, " %3d ", i + 1);
		wColorOff(gameWindow, COLOR_CYAN, COLOR_BLACK);
	}
	wmove(gameWindow, 3, 2);
	for (int i = 0; i < enemys; i++) {
		wprintw(gameWindow, "Health");
		wColorOn(gameWindow, COLOR_RED, COLOR_BLACK);
		wprintw(gameWindow, " %d ", enemy[i].health);
		wColorOff(gameWindow, COLOR_RED, COLOR_BLACK);
	}
}

void Buffer::listItems(std::vector<Item *> items) {
	for (auto i : items) {
		switch (i->getType()) {
		case WEAPON:

			break;
		case CONSUMABLE:

			break;
		default:
			break;
		}
	}
}