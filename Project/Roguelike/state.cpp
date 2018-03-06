#include "stdafx.h"
#include "state.h"
#include "Player.h"
#include "Map.h"
#include "tiles.h"
#include "general.h"
#include "enemy.h"

state::state() { /* Create dynamic objects and map */
	map = new Map;
	player = new Player;
	buffer = new Buffer;
	mapOfLevels = new std::map<int, Map *>;
}

state::~state() {	/* Delete pointer memory and NULL them */
	delete map;
	delete mapOfLevels;
	delete player;
	delete buffer;
	map = nullptr;
	mapOfLevels = nullptr;
	player = nullptr;
	buffer = nullptr;
}

void state::initGame() {
	defineTiles(tile);								/* Create tile struct array with all known tile values */
	initscr();										/* Start curses */
	curs_set(0);									/* Hide cursor */
	resize_term(SCREEN_HEIGHT, SCREEN_WIDTH);		/* Set initial window size */
	buffer->createBuffer();							/* Creates 3 windows to buffer */
	initializeColors();								/* Start colors and initialize 64 color pairs */
	status = true;
}

void state::gameLoop() {
	initGame();															/* Initialize required assets for game*/
	while (getGameStatus()) {												/* game loop which updates every input */
		buffer->drawText();												/* Draw text window content */
		buffer->drawStatus(player);										/* Draw all status window content */
		buffer->drawGame(map, tile, player);							/* Draw game screen depending on current map */
		executeInput(player, map, tile);								/* Execute command depending on input */
		if (tile[map->area[player->yPos][player->xPos]].exit == true) {	/* If player steps into exit */
			map = map->returnNewArea(player, mapOfLevels);				/* New zone is created or old one loaded */
		}
		else if (tile[map->area[player->yPos][player->xPos]].tileName == "Item") {	/* If tile on player position is a tile generate new item */
			player->newItemToInventory();
			map->changeAreaToDefault(player->yPos, player->xPos);
		}
		else if (lastCommand == "Movement") {							/* On player movement chance to start random encounter */
			if (checkForEncounter()) {									/* If encounter happens */
				buffer->drawGame(map, tile, player);					/* Redraw map with player on new position*/
				enemyEncounter(player);									/* Start encounter */
			}
		}
	}
	buffer->releaseBuffer();											/* Release window buffers */
}

bool state::getGameStatus() {
	return status;
}

void state::executeInput(Player *player, Map *map, Tile tile[]) {
	char cmd = player->getPlayerInput(buffer);							/* Get player input */
	if (cmd == 'w' || cmd == 'a' || cmd == 's' || cmd == 'd') {			/* Depending on input execute certain actions */
		if (player->playerMovement(map, tile, cmd) == 1)
			lastCommand = "Movement";
		else
			lastCommand = "Invalid movement";
	}
	else if (cmd == 'h') {
		buffer->listCommands();
		lastCommand = "Help";
	}
	else if (cmd == 'q') {
		status = false;
		lastCommand = "Quit";
	}
	else if (cmd == 'i') {
		buffer->listItems(player);
		lastCommand = "Inventory";
	}
}



