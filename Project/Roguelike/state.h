#pragma once

#include "Buffer.h"

class state : public Buffer {
public:
	bool status;										/* Game running state */
	void bufferCreate(state *game);						/* Create window buffers */
	void bufferRelease(state *game);					/* Release buffer memory */
	void state::command(char cmd, character *player, Map *map, Tile tile[]);
};