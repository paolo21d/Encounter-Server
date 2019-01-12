#pragma once
#include "Object.h"
#include "News.h"
#include "Deck.h"
#include <string>

class Character : public Object{
	friend class Game;
	
	Deck myDeck;
	int strength;
	int intelligence;
	int vitality;
	//int id;				//potrzebne do testów, potem może usuniemy
public:
	Character();
	Character(int x_, int y_, int s, int i, int v, string fileName);
	~Character();
	//int getId() const;	// --||--
	
	void addCards(std::vector<int> v);
	void removeCards(std::vector<int> v);
	void changeStrength(int x);
	void changeIntelligence(int x);
	void changeVitality(int x);

	virtual Mode interaction();
	virtual areaType checkAdjacent();
	virtual int freeMoney();
};
