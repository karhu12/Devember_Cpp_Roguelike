#pragma once

#include "stdafx.h"
#include "Map.h"
#include "Player.h"
#include "tiles.h"
#include "general.h"
#include "enemy.h"

class Player;
class Map;
class Enemy;
struct Tile;

class Buffer {
public:
	void createBuffer();												/* Create window buffers */
	void releaseBuffer();											/* Release buffer memory */
	void drawGame(Map *map, Tile tile[], Player *player);		/* Draw game state */
	void drawStatus(Player * player);							/* Draw status window specific */
	void drawText();											/* Draw text window base */
	void drawEncounter();										/* Draw encounter screen for game window */
	void listEnemies(Enemy *enemy, short enemys);
	void listCommands();										/* List available commands on text bar */
	WINDOW *gameWindow, *statusWindow, *textWindow;				/* Initialize game windows */
};
