#include "stdafx.h"
#include "enemy.h"
#include "general.h"

Enemy Enemy::createEnemy() {
	Enemy enemy;
	enemy.health = randomNumber(10, 10);
	enemy.minDamage = randomNumber(1, 2);
	enemy.maxDamage = randomNumber(3, 5);
	enemy.accuracy = randomNumber(60, 35);
	return enemy;
}