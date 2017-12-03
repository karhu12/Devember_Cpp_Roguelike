#pragma once

#define MAX_TILES 3

struct Tile {
	std::string tileName;
	char tileCharacter;
	bool walkable;
	short colorPair;
} ;

void defineTiles(Tile tile[]);