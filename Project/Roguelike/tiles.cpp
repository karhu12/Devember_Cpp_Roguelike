#include "stdafx.h"
#include "tiles.h"

void defineTiles(Tile tile[]) {
	tile[0].tileName = "Grass";
	tile[0].tileCharacter = ' ';
	tile[0].walkable = true;
	tile[0].exit = false;
	tile[0].foregroundColor = COLOR_GREEN;
	tile[0].backgroundColor = COLOR_GREEN;

	tile[1].tileName = "Forest";
	tile[1].tileCharacter = 'f';
	tile[1].walkable = true;
	tile[1].exit = false;
	tile[1].foregroundColor = COLOR_GREEN;
	tile[1].backgroundColor = COLOR_GREEN;

	tile[2].tileName = "Thick forest";
	tile[2].tileCharacter = '#';
	tile[2].walkable = false;
	tile[2].exit = false;
	tile[2].foregroundColor = COLOR_GREEN;
	tile[2].backgroundColor = COLOR_GREEN;

	tile[3].tileName = "Lake";
	tile[3].tileCharacter = '~';
	tile[3].walkable = false;
	tile[3].exit = false;
	tile[3].foregroundColor = COLOR_BLUE;
	tile[3].backgroundColor = COLOR_BLUE;

	tile[4].tileName = "Mountain wall";
	tile[4].tileCharacter = '#';
	tile[4].walkable = false;
	tile[4].exit = false;
	tile[4].foregroundColor = COLOR_WHITE;
	tile[4].backgroundColor = COLOR_BLACK;

	tile[5].tileName = "Rocky terrain";
	tile[5].tileCharacter = '.';
	tile[5].walkable = true;
	tile[5].exit = false;
	tile[5].foregroundColor = COLOR_WHITE;
	tile[5].backgroundColor = COLOR_BLACK;

	tile[6].tileName = "Exit";
	tile[6].tileCharacter = 'E';
	tile[6].walkable = true;
	tile[6].exit = true;
	tile[6].foregroundColor = COLOR_BLACK;
	tile[6].backgroundColor = COLOR_WHITE;

	tile[7].tileName = "Item";
	tile[7].tileCharacter = '?';
	tile[7].walkable = true;
	tile[7].exit = false;
	tile[7].foregroundColor = COLOR_YELLOW;
	tile[7].backgroundColor = COLOR_WHITE;

}

int returnColorPair(int foreground, int background) {
	return (foreground * 9 + background + 1);
}