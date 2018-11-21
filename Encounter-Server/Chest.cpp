#include "Chest.h"
#include "Hero.h"

Chest::Chest() {
}
Chest::Chest(Deck&& myDeck_, int gold_): gold(gold_){
	myDeck = myDeck_;
}

Chest::~Chest() {
}

void Chest::interaction(Hero& invader){
	invader.addGold(gold);
	invader.addCards(myDeck);
}
