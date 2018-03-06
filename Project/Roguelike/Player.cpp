#include "stdafx.h"
#include "Player.h"

Player::Player() {
	level = 1;
	health = 25;
	experience = 0;
	strength = 10;
	dexterity = 10;
	intelligence = 10;
	accuracy = 95;
	minDamage = 2;
	maxDamage = 8;
	accuracy = 80;
	xPos = 30;
	yPos = 9;
	itemAmount = 1;
	mainHand = new Item(DEFAULT_WEAPON);
	offHand = new Item(DEFAULT_WEAPON);
	playerCharacter = 'P';
	foregroundColor = COLOR_CYAN;
}

Player::~Player() {
	delete mainHand;
	delete offHand;
	mainHand = NULL;
	offHand = NULL;
}

int Player::playerMovement(Map *map, Tile tile[], char input) {
	if (input == 'd' || input == 'D') {
		if (this->xPos < AREA_MAX_WIDTH - 1) {
			if (tile[map->area[this->yPos][this->xPos + 1]].walkable == true) {
				this->xPos += 1;
				return 1;
			}
			else {
				return 0;
			}
		}
		else {
			return 0;
		}
	}
	if (input == 'a' || input == 'A') {
		if (this->xPos > 0) {
			if (tile[map->area[this->yPos][this->xPos + -1]].walkable == true) {
				this->xPos -= 1;
				return 1;
			}
			else {
				return 0;
			}
		}
		else {
			return 0;
		}
	}
	if (input == 'w' || input == 'W') {
		if (this->yPos > 0) {
			if (tile[map->area[this->yPos - 1][this->xPos]].walkable == true)  {
				this->yPos -= 1;
				return 1;
			}
			else {
				return 0;
			}
		}
		else {
			return 0;
		}
	}
	if (input == 's' || input == 'S') {
		if (this->yPos < AREA_MAX_HEIGHT - 1) {
			if (tile[map->area[this->yPos + 1][this->xPos]].walkable == true) {
				this->yPos += 1;
				return 1;
			}
			else {
				return 0;
			}
		}
		else {
			return 0;
		}
	}
}

char Player::getPlayerInput(Buffer *buffer) {
	input = mvwgetch(buffer->textWindow, 3, 1);
	return input;
}

int Player::playerAttack() {
	unsigned short roll = randomNumber(1, 100);
	short damage;
	if (roll < accuracy + mainHand->weapon->getAccuracy() + offHand->weapon->getAccuracy()) {	/* If roll is lower than player accuracy it hits else miss */
		damage = randomNumber(minDamage, (maxDamage + mainHand->weapon->getDamageBonus() + offHand->weapon->getDamageBonus()));
		mainHand->weapon->addAbilityModifierDamage(damage, strength, dexterity, intelligence);
		offHand->weapon->addAbilityModifierDamage(damage, strength, dexterity, intelligence);
	}
	else {
		damage = 0;
	}
	return damage;
}

void Player::newItemToInventory() {
	Item *newItem = new Item;	/* Create new item and place it in players inventory map */
	items[itemAmount] = newItem;
	itemAmount++;
}