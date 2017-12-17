#include "stdafx.h"
#include "enemy.h"
#include "general.h"

void Enemy::enemyValues() {
	this->health = randomNumber(15, 30);
	this->minDamage = randomNumber(1, 3);
	this->maxDamage = randomNumber(4, 6);
	this->accuracy = randomNumber(50, 80);
	this->experienceGiven = randomNumber(75, 150);
	this->alive = true;
}