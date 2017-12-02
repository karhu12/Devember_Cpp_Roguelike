#include "stdafx.h"

class state;

class character {
public:
	short health, level, experience;
	int xPos, yPos;
	void playerMovement(character *ptr, char input);
	character createPlayer();
};

class _buffer{
public:
	WINDOW *statusWindow, *gameWindow, *textWindow;										/* Initialize 3 windows for status,text and game */	
	void drawBorders(WINDOW * status, WINDOW * textBar);								/* draw borders */
	void bufferRelease(state *game);													/* Release buffer memory */
	void drawGame(WINDOW * game, int map[][AREA_MAX_WIDTH], character *player);			/* Draw game state */
	void drawStatus(WINDOW * status, character * player);								/* Draw status window specific */
};


class state : public _buffer {
public:
	bool status;
	int map[AREA_MAX_HEIGHT][AREA_MAX_WIDTH];
	void bufferCreate(state *game);
	typedef struct tiles {

	};
};

int main() {
	state game;										/* Initialize game state object */
	character player = player.createPlayer();
	char input;
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
		init_pair(6, COLOR_CYAN, COLOR_GREEN);
	}

	game.status = true;

	for (int i = 0; i < AREA_MAX_HEIGHT; i++)
		for (int j = 0; j < AREA_MAX_WIDTH; j++)
			game.map[i][j] = 0;						/* Initialize map with no tile value (tiles not used yet) */

	game.bufferCreate(&game);						/* Create game windows of approppriate size */

	while (game.status == true) {
		game.drawBorders(game.statusWindow, game.textWindow);
		game.drawStatus(game.statusWindow, &player);
		game.drawGame(game.gameWindow, game.map, &player);				/* Buffer draw functions */

		mvwprintw(game.textWindow, 1, 2, "player x: %d	player y: %d", player.xPos, player.yPos);
		input = mvwgetch(game.textWindow, 3, 2);
		if (input == 'q')
			game.status = false;
		else 
			player.playerMovement(&player,input);
	}
													/* Release window buffer memory */
	game.bufferRelease(&game);
	return 0;
}

character character::createPlayer() {
	character player;
	player.level = 1;
	player.health = 100;
	player.experience = 0;
	player.xPos = 30;
	player.yPos = 9;
	return player;
}

void character::playerMovement(character *ptr,char input) {
	if (input == 'd' || input == 'D')
		if (ptr->xPos < AREA_MAX_WIDTH)
			ptr->xPos += 1;
	if (input == 'a' || input == 'A')
		if (ptr->xPos > 0)
			ptr->xPos -= 1;
	if (input == 'w' || input == 'W')
		if (ptr->yPos > 0)
			ptr->yPos -= 1;
	if (input == 's' || input == 'S')
		if (ptr->yPos < AREA_MAX_HEIGHT)
			ptr->yPos += 1;
}

void state::bufferCreate(state *game) {
	game->statusWindow = newwin(20, 20, 5, 0);
	game->gameWindow = newwin(19, 61, 6, 23);
	game->textWindow = newwin(5, 85, 0, 0);
}

void _buffer::drawBorders(WINDOW * status, WINDOW * text) {
	box(status, ACS_VLINE, ACS_HLINE);
	box(text, ACS_VLINE, ACS_HLINE);				/* draw borders to window buffers */
	wrefresh(status);
	wrefresh(text);									/* Refresh draws buffer to the actual screen */
}

void _buffer::drawGame(WINDOW * game, int map[][AREA_MAX_WIDTH], character *player) {
	for (int i = 0; i < AREA_MAX_HEIGHT+1; i++) {					/* Example of game field drawn from 0,0 coordinate */
		for (int j = 0; j < AREA_MAX_WIDTH+1; j++) {
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