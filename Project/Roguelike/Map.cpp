#include "stdafx.h"
#include "Map.h"
#include "tiles.h"
#include "general.h"


Map *Map::createMap() {										/* Function to create new map */
	Map *map = new Map;
	static short created = 0;								/* Used to intialize first time in certain fashion */
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
	}														/* Random forest generation (no logic) */

	if (created == 0) {										/* First time setup for exits */
		map->id = 1;
		for (int i = 0; i < 2; i++) {
			map->exit[i].link = 0;
			map->exit[i].xPos = randomNumber(0, AREA_MAX_WIDTH);
			map->exit[i].yPos = 0;
			map->area[map->exit[i].yPos][map->exit[i].xPos] = FOREST_EXIT;
			if (i == 1) created++;
		}
	}
	else {													/* Normal setup for exits*/
		map->exit[1].link = 0;
		map->exit[1].xPos = randomNumber(0, AREA_MAX_WIDTH);
		map->exit[1].yPos = 0;
		map->area[map->exit[1].yPos][map->exit[1].xPos] = FOREST_EXIT;
	}
	return map;
}

Map *Map::newMap(std::map<int, Map *> *mapOfLevels, character *player, int index) {
	Map *newmap;
	static short maps = 1, oldMapId;
	short oldExitX = this->exit[index].xPos, oldExitY = this->exit[index].yPos;
	this->exit[index].link = maps + 1;
	oldMapId = this->id;
	(*mapOfLevels)[this->id] = this;
	newmap = new Map;
	newmap = Map::createMap();
	newmap->exit[0].link = oldMapId;
	newmap->id = maps + 1;
	if (oldExitX == 0) {
		newmap->exit[0].xPos = AREA_MAX_WIDTH - 1;
		newmap->exit[0].yPos = oldExitY;
		player->yPos = newmap->exit[0].yPos;
		player->xPos = newmap->exit[0].xPos - 1;
	}
	else if (oldExitY == 0) {
		newmap->exit[0].yPos = AREA_MAX_HEIGHT - 1;
		newmap->exit[0].xPos = oldExitX;
		player->yPos = newmap->exit[0].yPos - 1;
		player->xPos = newmap->exit[0].xPos;
	}
	newmap->area[newmap->exit[0].yPos][newmap->exit[0].xPos] = FOREST_EXIT;
	maps++;
	return newmap;
}

Map *Map::loadMap(std::map<int, Map *> *mapOfLevels, character * player, int index) {
	Map *map;
	short selectedMap = this->exit[index].link;
	short oldExitX = this->exit[index].xPos, oldExitY = this->exit[index].yPos;
	(*mapOfLevels)[this->id] = this;
	map = (*mapOfLevels)[selectedMap];
	if (player->yPos == 0) player->yPos = AREA_MAX_HEIGHT - 2;
	else if (player->yPos == AREA_MAX_HEIGHT - 1) player->yPos = 1;
	else if (player->xPos == 0) player->xPos = AREA_MAX_WIDTH - 2;
	else if (player->xPos == AREA_MAX_WIDTH - 1) player->xPos = 1;
	return map;	
}

Map *Map::returnNewArea(character *player, std::map<int, Map*> *mapOfLevels, state game) {
	Map *newmap;
	for (int i = 0; i < 2; i++) {
		if (this->exit[i].xPos == player->xPos && this->exit[i].yPos == player->yPos) {
			if (this->exit[i].link == 0) {
				newmap = this->newMap(mapOfLevels, player, i);
				//mvwprintw(game.textWindow, 1, 1, "New map created..."); DEBUG ONLY
				return newmap;
			}
			else if (this->exit[i].link != 0) {
				newmap = this->loadMap(mapOfLevels, player, i);
				//mvwprintw(game.textWindow, 1, 1, "Loading existing map..."); DEBUG ONLY AFFECTED BY SCREEN CLEARING
				return newmap;
			}
		}
	}
}
