#pragma once
#include "Character.h"
#include "Deck.h"
#include "News.h"
#include "Hero.h"
#include <vector>

extern const unsigned STARTINGCARDS;

class Dealer :	public Character {
	friend class Game;
	Deck soldCards;
	double saleFactor;
	
public:
	Dealer();
	Dealer(int x_, int y_, double saleFactor_, std::string fileName);
	Dealer(Deck& soldCards_, double saleFactor_);
	~Dealer();

	virtual int freeMoney();
	virtual Mode interaction();		//handluj z tym
	void removeCards(std::vector<int> v);
	void printCards();
};

