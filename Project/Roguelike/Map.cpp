#include "stdafx.h"
#include "Map.h"
#include "tiles.h"
#include "general.h"

Map *Map::createMap() {
	Map *map = new Map;
	int terrainType = randomNumber(1,4);

	if (terrainType == 1)
		map->environment = "Forest";
	else if (terrainType == 2)
		map->environment = "Field";
	else if (terrainType == 3)
		map->environment = "Cave";
	else
		map->environment = "Mountain";


	if (map->environment == "Forest") {
		for (int i = 0; i < AREA_MAX_HEIGHT; i++)
			for (int j = 0; j < AREA_MAX_WIDTH; j++)
				map->area[i][j] = GRASS;						/* Initialize map with grass values */

		for (int i = 4; i < 12; i++)
			for (int j = 20; j < 40; j++)
				map->area[i][j] = FOREST;
	}
	else if (map->environment == "Field") {
		for (int i = 0; i < AREA_MAX_HEIGHT; i++)
			for (int j = 0; j < AREA_MAX_WIDTH; j++)
				map->area[i][j] = GRASS;

		for (int i = 0; i < 8; i++)
			for (int j = 0; j < 10; j++)
				map->area[i][j] = FOREST;
	}
	else if (map->environment == "Cave") {
		for (int i = 0; i < AREA_MAX_HEIGHT; i++)
			for (int j = 0; j < AREA_MAX_WIDTH; j++)
				if (i > 0 && i < AREA_MAX_HEIGHT - 1 && j > 0 && j < AREA_MAX_WIDTH - 1) {
					map->area[i][j] = ROCKY_TERRAIN;
				}
				else {
					map->area[i][j] = MOUNTAIN;
				}
	}
	else {
		for (int i = 0; i < AREA_MAX_HEIGHT; i++)
			for (int j = 0; j < AREA_MAX_WIDTH; j++)
				if (i > 0 && i < AREA_MAX_HEIGHT - 1 && j > 0 && j < AREA_MAX_WIDTH - 1) {
					map->area[i][j] = ROCKY_TERRAIN;
				}
				else {
					map->area[i][j] = MOUNTAIN;
				}
	}

	return map;
}