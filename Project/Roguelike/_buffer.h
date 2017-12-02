#pragma once

#include "state.h"
#include "character.h"

class state;
class character;

class _buffer {
public:
	WINDOW *statusWindow, *gameWindow, *textWindow;										/* Initialize 3 windows for status,text and game */
	void drawBorders(WINDOW * status, WINDOW * textBar);								/* draw borders */
	void bufferRelease(state *game);													/* Release buffer memory */
	void drawGame(WINDOW * game, int map[][AREA_MAX_WIDTH], character *player);			/* Draw game state */
	void drawStatus(WINDOW * status, character * player);								/* Draw status window specific */
};
