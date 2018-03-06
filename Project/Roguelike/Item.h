#pragma once

#include "stdafx.h"
#include "Weapon.h"
#include "Consumable.h"
#include "general.h"

#define MIN_ITEM 1
#define MAX_ITEM 3

enum itemTypes { DEFAULT_WEAPON = 0, WEAPON = 1, CONSUMABLE = 2, SPELL = 3 };
class Weapon;
class Consumable;

class Item {
public:
	Item();
	Item(int itemType);
	~Item();
	Weapon *weapon;
	Consumable *consumable;
	int getType();

private:
	std::string type;
};