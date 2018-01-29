#pragma once

#include "stdafx.h"
#include "buffer.h"
#include "Player.h"
#include "Map.h"
#include "tiles.h"
#include "general.h"
#include "enemy.h"

class Map;
class Player;
class Buffer;

class state {
public:
	state();
	~state();
	std::string lastCommand;

	void executeInput(Player *player, Map *map, Tile tile[]);
	void enemyEncounter(Player *player);
	bool getGameStatus();
	void setStatus(bool);
	void gameLoop();
	void initGame();

private:
	bool status;							/* Game running state */
	Map *map;
	std::map<int, Map *> *mapOfLevels;
	Player *player;						/* Create player object with certain parameters */
	Buffer *buffer;
	Tile tile[MAX_TILES];
};