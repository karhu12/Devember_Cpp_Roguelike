#include "stdafx.h"
#include "state.h"
#include "character.h"
#include "Map.h"
#include "tiles.h"

void state::bufferCreate(state *game) {
	game->statusWindow = newwin(20, 20, 5, 0);
	game->gameWindow = newwin(19, 61, 6, 23);
	game->textWindow = newwin(5, 85, 0, 0);
}

void state::bufferRelease(state *game) {
	delwin(game->statusWindow);
	delwin(game->gameWindow);
	delwin(game->textWindow);
	endwin();									/* free every windows buffer memory */
}

void state::command(char cmd, character *player, Map map, Tile tile[]) {
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