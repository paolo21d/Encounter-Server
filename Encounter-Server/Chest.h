#pragma once
#include "Object.h"
#include "Deck.h"

class Chest :	public Object {

	Deck myDeck;				//kart
	int gold;				//pieniądze w skrzyni	
public:
	Chest();
	~Chest();
};

