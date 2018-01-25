#include "stdafx.h"
#include "enemy.h"

Enemy::Enemy() {
	health = randomNumber(15, 30);
	minDamage = randomNumber(1, 3);
	maxDamage = randomNumber(4, 6);
	accuracy = randomNumber(50, 80);
	experienceGiven = randomNumber(75, 150);
	alive = true;
}
