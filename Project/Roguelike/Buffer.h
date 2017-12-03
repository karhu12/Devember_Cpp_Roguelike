#pragma once

#include "character.h"
#include "Map.h"
#include "structs.h"

class Buffer {
public:
	WINDOW *statusWindow, *gameWindow, *textWindow;										/* Initialize 3 windows for status,text and game */
	void drawBorders(WINDOW * status, WINDOW * textBar);								/* draw borders */
	void drawGame(WINDOW * game, Map map, Tile tile[], character *player);			/* Draw game state */
	void drawStatus(WINDOW * status, character * player);								/* Draw status window specific */
};