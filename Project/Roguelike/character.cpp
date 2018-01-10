#include "stdafx.h"
#include "character.h"
#include "tiles.h"
#include "Map.h"
#include "Items.h"

character::character() {
	level = 1;
	health = 100;
	experience = 0;
	strength = 10;
	dexterity = 10;
	intelligence = 10;
	accuracy = 95;
	minDamage = 2;
	maxDamage = 8;
	accuracy = 80;
	xPos = 30;
	yPos = 9;
	items = 0;
	mainHand = generateItem(BAREHAND);
	offHand = generateItem(BAREHAND);
	playerCharacter = 'P';
	foregroundColor = COLOR_CYAN;
}

int character::playerMovement(Map *map, Tile tile[], char input) {
	if (input == 'd' || input == 'D') {
		if (this->xPos < AREA_MAX_WIDTH - 1) {
			if (tile[map->area[this->yPos][this->xPos + 1]].walkable == true) {
				this->xPos += 1;
				return 1;
			}
			else {
				return 0;
			}
		}
		else {
			return 0;
		}
	}
	if (input == 'a' || input == 'A') {
		if (this->xPos > 0) {
			if (tile[map->area[this->yPos][this->xPos + -1]].walkable == true) {
				this->xPos -= 1;
			}
			else {
				return 0;
			}
		}
		else {
			return 0;
		}
	}
	if (input == 'w' || input == 'W') {
		if (this->yPos > 0) {
			if (tile[map->area[this->yPos - 1][this->xPos]].walkable == true)  {
				this->yPos -= 1;
			}
			else {
				return 0;
			}
		}
		else {
			return 0;
		}
	}
	if (input == 's' || input == 'S') {
		if (this->yPos < AREA_MAX_HEIGHT - 1) {
			if (tile[map->area[this->yPos + 1][this->xPos]].walkable == true) {
				this->yPos += 1;
			}
			else {
				return 0;
			}
		}
		else {
			return 0;
		}
	}
}
