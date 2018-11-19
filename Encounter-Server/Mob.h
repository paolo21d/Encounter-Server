#pragma once
#include "Character.h"

class Mob :	public Character {

	Deck myDeck;
	int strength;
	int vitality;
	int intelligence;

public:
	Mob();
	~Mob();
};

