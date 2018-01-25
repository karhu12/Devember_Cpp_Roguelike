#pragma once
#define MAX_TILES 8
#define COLOR_GREY 8

enum tiles { GRASS = 0, FOREST = 1, THICK_FOREST = 2, LAKE = 3, MOUNTAIN = 4 , ROCKY_TERRAIN = 5, EXIT = 6, ITEM = 7};

struct Tile {
	std::string tileName;
	chtype tileCharacter;
	bool walkable, exit;
	short foregroundColor, backgroundColor;
} ;

void defineTiles(Tile tile[]);
int returnColorPair(int foreground, int background);