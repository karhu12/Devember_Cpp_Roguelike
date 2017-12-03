#include "stdafx.h"
#include "character.h"
#include "tiles.h"
#include "Map.h"

character character::createPlayer() {			/* Initializes the values of player object */
	character player;
	player.level = 1;
	player.health = 100;
	player.experience = 0;
	player.xPos = 30;
	player.yPos = 9;
	player.playerCharacter = 'P';
	player.foregroundColor = COLOR_CYAN;
	return player;
}

void character::playerMovement(Map map, Tile tile[], char input) {
	if (input == 'd' || input == 'D') {
		if (this->xPos < AREA_MAX_WIDTH - 1)
			if (tile[map.area[this->yPos][this->xPos + 1]].walkable == true)
				this->xPos += 1;
	}
	if (input == 'a' || input == 'A') {
		if (this->xPos > 0)
			if (tile[map.area[this->yPos][this->xPos + -1]].walkable == true)
				this->xPos -= 1;
	}
	if (input == 'w' || input == 'W') {
		if (this->yPos > 0)
			if (tile[map.area[this->yPos - 1][this->xPos]].walkable == true)
				this->yPos -= 1;
	}
	if (input == 's' || input == 'S') {
		if (this->yPos < AREA_MAX_HEIGHT - 1)
			if (tile[map.area[this->yPos + 1][this->xPos]].walkable == true)
				this->yPos += 1;
	}
}
