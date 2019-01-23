#pragma once
#include "Object.h"
#include "News.h"
#include "Deck.h"
#include <string>

extern const unsigned STARTINGCARDS;

class Character : public Object{
	friend class Game;
	
	Deck myDeck;
	int strength;
	int intelligence;
	int vitality;
	
public:
	Character();
	Character(int x_, int y_, int s, int i, int v, string fileName);
	~Character();
	
	void addCards(std::vector<int>& v);
	void removeCards(std::vector<int>& v);
	void changeStrength(int x);
	void changeIntelligence(int x);
	void changeVitality(int x);
	void gimmieSomeCardsBabe(std::vector<int>& v);
	Card* kovalskiCardAnalysys(int i);	//na przyszłość połączyć z remoceCards
	int randomCard();

	virtual Mode interaction();
	virtual areaType checkAdjacent();
	virtual int freeMoney();
};
