#include "Dealer.h"


Dealer::Dealer() {
}

Dealer::Dealer(Deck& soldCards_, double saleFactor_): saleFactor(saleFactor){
	soldCards = soldCards_;
}

Dealer::~Dealer() {
}

int Dealer::freeMoney()
{
	return 0;
}

Mode Dealer::interaction()
{
	return DEAL;
	//możliwe, że karty będą int'ami, więc nie ruszam tego na razie...
}

void Dealer::removeCards(std::vector<int> v)
{
	for(int i: v)
	{
		soldCards.removeCard(i);
	}
}