#pragma once

class Map {
public:
	std::string environment;						/* Environment type can be used in generation */
	short area[AREA_MAX_HEIGHT][AREA_MAX_WIDTH];	/* Two dimensional array to store all the tiles in map */
	short areaX, areaY, areaZ;						/* This objects position in world */
	static Map createMap();
};
