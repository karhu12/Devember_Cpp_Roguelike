#include "stdafx.h"
#include "Map.h"
#include "tiles.h"
#include "general.h"

Map *Map::createMap() {
	Map *map = new Map;
	static short created = 0;
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
	if (created == 0) {
		map->id = 1;
		for (int i = 0; i < 2; i++) {
			map->exit[i].link = 0;
			map->exit[i].ownLink = 1;
			map->exit[i].xPos = randomNumber(0, AREA_MAX_WIDTH);
			map->exit[i].yPos = 0;
			map->area[map->exit[i].yPos][map->exit[i].xPos] = FOREST_EXIT;
			if (i == 1) created++;
		}
	}
	else {
		map->exit[1].link = 0;
		map->exit[1].type = "Forest";
		map->exit[1].xPos = randomNumber(0, AREA_MAX_WIDTH);
		map->exit[1].yPos = 0;
		map->area[map->exit[1].yPos][map->exit[1].xPos] = FOREST_EXIT;
	}
	return map;
}

Map *Map::newMap(Map *map, std::map<int, Map *> *zone, int index) {
	static short maps = 1, oldLink;
	short oldExitX = map->exit[index].xPos, oldExitY = map->exit[index].yPos;
	map->exit[index].link = maps + 1;
	map->exit[index].ownLink = map->id;
	oldLink = map->id;
	(*zone)[maps] = map;
	map = new Map;
	map = Map::createMap();
	map->exit[0].link = oldLink;
	map->id = maps + 1;
	map->exit[0].ownLink = map->id;
	if (oldExitX == 0) {
		map->exit[0].xPos = AREA_MAX_WIDTH;
		map->exit[0].yPos = oldExitY;
	}
	else if (oldExitY == 0) {
		map->exit[0].yPos = AREA_MAX_HEIGHT - 1;
		map->exit[0].xPos = oldExitX;
	}
	map->area[map->exit[0].yPos][map->exit[0].xPos] = FOREST_EXIT;
	maps++;
	return map;
}

Map *Map::loadMap(Map *map, std::map<int, Map *> *zone, int index) {
	short selectedMap = map->exit[index].link;
	(*zone)[map->exit[index].ownLink] = map;
	map = (*zone)[selectedMap];
	return map;	
}