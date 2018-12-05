#ifndef NEWS_H
#define NEWS_H
#include <iostream>
#include <fstream>
#include "Character.h"
#include "Deck.h"

enum Mode{EXPLORE, FIGHT, DEAL};

struct News{

	Mode gameMode;
	const Character* firstFighter;
	const Character* secondFighter;

	double dealerFactor;
	Deck cardsForSale;	

	friend std::ostream& operator<<(std::ostream& os, const News& x);

};

#endif
