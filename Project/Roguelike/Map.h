#pragma once

class Map {
public:
	std::string environment;
	short area[AREA_MAX_HEIGHT][AREA_MAX_WIDTH];
	short areaX, areaY, areaZ;
	Map();
	~Map();
};
