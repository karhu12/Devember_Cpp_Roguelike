#pragma once

#include "stdafx.h"

class Enemy {
public:
	short health;
	short maxDamage, minDamage;
	short accuracy;
	bool alive;
	chtype enemyCharacter;
	void Enemy::enemyValues();
};