#pragma once
#include "Object.h"
#include "Deck.h"
#include "News.h"

class Chest :	public Object {
	friend class Game;
	
	Deck myDeck;				//karty
	int gold;				//pieniądze w skrzyni	
public:
	Chest();
	Chest(Deck& myDeck_, int gold_);
	~Chest();
	
	virtual int freeMoney();
	virtual Mode interaction();		//odpal skrzynkę
	virtual areaType checkAdjacent();

};

