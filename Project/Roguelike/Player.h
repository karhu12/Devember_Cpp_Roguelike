#pragma once

#include "stdafx.h"
#include "Item.h"
#include "tiles.h"
#include "Map.h"
#include "state.h"

class Map;
class Buffer;
class Item;

class Player {
public:
	Player();
	~Player();
	int playerMovement(Map *map, Tile tile[], char input);		/* Player functions */
	char getPlayerInput(Buffer *buffer);
	int playerAttack();
	void newItemToInventory();
	short health, level, experience;							/* Generic propertys of player */
	short strength, dexterity, intelligence;
	short xPos, yPos;											/* Players x,y position in area */
	short minDamage, maxDamage;
	short accuracy;
	short foregroundColor;										/* Players representing color on console*/
	chtype playerCharacter;										/* Tile representing player */
	Item *mainHand, *offHand;

private:
	char input;													/* Used for player input with getch */
	std::map<int, Item *> itemMap;
	short items;
};
