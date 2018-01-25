#include "stdafx.h"
#include "state.h"

int main() { 
	srand(time(NULL));
	state game;										/* Initialize game state object */
	game.gameLoop();
	return 0;
}