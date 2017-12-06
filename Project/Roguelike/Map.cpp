#include "stdafx.h"
#include "Map.h"
#include "tiles.h"
#include "general.h"

Map *Map::createMap() {
	Map *map = new Map;
	Trigger trigger;
	for (int i = 0; i < AREA_MAX_HEIGHT; i++)
		for (int j = 0; j < AREA_MAX_WIDTH; j++)
			map->area[i][j] = GRASS;						/* Initialize map with grass values */

	for (int i = 0; i < AREA_MAX_HEIGHT; i++) {				/* Generate borders for the map */
		for (int j = 0; j < AREA_MAX_WIDTH; j++) {
			if (i == 0 && j >= 0 && j < AREA_MAX_WIDTH)
				map->area[i][j] = THICK_FOREST;
			if (i == AREA_MAX_HEIGHT - 1 && j >= 0 && j < AREA_MAX_WIDTH)
				map->area[i][j] = THICK_FOREST;
			if (j == 0 && i >= 0 && i < AREA_MAX_HEIGHT)
				map->area[i][j] = THICK_FOREST;
			if (j == AREA_MAX_WIDTH - 1 && i >= 0 && i < AREA_MAX_HEIGHT)
				map->area[i][j] = THICK_FOREST;
		}
	}

	for (int i = randomNumber(0, 10); i < randomNumber(11,14); i++) {
		for (int j = randomNumber(0, 20); j < randomNumber(21,40); j++) {
			map->area[i][j] = FOREST;
		}
	}

	map->trigger.link = 0;
	map->trigger.type = "Forest";
	map->trigger.xPos = 20;
	map->trigger.yPos = 0;
	map->area[0][20] = FOREST_EXIT;

	return map;
}

Map *Map::newMap(Map *map, std::map<int, Map *> *zone) {
	static short maps = 1;
	map->trigger.link = maps + 1;
	map->trigger.ownLink = maps;
	(*zone)[maps] = map;
	map = new Map;
	map = Map::createMap();
	map->area[0][25] = FOREST_EXIT;
	map->trigger.link = 1;
	map->trigger.ownLink = maps + 1;
	map->trigger.xPos = 25;
	map->trigger.yPos = 0;
	maps++;
	return map;
}

Map *Map::loadMap(Map *map, std::map<int, Map *> *zone) {
	short selectedMap = map->trigger.link;
	(*zone)[map->trigger.ownLink] = map;
	map = (*zone)[selectedMap];
	return map;	
}