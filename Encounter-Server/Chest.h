#pragma once
#include "Object.h"
#include "Deck.h"

class Chest :	public Object {
	Deck myDeck;				//kart
	int gold;				//pieniądze w skrzyni	
public:
	Chest();
	Chest(Deck&& myDeck_, int gold_);
	~Chest();
	
	virtual void interaction(Hero& invader);		//odpal skrzynkę
};

