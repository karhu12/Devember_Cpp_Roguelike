#include "stdafx.h"
#include "state.h"
#include "character.h"
#include "Map.h"
#include "tiles.h"

void state::bufferCreate(state *game) {
	game->statusWindow = newwin(STATUS_SCREEN_HEIGHT, STATUS_SCREEN_WIDTH, 0, 0);
	game->gameWindow = newwin(AREA_MAX_HEIGHT, AREA_MAX_WIDTH, 1, STATUS_SCREEN_WIDTH + 1);
	game->textWindow = newwin(TEXT_SCREEN_HEIGHT, TEXT_SCREEN_WIDTH, STATUS_SCREEN_HEIGHT, 0);
}

void state::bufferRelease(state *game) {
	delwin(game->statusWindow);
	delwin(game->gameWindow);
	delwin(game->textWindow);
	endwin();									/* free every windows buffer memory */
}

void state::command(char cmd, character *player, Map *map, Tile tile[]) {
	if (cmd == 'w' || cmd == 'a' || cmd == 's' || cmd == 'd') {
		player->playerMovement(map,tile,cmd);
	}
	else if (cmd == 'h') {
		this->listCommands(this->textWindow);
	}
	else if (cmd == 'q') {
		this->status = false;
	}
}