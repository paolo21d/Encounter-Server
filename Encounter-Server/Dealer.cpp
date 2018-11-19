#include "Dealer.h"


Dealer::Dealer() {
}

Dealer::Dealer(Deck&& soldCards_, double saleFactor_): saleFactor(saleFactor){
	soldCards = soldCards_;
}

Dealer::~Dealer() {
}

void Dealer::interaction(const Hero& invader){
	//ustaw dane do wysłania na handlowanie
}
