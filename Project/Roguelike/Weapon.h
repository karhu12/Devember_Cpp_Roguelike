#pragma once
#include "Item.h"

enum weaponTypes { BAREHAND = 0, DAGGER = 1, SWORD = 2, TWO_H_SWORD = 3 };

class Weapon {
public:
	Weapon();
	Weapon(int);
	~Weapon();
	short getAccuracy() const { return accuracyBonus; }
	short getDamageBonus() const { return damageBonus; }
	std::string getWeaponType() const { return weaponType; }
	void addAbilityModifierDamage(short &damage, short strength, short dexterity, short intelligence);

private:
	short damageBonus, accuracyBonus;
	double strMod, dexMod, intMod;
	std::string weaponType;
};

