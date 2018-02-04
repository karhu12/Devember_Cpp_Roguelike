#include "stdafx.h"
#include "Weapon.h"


Weapon::Weapon() {
	int type = randomNumber(1, 3);
	switch (type) {
	case 1:
		weaponType = "Dagger";
		accuracyBonus = 2;
		damageBonus = 0;
		dexMod = 0.1;
		intMod = 0;
		strMod = 0.05;
		break;
	case 2:
		weaponType = "Sword";
		accuracyBonus = 1;
		damageBonus = 1;
		dexMod = 0.05;
		intMod = 0;
		strMod = 0.1;
		break;
	case 3:
		weaponType = "Two-handed sword";
		accuracyBonus = 1;
		damageBonus = 2;
		dexMod = 0;
		intMod = 0;
		strMod = 0.2;
		break;
	default:
		break;
	}
}

Weapon::Weapon(int type) {
	switch (type) {
		case 0:
			weaponType = "Fists";
			accuracyBonus = 0;
			damageBonus = 0;
			dexMod = 0;
			intMod = 0;
			strMod = 0.05;
			break;
		default:
			break;
	}
}

Weapon::~Weapon() {

}

void Weapon::addAbilityModifierDamage(short &damage, short strength, short dexterity, short intelligence) {
	damage += strength * strMod;
	damage += dexterity * dexMod;
	damage += intelligence * intMod;
}