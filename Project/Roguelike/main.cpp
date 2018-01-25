#include "stdafx.h"
#include "character.h"
#include "state.h"
#include "Map.h"
#include "general.h"
#include "enemy.h"

int main() { 
	srand((unsigned int)time(NULL));
	state game;										/* Initialize game state object */
	game.gameLoop();
	return 0;
}