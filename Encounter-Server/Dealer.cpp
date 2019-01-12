#include "Dealer.h"

//////////////////		KONSTRUKTORY

Dealer::Dealer() {
}

Dealer::Dealer(int x_, int y_, double saleFactor_, string fileName): saleFactor(saleFactor_){
	setX(x_);
	setY(y_);
	setFileName(fileName);
}

Dealer::Dealer(Deck& soldCards_, double saleFactor_): saleFactor(saleFactor){
	soldCards = soldCards_;
}

Dealer::~Dealer() {
	
}

/////////////////		VIRTUALNE

int Dealer::freeMoney()
{
	return 0;
}

Mode Dealer::interaction()
{
	return DEAL;
	//możliwe, że karty będą int'ami, więc nie ruszam tego na razie...
}

///////////////////		POZOSTAŁE

void Dealer::removeCards(std::vector<int> v)
{
	for(int i: v)
	{
		soldCards.removeCard(i);
	}
}