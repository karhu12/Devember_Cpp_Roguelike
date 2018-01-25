#pragma once

#include "stdafx.h"
#include "Items.h"
#include "tiles.h"
#include "Map.h"
#include "state.h"

class Map;

class Player: public Items {
public:
	Player();
	short health, level, experience;							/* Generic propertys of player */
	short strength, dexterity, intelligence;
	short xPos, yPos;											/* Players x,y position in area */
	short minDamage, maxDamage;
	short accuracy;
	short foregroundColor;										/* Players representing color on console*/
	char input;													/* Used for player input with getch */
	chtype playerCharacter;										/* Tile representing player */
	Items mainHand, offHand;
	short items;
	std::map<int, Items *> itemMap;
	int playerMovement(Map *map, Tile tile[], char input);		/* Player functions */
};
