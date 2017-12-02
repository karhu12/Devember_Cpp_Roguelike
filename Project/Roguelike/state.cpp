#include "stdafx.h"
#include "state.h"

void state::bufferCreate(state *game) {
	game->statusWindow = newwin(20, 20, 5, 0);
	game->gameWindow = newwin(19, 61, 6, 23);
	game->textWindow = newwin(5, 85, 0, 0);
}
