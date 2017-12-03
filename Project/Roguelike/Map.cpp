#include "stdafx.h"
#include "Map.h"

Map Map::createMap() {
	Map map;
	for (int i = 0; i < AREA_MAX_HEIGHT; i++)
		for (int j = 0; j < AREA_MAX_WIDTH; j++)
			map.area[i][j] = 0;						/* Initialize map with grass values */

	for (int i = 2; i < 8; i++)
		for (int j = 2; j < 10; j++)
			map.area[i][j] = 1;

	for (int i = 2; i < 8; i++)
		for (int j = 20; j < 43; j++)
			map.area[i][j] = 2;						/* Testing tiles */
	return map;
}