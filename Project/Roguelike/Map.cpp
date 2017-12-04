#include "stdafx.h"
#include "Map.h"
#include "tiles.h"

Map Map::createMap() {
	Map map;
	for (int i = 0; i < AREA_MAX_HEIGHT; i++)
		for (int j = 0; j < AREA_MAX_WIDTH; j++)
			map.area[i][j] = GRASS;						/* Initialize map with grass values */

	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 10; j++)
			map.area[i][j] = FOREST;
	for (int i = 3; i < 5; i++)
		for (int j = 3; j < 6; j++)
			map.area[i][j] = THICK_FOREST;

	for (int i = 1; i < 9; i++)
		for (int j = 19; j < 44; j++)
			map.area[i][j] = BEACH;

	for (int i = 2; i < 8; i++)
		for (int j = 20; j < 43; j++)
			map.area[i][j] = LAKE;						/* Testing tiles */

	for (int i = 12; i < 13; i++)
		for (int j = 35; j < 43; j++)
			map.area[i][j] = PATH;

	return map;
}