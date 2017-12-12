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
		if (player->playerMovement(map, tile, cmd) == 1)
			this->lastCommand = "Movement";
		else
			this->lastCommand = "Invalid movement";
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

void state::enemyEncounter(character *player) {
	short roll;												/* Variable to store hit roll (1/100) */
	short enemys = randomNumber(1, 3);						/* Generate random number of enemies */
	Enemy *enemy = new Enemy[enemys];						/* Create enemy objects */
	for (int i = 0; i < enemys; i++)						/* And give the objects initial values */
		enemy[i].enemyValues();
	bool encounter = true;									/* Boolean for encounter loop */

	mvwprintw(this->textWindow, 1, 1, "You are ambushed by %d enemy!", enemys);
	wprintw(this->textWindow, " Prepare to fight...");
	mvwprintw(this->textWindow, 3, 1, "Press any key to continue...");
	wgetch(this->textWindow);

	while (encounter) {										/* Encounter loop */
		bool validInput, validAttack;
		bool attemptedFlee = false, fled = false;			/* Booleans for checks */
		do {												/* Player begins combat */
			this->drawText();								/* Update screen boxes */
			this->drawStatus(player);
			mvwprintw(this->textWindow, 3, 1, "What do you do > ");
			char action = wgetch(this->textWindow);			/* Prompt players choise and check if its valid */
			int actionToInt;
			if (action == 'a' || action == 'A') {			/* Attack selection */
				do {
					this->drawText();
					mvwprintw(this->textWindow, 1, 1, "Choose target to attack");
					wmove(this->textWindow, 2, 1);
					for (int i = 0; i < enemys; i++) {		/* List enemies */
						wprintw(this->textWindow, "Enemy");
						wColorOn(this->textWindow, COLOR_CYAN, COLOR_BLACK);
						wprintw(this->textWindow, " %3d ", i + 1);
						wColorOff(this->textWindow, COLOR_CYAN, COLOR_BLACK);
					}
					wmove(this->textWindow, 3, 1);
					for (int i = 0; i < enemys; i++) {
						wprintw(this->textWindow, "Health");
						wColorOn(this->textWindow, COLOR_RED, COLOR_BLACK);
						wprintw(this->textWindow, " %d ", enemy[i].health);
						wColorOff(this->textWindow, COLOR_RED, COLOR_BLACK);
					}
					action = mvwgetch(this->textWindow, 3, 1);
					actionToInt = action - 48;				/* Turn char into corresponding int and check if its valid */
					if (actionToInt > 0 && actionToInt <= enemys) {
						if (enemy[actionToInt - 1].alive == true) {
							validAttack = true;
						}
						else {
							this->drawText();
							mvwprintw(this->textWindow, 1, 1, "You can't attack enemy that is dead!");
							mvwprintw(this->textWindow, 3, 1, "Press any key to continue...");
							wgetch(this->textWindow);
							validAttack = false;
						}
					}
					else {
						this->drawText();
						mvwprintw(this->textWindow, 1, 1, "You can't attack unlisted enemies!");
						mvwprintw(this->textWindow, 3, 1, "Press any key to continue...");
						wgetch(this->textWindow);
						validAttack = false;
					}
				} while (!validAttack);

				roll = randomNumber(player->minDamage, player->maxDamage);
				this->drawText();
				mvwprintw(this->textWindow, 1, 1, "You hit enemy %d...", actionToInt);
				wgetch(this->textWindow);
				this->drawText();
				enemy[actionToInt - 1].health -= roll;
				if (enemy[actionToInt - 1].health <= 0) {
					enemy[actionToInt - 1].alive = false;
					player->experience += enemy[actionToInt - 1].experienceGiven;
					mvwprintw(this->textWindow, 1, 1, "Enemy dies! It grants you %d experience!", enemy[actionToInt - 1].experienceGiven);
					mvwprintw(this->textWindow, 3, 1, "Press any key to continue...");
					wgetch(this->textWindow);
				}
				else {
					mvwprintw(this->textWindow, 1, 1, "You deal %d damage but the enemy still stands", roll);
					mvwprintw(this->textWindow, 3, 1, "Press any key to continue...");
					wgetch(this->textWindow);
				}
				validInput = true;
			}
			else if (action == 'f' || action == 'F') {			/* Attempt to flee */
				if (!attemptedFlee) {
					this->drawText();
					mvwprintw(this->textWindow, 1, 1, "Attempting to flee...");
					if (!attemptedFlee) {						/* If you have not tried fleeing before */
						roll = randomNumber(1, 100);
						if (roll >= 75) {						/* 25 % chance to flee */
							mvwprintw(this->textWindow, 2, 1, "Success! You flee successfully...");
							fled = true;
							encounter = false;
							validInput = true;
						}
						else {
							mvwprintw(this->textWindow, 2, 1, "Your flee attempt fails... You cant attempt fleeing again...");
							attemptedFlee = true;
							validInput = false;
						}
					}
				}
				else {
					this->drawText();
					mvwprintw(this->textWindow, 1, 1, "I cant attempt fleeing again!");
					validInput = false;
				}
				mvwprintw(this->textWindow, 3, 1, "Press any key to continue...");
				wgetch(this->textWindow);
			}
			else if (action == 'h' || action == 'H') {		/* Lookup commands */
				this->drawText();
				mvwprintw(this->textWindow, 1, 1, "Commands");
				mvwprintw(this->textWindow, 2, 1, "'A' to Attack, 'F' to flee");
				mvwprintw(this->textWindow, 3, 1, "Press any key to continue...");
				wgetch(this->textWindow);
				validInput = false;
			}
			else {											/* Else invalid input */
				this->drawText();
				mvwprintw(this->textWindow, 1, 1, "Invalid command! Check 'H' for commands");
				wrefresh(this->textWindow);
				validInput = false;
			}
		} while (!validInput);								/* Valid input if it ends player turn */

		int enemyCounter = 0;							
		for (int i = 0; i < enemys; i++) {					/* Check if all enemies are dead before enemy turns */
			if (!enemy[i].alive) enemyCounter++;
			if (enemyCounter == enemys) encounter = false;
		}

		if (encounter) {									/* If encounter is still active enemy turn starts*/
			this->drawText();
			mvwprintw(this->textWindow, 1, 1, "Enemy's turn");
			mvwprintw(this->textWindow, 3, 1, "Press any key to continue...");
			wgetch(this->textWindow);
			this->drawText();
			for (int i = 0; i < enemys; i++) {				/* enemy i's attack turn */
				if (enemy[i].alive) {						/* if enemy is alive play his turn else do not */
					roll = randomNumber(1, 100);
					if (roll > enemy[i].accuracy) {			/* If enemy i's roll is higher than his accuracy, hit */
						roll = randomNumber(enemy[i].minDamage, enemy[i].maxDamage);
						player->health -= roll;
						mvwprintw(this->textWindow, 1, 1, "Enemy %d hits player for %d damage!", i + 1, roll);
						mvwprintw(this->textWindow, 3, 1, "Press any key to continue...");
						wgetch(this->textWindow);
					}
					else {
						mvwprintw(this->textWindow, 1, 1, "Enemy %d misses player!", i + 1);
						mvwprintw(this->textWindow, 3, 1, "Press any key to continue...");
						wgetch(this->textWindow);
					}
				}
			}
		}
	}
	delete enemy;											/* Delete enemy objects */
}