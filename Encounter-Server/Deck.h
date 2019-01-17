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
	void fillRandomCards(vector<int>& v);
	int randomCard();
	Card* kovalskiSupport(int i);

	void print();
};

#endif // !DECK_H