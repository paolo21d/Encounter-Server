#pragma once
#ifndef DECK_H
#define DECK_H

#include "Card.h"
#include <vector>
using namespace std;
class Deck {
	vector<Card> deck;

public:
	Deck();
	~Deck();

	void addCard(const Card& card);

};

#endif // !DECK_H