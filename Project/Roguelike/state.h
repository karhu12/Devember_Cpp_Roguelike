#pragma once

#include "Buffer.h"

class state : public Buffer {
public:
	std::string lastCommand;
	void bufferCreate();					/* Create window buffers */
	void bufferRelease();					/* Release buffer memory */
	void command(char cmd, character *player, Map *map, Tile tile[]);
	void enemyEncounter(character *player);
	bool getStatus();
	void setStatus(bool);

private:
	bool status;										/* Game running state */
};