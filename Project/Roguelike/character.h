#pragma once

#include "Map.h"
#include "structs.h"

class character {
public:
	short health, level, experience;
	int xPos, yPos;
	void playerMovement(Map map, Tile tile[], char input);
	static character createPlayer();
};
