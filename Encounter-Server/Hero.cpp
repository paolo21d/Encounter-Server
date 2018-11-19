#include "Hero.h"

extern bool FIGHT;
extern Character& firstFighter;
extern Character& secondFighter;

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

void Hero::addCards(const Deck& newDeck){
	//myDeck.extend(newDeck);
}

void Hero::removeCards(const Deck& lostCards){
	myDeck.remove(lostCards);
}

void Hero::interaction(const Hero& invader){
	FIGHT = true;
	firstFighter = *this;
	secondFighter = invader;
	return;
}	

