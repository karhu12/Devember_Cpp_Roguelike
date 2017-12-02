#include "stdafx.h"
#include "character.h"

character character::createPlayer() {
	character player;
	player.level = 1;
	player.health = 100;
	player.experience = 0;
	player.xPos = 30;
	player.yPos = 9;
	return player;
}

void character::playerMovement(character *ptr, char input) {
	if (input == 'd' || input == 'D')
		if (ptr->xPos < AREA_MAX_WIDTH)
			ptr->xPos += 1;
	if (input == 'a' || input == 'A')
		if (ptr->xPos > 0)
			ptr->xPos -= 1;
	if (input == 'w' || input == 'W')
		if (ptr->yPos > 0)
			ptr->yPos -= 1;
	if (input == 's' || input == 'S')
		if (ptr->yPos < AREA_MAX_HEIGHT)
			ptr->yPos += 1;
}
