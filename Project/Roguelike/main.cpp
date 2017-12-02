#include "stdafx.h"
#include "character.h"
#include "state.h"


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