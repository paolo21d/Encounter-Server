#pragma once
#include "Object.h"
#include "News.h"
#include "Deck.h"
#include <string>

class Character : public Object{
	friend class Game;
	
	std::string name;
	Deck myDeck;
	int strength;
	int intelligence;
	int vitality;
	//int id;				//potrzebne do testów, potem może usuniemy
public:
	Character();
	~Character();
	//int getId() const;	// --||--
	
	void addCards(std::vector<int> v);
	void removeCards(std::vector<int> v);
	void changeStrength(int x);
	void changeIntelligence(int x);
	void changeVitality(int x);

	virtual Mode interaction();
	virtual areaType checkAdjacent();
};
