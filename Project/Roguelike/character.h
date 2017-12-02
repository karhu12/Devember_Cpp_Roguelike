#pragma once

class character {
public:
	short health, level, experience;
	int xPos, yPos;
	void playerMovement(character *ptr, char input);
	character createPlayer();
};
