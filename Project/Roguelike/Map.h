#pragma once

#include "stdafx.h"
#include "Map.h"
#include "Player.h"
#include "general.h"

struct Trigger {
	short xPos, yPos;
	short link;
	std::string type;
};

class Player;
struct Tile;

class Map {
public:
	Map();
	std::string environment;						/* Environment type can be used in generation */
	int defaultTile;
	short area[AREA_MAX_HEIGHT][AREA_MAX_WIDTH];	/* Two dimensional array to store all the tiles in map */
	short id;										/* Used to locate map */
	Trigger exit[2];
	Map *newMap(std::map<int, Map *> *zone, Player *player, int index);
	Map *loadMap(std::map<int, Map *> *mapOfLevels, Player *player, int index);
	Map *returnNewArea(Player *player, std::map<int, Map*> *mapOfLevels);
	void generateMap(int type);
	void changeAreaToDefault(int x, int y);
};
