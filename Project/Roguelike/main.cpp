#include "stdafx.h"
#include "character.h"
#include "state.h"
#include "Map.h"
#include "general.h"

int main() {
	state game;										/* Initialize game state object */
	character player = character::createPlayer();	/* Create player object with certain parameters */
	Map map = Map::createMap();						/* Create map object */
	Tile tile[MAX_TILES];
	defineTiles(tile);								/* Create tile struct array with all known tile values */

	char input;
	initscr();										/* Start curses */
	curs_set(0);									/* Hide cursor */
	resize_term(37, 91);							/* Set initial window size */
	int ind = 1;
	if (has_colors() == TRUE) {						/* Initialize all possible color pairs */
		start_color();
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j <= 8; j++) {
				init_pair(ind, i, j);
				ind++;
			}
		}
	}



	game.bufferCreate(&game);						/* Create game windows of approppriate size */
	game.status = true;
	while (game.status == true) {					/* game loop which updates every input */
		game.drawBorders(game.statusWindow, game.textWindow);
		game.drawStatus(game.statusWindow, &player);
		game.drawGame(game.gameWindow, map, tile, &player);
		mvwprintw(game.textWindow, 1, 2, "X : %2d  Y : %2d", player.xPos, player.yPos);
		input = mvwgetch(game.textWindow, 3, 2);

		if (input == 'q')
			game.status = false;
		else
			player.playerMovement(map, tile, input);
	}
	game.bufferRelease(&game);
													/* Release window buffer memory */
	return 0;
}