#pragma once
#include "character.h"

struct Trigger {
	short xPos, yPos;
	short link;
	std::string type;
};

class character;
class state;
struct Tile;

class Map {
public:
	Map();
	std::string environment;						/* Environment type can be used in generation */
	short area[AREA_MAX_HEIGHT][AREA_MAX_WIDTH];	/* Two dimensional array to store all the tiles in map */
	short id;										/* Used to locate map */
	Trigger exit[2];
	Map *newMap(std::map<int, Map *> *zone, character *player, int index);
	Map *loadMap(std::map<int, Map *> *mapOfLevels, character *player, int index);
	Map *returnNewArea(character *player, std::map<int, Map*> *mapOfLevels);
	void generateMap(int type);
};
