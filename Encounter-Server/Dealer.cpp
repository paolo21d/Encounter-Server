#include "Dealer.h"
#include "News.h"


Dealer::Dealer() {
}

Dealer::Dealer(Deck& soldCards_, double saleFactor_): saleFactor(saleFactor){
	soldCards = soldCards_;
}

Dealer::~Dealer() {
}

void Dealer::interaction(Hero& invader, News& news){
	news.gameMode = DEAL;
	news.dealerFactor = saleFactor;
	//możliwe, że karty będą int'ami, więc nie ruszam tego na razie...
}
