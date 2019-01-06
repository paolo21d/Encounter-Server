#include "Hero.h"


Hero::Hero() {
}

Hero::~Hero() {
	
}

Hero::Hero(const Deck& myDeck_, int strength_, int vitality_, int intelligence_, int gold_): myDeck(myDeck_), strength(strength_), vitality(vitality_), intelligence(intelligence_), gold(gold_) {
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

