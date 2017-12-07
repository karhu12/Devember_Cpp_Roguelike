#pragma once

struct Trigger {
	short xPos, yPos;
	short link, ownLink;
	std::string type;
};

class Map {
public:
	std::string environment;						/* Environment type can be used in generation */
	short area[AREA_MAX_HEIGHT][AREA_MAX_WIDTH];	/* Two dimensional array to store all the tiles in map */
	short id;										/* Used to locate map */
	short xExit,yExit;
	static Map *createMap();
	Map *newMap(Map *map, std::map<int, Map *> *zone, int index);
	Map *loadMap(Map *map, std::map<int, Map *> *zone, int index);
	Trigger exit[2];
};
