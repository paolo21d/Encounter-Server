#pragma once
#include "Character.h"
#include "Deck.h"
#include "News.h"

class Hero :	public Character {

	Deck myDeck;
	int strength;
	int intelligence;
	int vitality;
	int gold;
	
public:
	Hero();
	Hero(const Deck& myDeck_, int strength_, int vitality_, int intelligence_, int gold_ = 0);
	~Hero();
	

	void addGold(int newGold);
	void removeGold(int spentGold);
	int getGold();

	void addCards(std::vector<int> v);
	void removeCards(const Deck& lostCards);
	void changeStrength(int x);
	void changeIntelligence(int x);
	void changeVitality(int x);
	virtual Mode interaction();		//walcz
};

