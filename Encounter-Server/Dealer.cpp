#include "Dealer.h"
#include "News.h"

extern News news;

Dealer::Dealer() {
}

Dealer::Dealer(Deck&& soldCards_, double saleFactor_): saleFactor(saleFactor){
	soldCards = soldCards_;
}

Dealer::~Dealer() {
}

void Dealer::interaction(Hero& invader){
	news.gameMode = DEAL;
	news.SALEFACTOR = saleFactor;
	//możliwe, że karty będą int'ami, więc nie ruszam tego na razie...
}
