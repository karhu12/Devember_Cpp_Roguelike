#pragma once
#include "stdafx.h"

class Items {
public:
	std::string type;
	short damageBonus, accuracyBonus;
	double strMod, dexMod, intMod;
	Items generateItem(std::string str);
};