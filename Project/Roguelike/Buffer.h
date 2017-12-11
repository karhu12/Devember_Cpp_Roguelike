#pragma once

#include "character.h"
#include "Map.h"
#include "tiles.h"

class Buffer {
public:
	WINDOW *statusWindow, *gameWindow, *textWindow;				/* Initialize game windows */
	void drawBorders();											/* draw borders */
	void drawGame(Map *map, Tile tile[], character *player);	/* Draw game state */
	void drawStatus(character * player);						/* Draw status window specific */
	void listCommands();										/* List available commands on text bar */
};
