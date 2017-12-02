#pragma once

#include "_buffer.h"


class state : public _buffer {
public:
	bool status;
	int map[AREA_MAX_HEIGHT][AREA_MAX_WIDTH];
	void bufferCreate(state *game);
};
