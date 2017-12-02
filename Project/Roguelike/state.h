#pragma once

#include "_buffer.h"

class state : public _buffer {
public:
	bool status;										/* Game running state */
	int map[AREA_MAX_HEIGHT][AREA_MAX_WIDTH];			/* Current map values */
	void bufferCreate(state *game);						/* Create window buffers */
	void bufferRelease(state *game);					/* Release buffer memory */
};
