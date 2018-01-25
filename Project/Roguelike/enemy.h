#pragma once

#include "stdafx.h"
#include "general.h"

class Enemy {
public:
	Enemy();
	short health;
	short maxDamage, minDamage;
	short accuracy;
	short experienceGiven;
	bool alive;
	chtype enemyCharacter;
};