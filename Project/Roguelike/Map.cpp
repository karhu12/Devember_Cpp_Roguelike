#include "stdafx.h"
#include "Map.h"
#include "tiles.h"
#include "general.h"

enum terrainType{ FOREST_AREA = 0, CAVE_AREA = 1};

Map::Map() {
	static short initialized = 0;								/* Used to intialize first time in certain fashion */
	int type = randomNumber(0, 1);										/* Generate one of 2 type map*/
	if (type == FOREST_AREA) {									/* Generate forest */
		generateMap(FOREST_AREA);
	}
	else if (type == CAVE_AREA) {								/* Generate cave */
		generateMap(CAVE_AREA);
	}

	if (initialized == 0) {										/* First time setup for exits */
		id = 1;
		for (int i = 0; i < 2; i++) {							/* Loop for creating 2 exits on first area */
			int x = randomNumber(1, 4);							/* Randomize if exits go on top/bottom or sides */
			exit[i].link = 0;
			if (x == 1) {										/* Exit goes to random position on top */
				exit[i].yPos = 0;
				do {
					exit[i].xPos = randomNumber(1, AREA_MAX_WIDTH - 1);
				} while (area[exit[i].yPos][exit[i].xPos] == EXIT);
			}
			else if (x == 2) {									/* Exit goes to random position on bottom */
				exit[i].yPos = AREA_MAX_HEIGHT - 1;
				do {
					exit[i].xPos = randomNumber(1, AREA_MAX_WIDTH - 1);
				} while (area[exit[i].yPos][exit[i].xPos] == EXIT);
			}
			else if (x == 3) {									/* Exit goes to random position on left side */
				exit[i].xPos = 0;
				do {
					exit[i].yPos = randomNumber(1, AREA_MAX_HEIGHT - 1);
				} while (area[exit[i].yPos][exit[i].xPos] == EXIT);
			}
			else {												/* Exit goes to random position on right side */
				exit[i].xPos = AREA_MAX_WIDTH - 1;
				do {
					exit[i].yPos = randomNumber(1, AREA_MAX_HEIGHT - 1);
				} while (area[exit[i].yPos][exit[i].xPos] == EXIT);
			}
			area[exit[i].yPos][exit[i].xPos] = EXIT;
			if (i == 1) initialized++;
		}
	}
	else {														/* Normal setup for exits*/
		int x = randomNumber(1, 4);								/* Same random setup than before but now for only one exit */
		exit[1].link = 0;
		if (x == 1) {
			exit[1].yPos = 0;
			do {
				exit[1].xPos = randomNumber(1, AREA_MAX_WIDTH - 1);
			} while (area[exit[1].yPos][exit[1].xPos] == EXIT);
		}
		else if (x == 2) {
			exit[1].yPos = AREA_MAX_HEIGHT - 1;
			do {
				exit[1].xPos = randomNumber(1, AREA_MAX_WIDTH - 1);
			} while (area[exit[1].yPos][exit[1].xPos] == EXIT);
		}
		else if (x == 3) {
			exit[1].xPos = 0;
			do {
				exit[1].yPos = randomNumber(1, AREA_MAX_HEIGHT - 1);
			} while (area[exit[1].yPos][exit[1].xPos] == EXIT);
		}
		else {
			exit[1].xPos = AREA_MAX_WIDTH - 1;
			do {
				exit[1].yPos = randomNumber(1, AREA_MAX_HEIGHT - 1);
			} while (area[exit[1].yPos][exit[1].xPos] == EXIT);
		}
		area[exit[1].yPos][exit[1].xPos] = EXIT;
	}
}

