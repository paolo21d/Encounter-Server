#include "Chest.h"
#include "Hero.h"

Chest::Chest() {
}

Chest::Chest(Deck& myDeck_, int gold_): gold(gold_){
	myDeck = myDeck_;
}

Chest::~Chest() {
	
}

int Chest::freeMoney()
{
	return gold;
}

Mode Chest::interaction(){
	return DEAL;
}

areaType Chest::checkAdjacent()
{
	return INTERACTING;
}

