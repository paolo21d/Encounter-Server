#pragma once
#include "Character.h"
#include "Deck.h"
#include "News.h"

class Mob :	public Character {
	Deck myDeck;
	int strength;
	int vitality;
	int intelligence;

public:
	Mob();
	Mob(const Deck& myDeck_, int strength_, int vitality_, int intelligence_);
	~Mob();

	virtual Mode interaction();		//walcz
};
