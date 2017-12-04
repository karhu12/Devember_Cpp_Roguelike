#pragma once
#define MAX_TILES 6
#define COLOR_GREY 8

enum tiles { GRASS = 0, FOREST = 1, THICK_FOREST = 2, LAKE = 3, PATH = 4 , BEACH = 5};

struct Tile {
	std::string tileName;
	chtype tileCharacter;
	bool walkable;
	short foregroundColor, backgroundColor;
} ;

void defineTiles(Tile tile[]);
int returnColorPair(int foreground, int background);