void state::enemyEncounter(Player *player) {
	short roll, damage;
	short enemys = randomNumber(1, 3);									/* Generate random number of enemies */
	Enemy *enemy = new Enemy[enemys];									/* Create enemy objects */
	bool encounter = true;												/* Boolean for encounter loop */

	mvwprintw(buffer->textWindow, 1, 1, "You are ambushed by %d enemy!", enemys);
	wprintw(buffer->textWindow, " Prepare to fight...");
	wrefresh(buffer->textWindow);
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));

	while (encounter) {													/* Encounter loop */
		bool validInput, validAttack, attemptedFlee = false, fled = false; /* Booleans for checks */
		do {															/* Player begins combat */
			buffer->drawEncounter();									/* Update screen boxes */
			buffer->drawStatus(player);
			mvwprintw(buffer->gameWindow, 25, 1, "What is your move > ");
			buffer->listEnemies(enemy, enemys);
			char action = wgetch(buffer->gameWindow);					/* Prompt players choise and check if its valid */
			int actionToInt;
			if (action == 'a' || action == 'A') {						/* Attack selection */
				do {
					buffer->drawEncounter();
					mvwprintw(buffer->gameWindow, 25, 1, "Choose target to attack");
					buffer->listEnemies(enemy, enemys);
					action = mvwgetch(buffer->gameWindow, 26, 1);
					actionToInt = action - 48;							/* Turn char into corresponding int and check if its valid */
					if (actionToInt > 0 && actionToInt <= enemys) {		/* If choise is one of the enemies */
						if (enemy[actionToInt - 1].alive == true) {		/* If selected enemy is still alive*/
							validAttack = true;
						}
						else {											/* Else cant attack */
							buffer->drawEncounter();
							mvwprintw(buffer->gameWindow, 25, 1, "You can't attack enemy that is dead!");
							mvwprintw(buffer->gameWindow, 26, 1, "Press any key to continue...");
							wgetch(buffer->gameWindow);
							validAttack = false;
						}
					}
					else {
						buffer->drawEncounter();
						mvwprintw(buffer->gameWindow, 25, 1, "You can't attack unlisted enemies!");
						mvwprintw(buffer->gameWindow, 26, 1, "Press any key to continue...");
						wgetch(buffer->gameWindow);
						validAttack = false;
					}
				} while (!validAttack);

				buffer->drawEncounter();
				mvwprintw(buffer->gameWindow, 25, 1, "You hit enemy %d...", actionToInt);
				buffer->listEnemies(enemy, enemys);
				wrefresh(buffer->gameWindow);
				std::this_thread::sleep_for(std::chrono::milliseconds(1000));
				if ((damage = player->playerAttack()) != 0) {
					buffer->drawEncounter();
					enemy[actionToInt - 1].health -= damage;
					if (enemy[actionToInt - 1].health <= 0) {
						enemy[actionToInt - 1].alive = false;
						player->experience += enemy[actionToInt - 1].experienceGiven;
						buffer->listEnemies(enemy, enemys);
						mvwprintw(buffer->gameWindow, 25, 1, "Enemy dies! It grants you %d experience!", enemy[actionToInt - 1].experienceGiven);
						buffer->drawStatus(player);
						wrefresh(buffer->gameWindow);
						std::this_thread::sleep_for(std::chrono::milliseconds(2000));
					}
					else {
						buffer->listEnemies(enemy, enemys);
						mvwprintw(buffer->gameWindow, 25, 1, "You deal %d damage but the enemy still stands", damage);
						wrefresh(buffer->gameWindow);
						std::this_thread::sleep_for(std::chrono::milliseconds(1500));
					}
				}
				else {
					buffer->listEnemies(enemy, enemys);
					mvwprintw(buffer->gameWindow, 25, 1, "Your attack misses...");
					wrefresh(buffer->gameWindow);
					std::this_thread::sleep_for(std::chrono::milliseconds(1000));
				}
				validInput = true;
			}
			else if (action == 'f' || action == 'F') {			/* Attempt to flee */
				if (!attemptedFlee) {
					buffer->drawEncounter();
					mvwprintw(buffer->gameWindow, 25, 1, "Attempting to flee...");
					wrefresh(buffer->gameWindow);
					std::this_thread::sleep_for(std::chrono::milliseconds(1000));
					buffer->drawEncounter();
					if (!attemptedFlee) {						/* If you have not tried fleeing before */
						roll = randomNumber(1, 100);
						if (roll >= 75) {						/* 25 % chance to flee */
							mvwprintw(buffer->gameWindow, 25, 1, "Success!");
							mvwprintw(buffer->gameWindow, 1, 1, "You flee successfully...");
							fled = true;
							encounter = false;
							validInput = true;
						}
						else {
							mvwprintw(buffer->gameWindow, 25, 1, "Fail...");
							mvwprintw(buffer->gameWindow, 1, 1, "Your flee attempt fails!");
							attemptedFlee = true;
							validInput = false;
						}
					}
				}
				else {
					buffer->drawEncounter();
					mvwprintw(buffer->gameWindow, 25, 1, "Attempting to flee...");
					mvwprintw(buffer->gameWindow, 1, 1, "I cant attempt fleeing again!");
					validInput = false;
				}
				mvwprintw(buffer->gameWindow, 2, 1, "Press any key to continue...");
				wgetch(buffer->gameWindow);
			}
			else if (action == 'h' || action == 'H') {		/* Lookup commands */
				buffer->drawEncounter();
				mvwprintw(buffer->gameWindow, 25, 1, "Help");
				mvwprintw(buffer->gameWindow, 1, 1, "Commands");
				mvwprintw(buffer->gameWindow, 2, 1, "'A' to Attack, 'F' to flee");
				mvwprintw(buffer->gameWindow, 3, 1, "Press any key to continue...");
				wgetch(buffer->gameWindow);
				validInput = false;
			}
			else {											/* Else invalid input */
				buffer->drawEncounter();
				mvwprintw(buffer->gameWindow, 1, 1, "Invalid command! Check 'H' for commands");
				wrefresh(buffer->gameWindow);
				validInput = false;
			}
		} while (!validInput);								/* Valid input if it ends player turn */

		int enemyCounter = 0;							
		for (int i = 0; i < enemys; i++) {					/* Check if all enemies are dead before enemy turns */
			if (!enemy[i].alive) enemyCounter++;
			if (enemyCounter == enemys) encounter = false;
		}

		if (encounter) {									/* If encounter is still active enemy turn starts*/
			buffer->drawEncounter();
			buffer->listEnemies(enemy, enemys);
			mvwprintw(buffer->gameWindow, 25, 1, "Enemy's turn");
			wrefresh(buffer->gameWindow);
			std::this_thread::sleep_for(std::chrono::milliseconds(2000));
			for (int i = 0; i < enemys; i++) {				/* enemy i's attack turn */
				buffer->drawEncounter();
				buffer->listEnemies(enemy, enemys);
				if (enemy[i].alive) {						/* if enemy is alive play his turn else do not */
					roll = randomNumber(1, 100);
					if (roll < enemy[i].accuracy) {			/* If enemy i's roll is lower than accuracy, hit */
						roll = randomNumber(enemy[i].minDamage, enemy[i].maxDamage);
						player->health -= roll;
						if (player->health > 0) {
							mvwprintw(buffer->gameWindow, 25, 1, "Enemy %d hits player for %d damage!", i + 1, roll);
							buffer->drawStatus(player);
							wrefresh(buffer->gameWindow);
							std::this_thread::sleep_for(std::chrono::milliseconds(1500));
						}
						else {
							mvwprintw(buffer->gameWindow, 25, 1, "Enemy %d hits player for %d damage!", i + 1, roll);
							mvwprintw(buffer->gameWindow, 26, 1, "Enemy has defeated you...");
							mvwprintw(buffer->gameWindow, 27, 1, "GAME OVER");
							buffer->drawStatus(player);
							wrefresh(buffer->gameWindow);
							encounter = false;
							status = false;
							std::this_thread::sleep_for(std::chrono::milliseconds(2000));
							break;
						}
					}
					else {
						mvwprintw(buffer->gameWindow, 25, 1, "Enemy %d misses player!", i + 1);
						wrefresh(buffer->gameWindow);
						std::this_thread::sleep_for(std::chrono::milliseconds(1000));
					}
				}
			}
		}
	}
	delete enemy;											/* Delete enemy objects */
	enemy = nullptr;
}