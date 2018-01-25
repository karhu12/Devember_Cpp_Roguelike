#pragma once

#include "Buffer.h"

class state : public Buffer {
public:
	state();
	~state();
	std::string lastCommand;
	void bufferCreate();					/* Create window buffers */
	void bufferRelease();					/* Release buffer memory */
	void command(char cmd, character *player, Map *map, Tile tile[]);
	void enemyEncounter(character *player);
	bool getStatus();
	void setStatus(bool);
	void gameLoop();
	Map *map;
	std::map<int, Map *> *mapOfLevels;
	character player;						/* Create player object with certain parameters */

private:
	bool status;							/* Game running state */
};