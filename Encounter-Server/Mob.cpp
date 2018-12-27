#include "Mob.h"
#include "Hero.h"
#include "News.h"


Mob::Mob() {
}

Mob::~Mob() {
}

Mob::Mob(const Deck& myDeck_, int strength_, int vitality_, int intelligence_): myDeck(myDeck_), strength(strength_), vitality(vitality_), intelligence(intelligence_) {
}

void Mob::interaction(Hero& invader, NewsExplore& news){
	news.gameMode = FIGHT;
	return;
}	

