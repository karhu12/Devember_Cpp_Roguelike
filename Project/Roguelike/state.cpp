#include "stdafx.h"
#include "state.h"
#include "character.h"
#include "Map.h"
#include "tiles.h"
#include "general.h"
#include "enemy.h"

state::state() {
	map = new Map;									/* Create map object */
	mapOfLevels = new std::map<int, Map *>;			/* Dynamic map pointer that stores map pointers*/
}

state::~state() {
	delete map;
	delete mapOfLevels;
	map = NULL;
	mapOfLevels = NULL;
}

void state::gameLoop() {
	Tile tile[MAX_TILES];
	defineTiles(tile);								/* Create tile struct array with all known tile values */
	initscr();										/* Start curses */
	curs_set(0);									/* Hide cursor */
	resize_term(SCREEN_HEIGHT, SCREEN_WIDTH);		/* Set initial window size */
	initializeColors();								/* Start colors and initialize 64 color pairs */
	bufferCreate();							/* Create game windows of approppriate size */
	setStatus(true);
	while (getStatus() == true) {									/* game loop which updates every input */
		drawText();												/* Draw text window content */
		drawStatus(&player);										/* Draw all status window content */
		drawGame(map, tile, &player);								/* Draw game screen depending on current map */
		player.input = mvwgetch(textWindow, 3, 1);					/* Get input from player */
		command(player.input, &player, map, tile);					/* Execute command depending on input */
		if (tile[map->area[player.yPos][player.xPos]].exit == true) {	/* If player steps into exit */
			map = map->returnNewArea(&player, mapOfLevels);		/* New zone is created or old one loaded */
		}
		else if (tile[map->area[player.yPos][player.xPos]].tileName == "Item") {
			Items *item = new Items;									/* When player finds item spawn it generates new item and stores it in item map */
			item->generateItem(randomNumber(MIN_ITEM, MAX_ITEM));
			(player.itemMap)[player.items] = item;
		}
		else if (lastCommand == "Movement") {						/* On player movement chance to start random encounter */
			if (checkForEncounter() == true) {							/* If encounter happens */
				drawGame(map, tile, &player);						/* Redraw map with player on new position*/
				enemyEncounter(&player);							/* Start encounter */
			}
		}
	}
	bufferRelease();											/* Release window buffer memory */
}

void state::bufferCreate() {
	statusWindow = newwin(STATUS_SCREEN_HEIGHT, STATUS_SCREEN_WIDTH, 0, 0);
	gameWindow = newwin(AREA_MAX_HEIGHT, AREA_MAX_WIDTH, 1, STATUS_SCREEN_WIDTH + 1);
	textWindow = newwin(TEXT_SCREEN_HEIGHT, TEXT_SCREEN_WIDTH, STATUS_SCREEN_HEIGHT, 0);
}

void state::bufferRelease() {
	delwin(statusWindow);
	delwin(gameWindow);
	delwin(textWindow);
	endwin();									/* free every windows buffer memory */
}

bool state::getStatus() {
	return status;
}

void state::setStatus(bool newStatus) {
	status = newStatus;
}

