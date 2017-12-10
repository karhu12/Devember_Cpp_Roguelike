#pragma once

#include "stdafx.h"

class Enemy {
public:
	short health;
	short maxDamage, minDamage;
	short accuracy;
	chtype enemyCharacter;
	static Enemy createEnemy();
};