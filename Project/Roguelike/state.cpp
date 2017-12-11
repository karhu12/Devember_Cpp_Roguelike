#include "stdafx.h"
#include "state.h"
#include "character.h"
#include "Map.h"
#include "tiles.h"
#include "general.h"
#include "enemy.h"

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
		this->lastCommand = "Movement";
	}
	else if (cmd == 'h') {
		this->listCommands();
		this->lastCommand = "Help";
	}
	else if (cmd == 'q') {
		this->status = false;
		this->lastCommand = "Quit";

	}
}

void state::enemyEncounter() {
	box(this->gameWindow, ACS_VLINE, ACS_HLINE);			/* Start by drawing empty boxed field */
	for (int i = 1; i < AREA_MAX_HEIGHT - 1; i++) {
		for (int j = 1; j < AREA_MAX_WIDTH - 1; j++) {
			mvwaddch(this->gameWindow, i, j, ' ');
		}
	}
	short hitRoll;											/* Variable to store hit roll (1/100) */
	short enemys = randomNumber(1, 3);						/* Generate random number of enemies */
	Enemy *enemy = new Enemy[enemys];						/* Create enemy objects */
	for (int i = 0; i < enemys; i++)						/* And give the objects initial values */
		enemy[i].enemyValues();
	bool encounter = true;									/* Boolean for encounter loop */

	mvwprintw(this->textWindow, 1, 1, "You are ambushed by %d enemies!", enemys);
	wrefresh(this->gameWindow);
	wgetch(this->textWindow);
	while (encounter) {										/* Encounter loop */
		bool playerTurn = true;
		while (playerTurn) {
			//What does the player want to do?
			//input
			//check if input valid
			//execute
			playerTurn = false;
		}
		
		for (int i = 0; i < enemys; i++) {					/* enemy i's attack turn */
			//Roll for random hit
			//if hits random roll damage min/max damage
			//if player is dead break loop and set game state to lost
		}

		//if all enemies are dead / player is dead break loop
		encounter = false;
	}


	delete enemy;
}