void state::command(char cmd, character *player, Map *map, Tile tile[]) {
	if (cmd == 'w' || cmd == 'a' || cmd == 's' || cmd == 'd') {
		if (player->playerMovement(map, tile, cmd) == 1)
			lastCommand = "Movement";
		else
			lastCommand = "Invalid movement";
	}
	else if (cmd == 'h') {
		listCommands();
		lastCommand = "Help";
	}
	else if (cmd == 'q') {
		status = false;
		lastCommand = "Quit";
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
	wrefresh(this->textWindow);
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));

	while (encounter) {										/* Encounter loop */
		bool validInput, validAttack;
		bool attemptedFlee = false, fled = false;			/* Booleans for checks */
		do {												/* Player begins combat */
			this->drawEncounter();							/* Update screen boxes */
			this->drawStatus(player);
			mvwprintw(this->gameWindow, 25, 1, "What is your move > ");
			wmove(this->gameWindow, 2, 2);
			for (int i = 0; i < enemys; i++) {				/* List enemies */
				wprintw(this->gameWindow, "Enemy");
				wColorOn(this->gameWindow, COLOR_CYAN, COLOR_BLACK);
				wprintw(this->gameWindow, " %3d ", i + 1);
				wColorOff(this->gameWindow, COLOR_CYAN, COLOR_BLACK);
			}
			wmove(this->gameWindow, 3, 2);
			for (int i = 0; i < enemys; i++) {
				wprintw(this->gameWindow, "Health");
				wColorOn(this->gameWindow, COLOR_RED, COLOR_BLACK);
				wprintw(this->gameWindow, " %d ", enemy[i].health);
				wColorOff(this->gameWindow, COLOR_RED, COLOR_BLACK);
			}
			char action = wgetch(this->gameWindow);			/* Prompt players choise and check if its valid */
			int actionToInt;
			if (action == 'a' || action == 'A') {			/* Attack selection */
				do {
					this->drawEncounter();
					mvwprintw(this->gameWindow, 25, 1, "Choose target to attack");
					wmove(this->gameWindow, 2, 2);
					for (int i = 0; i < enemys; i++) {				/* List enemies again*/
						wprintw(this->gameWindow, "Enemy");
						wColorOn(this->gameWindow, COLOR_CYAN, COLOR_BLACK);
						wprintw(this->gameWindow, " %3d ", i + 1);
						wColorOff(this->gameWindow, COLOR_CYAN, COLOR_BLACK);
					}
					wmove(this->gameWindow, 3, 2);
					for (int i = 0; i < enemys; i++) {
						wprintw(this->gameWindow, "Health");
						wColorOn(this->gameWindow, COLOR_RED, COLOR_BLACK);
						wprintw(this->gameWindow, " %d ", enemy[i].health);
						wColorOff(this->gameWindow, COLOR_RED, COLOR_BLACK);
					}
					action = mvwgetch(this->gameWindow, 26, 1);
					actionToInt = action - 48;				/* Turn char into corresponding int and check if its valid */
					if (actionToInt > 0 && actionToInt <= enemys) {	/* If choise is one of the enemies */
						if (enemy[actionToInt - 1].alive == true) {	/* If selected enemy is still alive*/
							validAttack = true;
						}
						else {										/* Else cant attack */
							this->drawEncounter();
							mvwprintw(this->gameWindow, 25, 1, "You can't attack enemy that is dead!");
							mvwprintw(this->gameWindow, 26, 1, "Press any key to continue...");
							wgetch(this->gameWindow);
							validAttack = false;
						}
					}
					else {
						this->drawEncounter();
						mvwprintw(this->gameWindow, 25, 1, "You can't attack unlisted enemies!");
						mvwprintw(this->gameWindow, 26, 1, "Press any key to continue...");
						wgetch(this->gameWindow);
						validAttack = false;
					}
				} while (!validAttack);

				this->drawEncounter();
				mvwprintw(this->gameWindow, 25, 1, "You hit enemy %d...", actionToInt);
				wgetch(this->gameWindow);
				roll = randomNumber(1, 100);
				if (roll < player->accuracy + player->mainHand.accuracyBonus + player->offHand.accuracyBonus) {	/* If roll is lower than player accuracy it hits else miss */
					roll = randomNumber(player->minDamage,  (player->maxDamage + player->mainHand.damageBonus + player->offHand.damageBonus));
					roll += (player->strength * (player->mainHand.strMod + player->offHand.strMod));
					roll += (player->dexterity * (player->mainHand.dexMod + player->offHand.dexMod));
					roll += (player->intelligence * (player->mainHand.intMod + player->offHand.intMod));		/* Calculate damage from weapons mods and base stats */
					this->drawEncounter();
					enemy[actionToInt - 1].health -= roll;
					if (enemy[actionToInt - 1].health <= 0) {
						enemy[actionToInt - 1].alive = false;
						player->experience += enemy[actionToInt - 1].experienceGiven;
						mvwprintw(this->gameWindow, 25, 1, "Enemy dies! It grants you %d experience!", enemy[actionToInt - 1].experienceGiven);
						mvwprintw(this->gameWindow, 26, 1, "Press any key to continue...");
						wgetch(this->gameWindow);
					}
					else {
						mvwprintw(this->gameWindow, 25, 1, "You deal %d damage but the enemy still stands", roll);
						mvwprintw(this->gameWindow, 26, 1, "Press any key to continue...");
						wgetch(this->gameWindow);
					}
				}
				else {
					mvwprintw(this->gameWindow, 25, 1, "Your attack misses...");
					mvwprintw(this->gameWindow, 26, 1, "Press any key to continue...");
					wgetch(this->gameWindow);
				}
				validInput = true;
			}
			else if (action == 'f' || action == 'F') {			/* Attempt to flee */
				if (!attemptedFlee) {
					this->drawEncounter();
					mvwprintw(this->gameWindow, 1, 1, "Attempting to flee...");
					if (!attemptedFlee) {						/* If you have not tried fleeing before */
						roll = randomNumber(1, 100);
						if (roll >= 75) {						/* 25 % chance to flee */
							mvwprintw(this->gameWindow, 1, 1, "Success! You flee successfully...");
							fled = true;
							encounter = false;
							validInput = true;
						}
						else {
							mvwprintw(this->gameWindow, 1, 1, "Your flee attempt fails!");
							attemptedFlee = true;
							validInput = false;
						}
					}
				}
				else {
					this->drawEncounter();
					mvwprintw(this->gameWindow, 1, 1, "I cant attempt fleeing again!");
					validInput = false;
				}
				mvwprintw(this->gameWindow, 2, 1, "Press any key to continue...");
				wgetch(this->gameWindow);
			}
			else if (action == 'h' || action == 'H') {		/* Lookup commands */
				this->drawEncounter();
				mvwprintw(this->gameWindow, 1, 1, "Commands");
				mvwprintw(this->gameWindow, 2, 1, "'A' to Attack, 'F' to flee");
				mvwprintw(this->gameWindow, 3, 1, "Press any key to continue...");
				wgetch(this->gameWindow);
				validInput = false;
			}
			else {											/* Else invalid input */
				this->drawEncounter();
				mvwprintw(this->gameWindow, 1, 1, "Invalid command! Check 'H' for commands");
				wrefresh(this->gameWindow);
				validInput = false;
			}
		} while (!validInput);								/* Valid input if it ends player turn */

		int enemyCounter = 0;							
		for (int i = 0; i < enemys; i++) {					/* Check if all enemies are dead before enemy turns */
			if (!enemy[i].alive) enemyCounter++;
			if (enemyCounter == enemys) encounter = false;
		}

		if (encounter) {									/* If encounter is still active enemy turn starts*/
			this->drawEncounter();
			mvwprintw(this->gameWindow, 25, 1, "Enemy's turn");
			mvwprintw(this->gameWindow, 26, 1, "Press any key to continue...");
			wgetch(this->gameWindow);
			this->drawEncounter();
			for (int i = 0; i < enemys; i++) {				/* enemy i's attack turn */
				if (enemy[i].alive) {						/* if enemy is alive play his turn else do not */
					roll = randomNumber(1, 100);
					if (roll < enemy[i].accuracy) {			/* If enemy i's roll is lower than accuracy, hit */
						roll = randomNumber(enemy[i].minDamage, enemy[i].maxDamage);
						player->health -= roll;
						if (player->health > 0) {
							mvwprintw(this->gameWindow, 25, 1, "Enemy %d hits player for %d damage!", i + 1, roll);
							mvwprintw(this->gameWindow, 26, 1, "Press any key to continue...");
							wgetch(this->gameWindow);
						}
						else {
							mvwprintw(this->gameWindow, 25, 1, "Enemy %d hits player for %d damage!", i + 1, roll);
							mvwprintw(this->gameWindow, 26, 1, "Enemy has defeated you...");
							mvwprintw(this->gameWindow, 27, 1, "GAME OVER");
							wgetch(this->gameWindow);
							encounter = false;
							status = false;
							break;
						}
					}
					else {
						mvwprintw(this->gameWindow, 25, 1, "Enemy %d misses player!", i + 1);
						mvwprintw(this->gameWindow, 26, 1, "Press any key to continue...");
						wgetch(this->gameWindow);
					}
				}
			}
		}
	}
	delete enemy;											/* Delete enemy objects */
}