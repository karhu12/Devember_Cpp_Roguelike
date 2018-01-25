#include "stdafx.h"
#include "Items.h"


Items Items::generateItem(int type) {
	Items item;
	if (type == BAREHAND) {
		item.type = "Fists";
		item.accuracyBonus = 0;
		item.damageBonus = 0;
		item.dexMod = 0;
		item.intMod = 0;
		item.strMod = 0.05;
	}
	else if (type == DAGGER) {
		item.type = "Dagger";
		item.accuracyBonus = 3;
		item.damageBonus = 0;
		item.dexMod = 0.15;
		item.intMod = 0;
		item.strMod = 0.05;
	}
	else if (type == SWORD) {
		item.type = "Sword";
		item.accuracyBonus = 5;
		item.damageBonus = 1;
		item.dexMod = 0.1;
		item.intMod = 0;
		item.strMod = 0.15;
	}
	else if (type == TWO_H_SWORD) {
		item.type = "Sword";
		item.accuracyBonus = 10;
		item.damageBonus = 3;
		item.dexMod = 0;
		item.intMod = 0;
		item.strMod = 0.4;
	}
	return item;
}