#include "stdafx.h"
#include "Item.h"


Item::Item() {
	int itemType = randomNumber(1, 3);
	switch (itemType) {
		case WEAPON:
			type = "Weapon";
			weapon = new Weapon;
			break;
		case CONSUMABLE:
			type = "Consumable";
			consumable = new Consumable;
			break;
		case SPELL:
			type = "Spell";
			break;
		default:
			break;
}
}

Item::Item(int itemType) {
	switch (itemType) {
	case DEFAULT_WEAPON:
		type = "Weapon";
		weapon = new Weapon(DEFAULT_WEAPON);
		break;
	case WEAPON:
		type = "Weapon";
		weapon = new Weapon;
		break;
	case CONSUMABLE:
		type = "Consumable";
		break;
	case SPELL:
		type = "Spell";
		break;
	default:
		break;
	}
}

Item::~Item() {
		delete weapon;
		weapon = NULL;
}