#pragma once

#define MAX_TILES 3

struct Tile {
	std::string tileName;
	chtype tileCharacter;
	bool walkable;
	short foregroundColor, backgroundColor;
} ;

void defineTiles(Tile tile[]);
int returnColorPair(int foreground, int background);