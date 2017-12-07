#include "stdafx.h"
#include "character.h"
#include "state.h"
#include "Map.h"
#include "general.h"

int main() {
	srand(time(NULL));
	state game;										/* Initialize game state object */
	character player = character::createPlayer();	/* Create player object with certain parameters */
	std::map<int, Map *> *mapOfLevels 
	= new std::map<int, Map *>;						/* Dynamic map pointer that stores map pointers*/
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
		if (tile[map->area[player.yPos][player.xPos]].exit == true) {
			for (int i = 0; i < 2; i++) {
				if (map->exit[i].xPos == player.xPos && map->exit[i].yPos == player.yPos) {
					if (map->exit[i].link == 0) {
						map = map->newMap(map, mapOfLevels, i);
						player.yPos = map->exit[0].yPos;
						player.xPos = map->exit[0].xPos;
						mvwprintw(game.textWindow, 1, 1, "New map created...");
						break;
					}
					else if (map->exit[i].link != 0) {
						map = map->loadMap(map, mapOfLevels, i);
						mvwprintw(game.textWindow, 1, 1, "Loading existing map...");
						break;
					}
				}
			}
		}
	}
	game.bufferRelease(&game);
													/* Release window buffer memory */
	return 0;
}