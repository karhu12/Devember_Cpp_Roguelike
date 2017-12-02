#pragma once

#include "character.h"

class character;

class _buffer {
public:
	WINDOW *statusWindow, *gameWindow, *textWindow;										/* Initialize 3 windows for status,text and game */
	void drawBorders(WINDOW * status, WINDOW * textBar);								/* draw borders */
	void drawGame(WINDOW * game, int map[][AREA_MAX_WIDTH], character *player);			/* Draw game state */
	void drawStatus(WINDOW * status, character * player);								/* Draw status window specific */
};
