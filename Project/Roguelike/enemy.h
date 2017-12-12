#pragma once

#include "stdafx.h"

class Enemy {
public:
	short health;
	short maxDamage, minDamage;
	short accuracy;
	short experienceGiven;
	bool alive;
	chtype enemyCharacter;
	void Enemy::enemyValues();
};