Map *Map::newMap(std::map<int, Map *> *mapOfLevels, character *player, int index) {
	Map *newmap;										/* New map to be returned */
	static short maps = 1, oldMapId;					/* maps tracked statically */
	short oldExitX = this->exit[index].xPos, oldExitY = this->exit[index].yPos;	/* Set old x and y exit on variables*/
	this->exit[index].link = maps + 1;					/* Current maps link will be the map to be created */
	oldMapId = this->id;								/* Old maps id is current map */
	(*mapOfLevels)[this->id] = this;					/* Store current object pointer in map */
	newmap = new Map;									/* Create fresh map */
	newmap->exit[0].link = oldMapId;					/* One exit will have the connection to old exit */
	newmap->id = maps + 1;								/* New map id will be the same as link on old map */
	if (oldExitX == 0) {								/* Change player position and new exit position depending on old position */
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
	else if (oldExitX == AREA_MAX_WIDTH - 1) {
		newmap->exit[0].xPos = 1;
		newmap->exit[0].yPos = oldExitY;
		player->yPos = newmap->exit[0].yPos;
		player->xPos = newmap->exit[0].xPos + 1;
	}
	else if (oldExitY == AREA_MAX_HEIGHT - 1) {
		newmap->exit[0].yPos = 0;
		newmap->exit[0].xPos = oldExitX;
		player->yPos = newmap->exit[0].yPos + 1;
		player->xPos = newmap->exit[0].xPos;
	}
	newmap->area[newmap->exit[0].yPos][newmap->exit[0].xPos] = EXIT;	/* Set new exit position be recognisible tile */
	maps++;
	return newmap;
}

Map *Map::loadMap(std::map<int, Map *> *mapOfLevels, character * player, int index) {
	Map *map;
	short selectedMap = this->exit[index].link;		/* Map to be loadede from exit link */
	short oldExitX = this->exit[index].xPos, oldExitY = this->exit[index].yPos;
	(*mapOfLevels)[this->id] = this;				/* Store current area object to map */
	map = (*mapOfLevels)[selectedMap];				/* Pointer gets new value from map */
	if (player->yPos == 0) player->yPos = AREA_MAX_HEIGHT - 2;	/* Change player position depending on player position on exit*/
	else if (player->yPos == AREA_MAX_HEIGHT - 1) player->yPos = 1;
	else if (player->xPos == 0) player->xPos = AREA_MAX_WIDTH - 2;
	else if (player->xPos == AREA_MAX_WIDTH - 1) player->xPos = 1;
	return map;	
}

Map *Map::returnNewArea(character *player, std::map<int, Map*> *mapOfLevels) {
	Map *newmap;									/* Map object to be returned */
	for (int i = 0; i < 2; i++) {
		if (this->exit[i].xPos == player->xPos && this->exit[i].yPos == player->yPos) {
			if (this->exit[i].link == 0) {			/* If there is no link function creates new map and stores old one in map */
				newmap = this->newMap(mapOfLevels, player, i);
				return newmap;
			}
			else if (this->exit[i].link != 0) {		/* If there is link load or map object and store current */
				newmap = this->loadMap(mapOfLevels, player, i);
				return newmap;
			}
		}
	}
}

void Map::generateMap(int type) {
	if (type == FOREST_AREA) {									/* Generate area depending on parameter */
		for (int i = 0; i < AREA_MAX_HEIGHT; i++)				/* Initialize map with grass values */
			for (int j = 0; j < AREA_MAX_WIDTH; j++)
				this->area[i][j] = GRASS;
		for (int i = 0; i < AREA_MAX_HEIGHT; i++) {				/* Generate borders for the map */
			for (int j = 0; j < AREA_MAX_WIDTH; j++) {
				if (i == 0 && j >= 0 && j < AREA_MAX_WIDTH)
					this->area[i][j] = THICK_FOREST;
				if (i == AREA_MAX_HEIGHT - 1 && j >= 0 && j < AREA_MAX_WIDTH)
					this->area[i][j] = THICK_FOREST;
				if (j == 0 && i >= 0 && i < AREA_MAX_HEIGHT)
					this->area[i][j] = THICK_FOREST;
				if (j == AREA_MAX_WIDTH - 1 && i >= 0 && i < AREA_MAX_HEIGHT)
					this->area[i][j] = THICK_FOREST;
			}
		}
		short forests = randomNumber(2, 4);						/* Random forest generation */
		for (int f = 0; f < forests; f++) {
			short y = randomNumber(2, 14), x = randomNumber(2, 27);
			for (int i = randomNumber(1, y); i < randomNumber(y + 1, AREA_MAX_HEIGHT - 1); i++) {
				for (int j = randomNumber(1, x); j < randomNumber(x + 1, AREA_MAX_WIDTH - 1); j++) {
					this->area[i][j] = FOREST;
				}
			}
		}
		short lakes = randomNumber(0, 2);						/* Lake generation WIP */
		for (int l = 0; l < lakes; l++) {
			short y = randomNumber(4, AREA_MAX_HEIGHT - 4), x = randomNumber(6, AREA_MAX_WIDTH - 6);
			for (int i = y - 4; i < y; i++) {
				for (int j = x - 6; j < x; j++) {
					this->area[i][j] = LAKE;
				}
			}
		}
		if (randomNumber(0, 1) == 1) {
			short y = randomNumber(0,AREA_MAX_HEIGHT),x = randomNumber(0,AREA_MAX_WIDTH);
			this->area[y][x] = ITEM;
		}
	}
	else if (type == CAVE_AREA) {
		for (int i = 0; i < AREA_MAX_HEIGHT; i++)				/* Initialize map with rock values */
			for (int j = 0; j < AREA_MAX_WIDTH; j++)
				this->area[i][j] = ROCKY_TERRAIN;
		for (int i = 0; i < AREA_MAX_HEIGHT; i++) {				/* Generate borders for the map */
			for (int j = 0; j < AREA_MAX_WIDTH; j++) {
				if (i == 0 && j >= 0 && j < AREA_MAX_WIDTH)
					this->area[i][j] = MOUNTAIN;
				if (i == AREA_MAX_HEIGHT - 1 && j >= 0 && j < AREA_MAX_WIDTH)
					this->area[i][j] = MOUNTAIN;
				if (j == 0 && i >= 0 && i < AREA_MAX_HEIGHT)
					this->area[i][j] = MOUNTAIN;
				if (j == AREA_MAX_WIDTH - 1 && i >= 0 && i < AREA_MAX_HEIGHT)
					this->area[i][j] = MOUNTAIN;
			}
		}
		if (randomNumber(0, 1) == 1) {
			short y = randomNumber(0, AREA_MAX_HEIGHT), x = randomNumber(0, AREA_MAX_WIDTH);
			this->area[y][x] = ITEM;
		}
	}
}