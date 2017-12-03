#pragma once

#include "Map.h"
#include "tiles.h"

class character {
public:
	short health, level, experience;							/* Generic propertys of player */
	short xPos, yPos;											/* Players x,y position in area */
	short foregroundColor;										/* Players representing color on console*/
	chtype playerCharacter;
	void playerMovement(Map map, Tile tile[], char input);		/* Player functions */
	static character createPlayer();
};
