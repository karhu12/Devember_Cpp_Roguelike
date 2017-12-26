#include "stdafx.h"
#include "character.h"
#include "state.h"
#include "Map.h"
#include "general.h"
#include "enemy.h"

int main() { 
	srand((unsigned int)time(NULL));
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
	while (game.status == true) {										/* game loop which updates every input */
		game.drawText();												/* Draw text window content */
		game.drawStatus(&player);										/* Draw all status window content */
		game.drawGame(map, tile, &player);								/* Draw game screen depending on current map */
		player.input = mvwgetch(game.textWindow, 3, 1);					/* Get input from player */
		game.command(player.input, &player, map, tile);					/* Execute command depending on input */
		if (tile[map->area[player.yPos][player.xPos]].exit == true) {	/* If player steps into exit */
			map = map->returnNewArea(&player, mapOfLevels, game);		/* New zone is created or old one loaded */
		}
		else if (tile[map->area[player.yPos][player.xPos]].tileName == "Item") {
			Items *item = new Items;									/* When player finds item spawn it generates new item and stores it in item map */
			item->generateItem(randomNumber(MIN_ITEM, MAX_ITEM));
			(player.itemMap)[player.items] = item;
		}
		else if (game.lastCommand == "Movement") {						/* On player movement chance to start random encounter */
			if (checkForEncounter() == true) {							/* If encounter happens */
				game.drawGame(map, tile, &player);						/* Redraw map with player on new position*/
				game.enemyEncounter(&player);							/* Start encounter */
			}
		}
	}
	game.bufferRelease(&game);											/* Release window buffer memory */
	return 0;
}