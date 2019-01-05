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

void Hero::addCards(std::vector<int> v){
	for(int i: v)
	{
		myDeck.addCard(i);
	}
}

void Hero::removeCards(const Deck& lostCards){
	//myDeck.remove(lostCards);
}

void Hero::changeStrength(int x){
	strength += x;
}
void Hero::changeIntelligence(int x){
	intelligence += x;
}
void Hero::changeVitality(int x){
	vitality += x;
}

Mode Hero::interaction(){
	return FIGHT;
}	

