#include "stdafx.h"
#include "structs.h"

void defineTiles(Tile tile[]) {
	tile[0].tileName = "Grass";
	tile[0].tileCharacter = '.';
	tile[0].walkable = true;
	tile[0].colorPair = 2;

	tile[1].tileName = "Small tree";
	tile[1].tileCharacter = 't';
	tile[1].walkable = true;
	tile[1].colorPair = 2;

	tile[2].tileName = "Water";
	tile[2].tileCharacter = '~';
	tile[2].walkable = false;
	tile[2].colorPair = 1;
}