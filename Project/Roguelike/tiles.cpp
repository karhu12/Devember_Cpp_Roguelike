#include "stdafx.h"
#include "tiles.h"

void defineTiles(Tile tile[]) {
	tile[0].tileName = "Grass";
	tile[0].tileCharacter = '.';
	tile[0].walkable = true;
	tile[0].foregroundColor = COLOR_GREEN;
	tile[0].backgroundColor = COLOR_GREEN;

	tile[1].tileName = "Small tree";
	tile[1].tileCharacter = 't';
	tile[1].walkable = true;
	tile[1].foregroundColor = COLOR_GREEN;
	tile[1].backgroundColor = COLOR_GREEN;

	tile[2].tileName = "Water";
	tile[2].tileCharacter = '~';
	tile[2].walkable = false;
	tile[2].foregroundColor = COLOR_BLUE;
	tile[2].backgroundColor = COLOR_BLUE;
}

int returnColorPair(int foreground, int background) {
	return (foreground * 9 + background + 1);
}