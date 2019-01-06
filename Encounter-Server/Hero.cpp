#include "Hero.h"


Hero::Hero() {
}

Hero::~Hero() {

}

Hero::Hero(int gold_): gold(gold_) {
}

void Hero::addGold(int newGold){
	gold += newGold;
}

void Hero::removeGold(int spentGold){
	gold -= spentGold;
}	

int Hero::getGold() {
	return gold;
}

