#include "Mob.h"
#include "Hero.h"

extern bool FIGHT;
extern Character& firstFighter;
extern Character& secondFighter;

Mob::Mob() {
}

Mob::~Mob() {
}

Mob::Mob(const Deck& myDeck_, int strength_, int vitality_, int intelligence_): myDeck(myDeck_), strength(strength_), vitality(vitality_), intelligence(intelligence_) {
}

void Mob::interaction(const Hero& invader){
	FIGHT = true;
	firstFighter = *this;
	secondFighter = invader;
	return;
}	

