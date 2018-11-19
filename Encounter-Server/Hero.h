#pragma once
#include "Character.h"
#include "Deck.h"

class Hero :	public Character {
	Deck myDeck;
	int strength;
	int intelligence;
	int vitality;
	int gold;
	
public:
	Hero();
	Hero(const Deck& myDeck_, int strength_, int vitality_, int intelligence_, int gold_ = 0);
	~Hero();
		
	void addGold(int newGold);
	void removeGold(int spentGold);
	void addCards(const Deck& newDeck);
	void removeCards(const Deck& lostCards);
	virtual void interaction(const Hero& invader);		//walcz
};

