#pragma once

#include "stdafx.h"

#define MIN_ITEM 1
#define MAX_ITEM 3
enum itemTypes { BAREHAND = 0, DAGGER = 1, SWORD = 2, TWO_H_SWORD = 3 };

class Items {
public:
	std::string type;
	short damageBonus, accuracyBonus;
	double strMod, dexMod, intMod;
	Items generateItem(int type);
};