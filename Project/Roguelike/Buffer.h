#pragma once

#include "character.h"
#include "Map.h"
#include "tiles.h"

class Buffer {
public:
	WINDOW *statusWindow, *gameWindow, *textWindow;					/* Initialize game windows */
	void drawBorders(WINDOW * status, WINDOW * textBar);						/* draw borders */
	void drawGame(WINDOW * game, Map *map, Tile tile[], character *player);		/* Draw game state */
	void drawStatus(WINDOW * status, character * player);						/* Draw status window specific */
	void listCommands(WINDOW * text);									/* List available commands on text bar */
};
