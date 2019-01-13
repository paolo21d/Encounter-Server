#pragma once
#include "Character.h"
#include "Deck.h"
#include "News.h"

extern const int BASICSTATS;

class Hero :	public Character {
	friend class Game;

	int gold;
	int currentLocation;

public:
	Hero();
	~Hero();
	
	int getCurrLocationId();
	void setCurrLocationId(int newLocation);
	void addGold(int newGold);
	void removeGold(int spentGold);
	int getGold();
	//void setPosition();
};
