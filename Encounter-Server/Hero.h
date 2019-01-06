#pragma once
#include "Character.h"
#include "Deck.h"
#include "News.h"

class Hero :	public Character {
	friend class Game;

	int gold;
public:
	Hero();
	Hero(const Deck& myDeck_, int strength_, int vitality_, int intelligence_, int gold_ = 0);
	~Hero();
	

	void addGold(int newGold);
	void removeGold(int spentGold);
	int getGold();

};

