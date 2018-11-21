#include "Dealer.h"

extern bool DEAL;
extern double SALEFACTOR;

Dealer::Dealer() {
}

Dealer::Dealer(Deck&& soldCards_, double saleFactor_): saleFactor(saleFactor){
	soldCards = soldCards_;
}

Dealer::~Dealer() {
}

void Dealer::interaction(Hero& invader){
	DEAL = true;
	SALEFACTOR = saleFactor;
	//możliwe, że karty będą int'ami, więc nie ruszam tego na razie...
}
