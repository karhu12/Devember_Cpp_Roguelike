#include "stdafx.h"
#include "character.h"
#include "state.h"
#include "Map.h"
#include "general.h"



int main() {
	srand(time(NULL));
	state game;										/* Initialize game state object */
	character player = character::createPlayer();	/* Create player object with certain parameters */
	std::map<std::string, Map *> mapOfLevel;
	Map *map = Map::createMap();					/* Create map object */
	Tile tile[MAX_TILES];
	defineTiles(tile);								/* Create tile struct array with all known tile values */

	initscr();										/* Start curses */
	curs_set(0);									/* Hide cursor */
	resize_term(SCREEN_HEIGHT, SCREEN_WIDTH);		/* Set initial window size */
	initializeColors();								/* Start colors and initialize 64 color pairs */
	game.bufferCreate(&game);						/* Create game windows of approppriate size */
	game.status = true;
	while (game.status == true) {									/* game loop which updates every input */
		game.drawBorders(game.statusWindow, game.textWindow);		/* Draw borders for status and text window */
		game.drawStatus(game.statusWindow, &player);				/* Draw all status window content */
		game.drawGame(game.gameWindow, map, tile, &player);			/* Draw game screen depending on current map */
		player.input = mvwgetch(game.textWindow, 3, 2);				/* Get input from player */
		game.command(player.input, &player, map, tile);				/* Execute command depending on input */
	}
	game.bufferRelease(&game);
													/* Release window buffer memory */
	return 0;
}