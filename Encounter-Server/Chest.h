#pragma once
#include "Object.h"
#include "Deck.h"
#include "News.h"

extern const unsigned STARTINGCARDS;

class Chest :	public Object {
	friend class Game;
	
	Deck myDeck;				//karty
	int gold;				//pieniądze w skrzyni	
public:
	Chest();
	Chest(int x_, int y_, int gold_, std::string fileName);
	Chest(Deck& myDeck_, int gold_);
	~Chest();
	
	virtual int freeMoney();
	virtual Mode interaction();		//odpal skrzynkę
	virtual areaType checkAdjacent();

};

