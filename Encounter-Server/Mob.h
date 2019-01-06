#pragma once
#include "Character.h"
#include "Deck.h"
#include "News.h"

class Mob :	public Character {
	friend class Game;

public:
	Mob();
	Mob(const Deck& myDeck_, int strength_, int vitality_, int intelligence_);
	~Mob();

};
