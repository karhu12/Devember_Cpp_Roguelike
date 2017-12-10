#include "stdafx.h"
#include "character.h"
#include "state.h"
#include "Map.h"
#include "general.h"
#include "enemy.h"

int main() {
	srand(time(NULL));
	state game;										/* Initialize game state object */
	character player = character::createPlayer();	/* Create player object with certain parameters */
	std::map<int, Map *> *mapOfLevels 
	= new std::map<int, Map *>;						/* Dynamic map pointer that stores map pointers*/
	Map *map = Map::createMap();					/* Create map object */
	Tile tile[MAX_TILES];
	defineTiles(tile);								/* Create tile struct array with all known tile values */

	initscr();										/* Start curses */
	curs_set(0);									/* Hide cursor */
	resize_term(SCREEN_HEIGHT, SCREEN_WIDTH);		/* Set initial window size */
	initializeColors();								/* Start colors and initialize 64 color pairs */
	game.bufferCreate(&game);						/* Create game windows of approppriate size */
	game.status = true;
	while (game.status == true) {										/* game loop which updates every input */
		game.drawBorders(game.statusWindow, game.textWindow);			/* Draw borders for status and text window */
		game.drawStatus(game.statusWindow, &player);					/* Draw all status window content */
		game.drawGame(game.gameWindow, map, tile, &player);				/* Draw game screen depending on current map */
		player.input = mvwgetch(game.textWindow, 3, 2);					/* Get input from player */
		game.command(player.input, &player, map, tile);					/* Execute command depending on input */
		if (tile[map->area[player.yPos][player.xPos]].exit == true) {	/* If player steps into exit */
			map = map->returnNewArea(&player, mapOfLevels, game);		/* New zone is created or old one loaded */
		}
		else if (game.lastCommand == "Movement") {						/* On player movement chance to start random encounter */
			int * chance = new int;
			*chance = randomNumber(1, 100);
			if (*chance >= 90) {
				short enemys = randomNumber(1, 3), hitRoll, damage;
				bool encounter = true, enemiesAlive = true, fled = false;
				char command;
				mvwprintw(game.textWindow, 1, 1, "You encounter %d enemys, press any key...", enemys);
				wrefresh(game.textWindow);
				Enemy *enemy = new Enemy[enemys];
				for (int i = 0; i < enemys; i++) {
					enemy[i] = Enemy::createEnemy();
				}
				while (encounter) {
					if (enemiesAlive == false || player.health == 0 || fled == true) break;
					// Draw encounter
					box(game.gameWindow, ACS_VLINE, ACS_HLINE);
					for (int i = 1; i < AREA_MAX_HEIGHT - 1; i++) {
						for (int j = 1; j < AREA_MAX_WIDTH - 1; j++) {
							mvwaddch(game.gameWindow, i, j, ' ');
						}
					}
					// Play encounter
					for (int i = 0; i < enemys; i++) {
						if (enemy[i].health <= 0) break;
						hitRoll = randomNumber(1, 100);
						if (hitRoll > enemy[i].accuracy) {
							damage = randomNumber(enemy[i].minDamage, enemy[i].maxDamage);
							mvwprintw(game.textWindow, 1, 1, "Enemy hits player for %d damage", damage);
							mvwprintw(game.textWindow, 2, 1, "Any key to continue...");
							wgetch(game.textWindow);
							if ((player.health -= damage) <= 0) {
								mvwprintw(game.textWindow, 1, 1, "YOU DIED");
								game.status = false;
								wgetch(game.textWindow);
								break;
							}
						}
						else {
							mvwprintw(game.textWindow, 1, 1, "Enemy misses...");
							wgetch(game.textWindow);
						}
					}
					while (addch(wgetch(game.textWindow)) != '\n');
					mvwprintw(game.textWindow, 1, 1, "What is your move?");
					while ((command = wgetch(game.gameWindow)) != 'a' || 'f' ) {
						
					}
					if (command == 'a') {
						damage = randomNumber(player.physicalMinDamage, player.physicalMaxDamage);
						for (int i = 0; i < enemys; i++) {
							if (enemy[i].health > 0) {
								enemy[i].health -= damage;
								break;
							}
						}
					}
					int counter = 0;
					for (int i = 0; i < enemys; i++) {
						if (enemy[i].health <= 0) counter++;
					}
					if (counter == enemys) {
						encounter = false;
					}
					else
						counter = 0;
				}
				delete enemy;
			}
			delete chance;
		}
	}
	game.bufferRelease(&game);
													/* Release window buffer memory */
	return 0;
}