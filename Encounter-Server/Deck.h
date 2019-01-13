#pragma once
#ifndef DECK_H
#define DECK_H

#include "Card.h"
#include <vector>
using namespace std;
class Deck {
	friend class Game;
	vector<Card*> deck;

public:
	Deck();
	~Deck();

	void addCard(const int cardNum);
	void removeCard(const int cardNum);
	void fill(int amount);

};

#endif // !DECK_H