#pragma once

#include "Map.h"
#include "tiles.h"

class character {
public:
	short health, level, experience;							/* Generic propertys of player */
	short strength, dexterity, intelligence;
	short xPos, yPos;											/* Players x,y position in area */
	short foregroundColor;										/* Players representing color on console*/
	char input;													/* Used for player input with getch */
	chtype playerCharacter;										/* Tile representing player */
	void playerMovement(Map map, Tile tile[], char input);		/* Player functions */
	static character createPlayer();
};
