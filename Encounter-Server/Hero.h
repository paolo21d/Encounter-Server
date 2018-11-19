#pragma once
#include "Character.h"
class Hero :	public Character {
	Deck myDeck;
	int strength;
	int intelligence;
	int vitality;
	
public:
	Hero();
	~Hero();
};

