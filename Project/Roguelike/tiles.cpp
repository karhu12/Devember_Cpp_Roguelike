#include "stdafx.h"
#include "tiles.h"

void defineTiles(Tile tile[]) {
	tile[0].tileName = "Grass";
	tile[0].tileCharacter = ' ';
	tile[0].walkable = true;
	tile[0].foregroundColor = COLOR_GREEN;
	tile[0].backgroundColor = COLOR_GREEN;

	tile[1].tileName = "Forest";
	tile[1].tileCharacter = 'f';
	tile[1].walkable = true;
	tile[1].foregroundColor = COLOR_GREEN;
	tile[1].backgroundColor = COLOR_GREEN;

	tile[2].tileName = "Thick forest";
	tile[2].tileCharacter = 'F';
	tile[2].walkable = false;
	tile[2].foregroundColor = COLOR_GREEN;
	tile[2].backgroundColor = COLOR_GREEN;

	tile[3].tileName = "Lake";
	tile[3].tileCharacter = '~';
	tile[3].walkable = false;
	tile[3].foregroundColor = COLOR_BLUE;
	tile[3].backgroundColor = COLOR_BLUE;

	tile[4].tileName = "Path";
	tile[4].tileCharacter = ' ';
	tile[4].walkable = true;
	tile[4].foregroundColor = COLOR_GREY;
	tile[4].backgroundColor = COLOR_GREY;

	tile[5].tileName = "Beach";
	tile[5].tileCharacter = ACS_BLOCK;
	tile[5].walkable = true;
	tile[5].foregroundColor = COLOR_YELLOW;
	tile[5].backgroundColor = COLOR_YELLOW;
}

int returnColorPair(int foreground, int background) {
	return (foreground * 9 + background + 1);
}