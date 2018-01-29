#include "stdafx.h"
#include "Weapon.h"


Weapon::Weapon() {
	
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