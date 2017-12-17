#include "stdafx.h"
#include "Items.h"

Items Items::generateItem(std::string str) {
	Items item;
	if (str == "Barehand") {
		item.type = str;
		item.accuracyBonus = 0;
		item.damageBonus = 0;
		item.dexMod = 0;
		item.intMod = 0;
		item.strMod = 0.1;
	}
	else if (str == "Sword") {
		item.type = str;
		item.accuracyBonus = 5;
		item.damageBonus = 2;
		item.dexMod = 0.1;
		item.intMod = 0;
		item.strMod = 0.3;
	}
	return item;
}