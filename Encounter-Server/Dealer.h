#pragma once
#include "Character.h"
#include "Deck.h"

class Dealer :	public Character {
	Deck soldCards;
	double saleFactor;
	
public:
	Dealer();
	Dealer(Deck&& soldCards_, double saleFactor_);
	~Dealer();

	virtual void interaction(Hero& invader);		//handluj z tym
};

