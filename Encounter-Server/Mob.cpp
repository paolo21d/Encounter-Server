#include "Mob.h"
#include "Hero.h"
#include "News.h"

extern News news;

Mob::Mob() {
}

Mob::~Mob() {
}

Mob::Mob(const Deck& myDeck_, int strength_, int vitality_, int intelligence_): myDeck(myDeck_), strength(strength_), vitality(vitality_), intelligence(intelligence_) {
}

void Mob::interaction(const Hero& invader){
	news.gameMode = FIGHT;
	news.firstFighter = this;
	news.secondFighter = &invader;
	return;
}	

