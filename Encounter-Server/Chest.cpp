#include "Chest.h"
#include "Hero.h"

///////////////////////		KONSTRUKTORY

Chest::Chest() {
}

Chest::Chest(int x_, int y_, int gold_, string fileName): gold(gold_) {
	setX(x_);
	setY(y_);
	setFileName(fileName);
	myDeck.fill(STARTINGCARDS);
}

Chest::Chest(Deck& myDeck_, int gold_): gold(gold_){
	myDeck = myDeck_;
}

Chest::~Chest() {	
}

//////////////////////		VIRTUALNE

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

