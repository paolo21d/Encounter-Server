#pragma once
#ifndef CARD_H
#define CARD_H

#include <string>
using namespace std;
class Card { 
	friend class Game;
	int id;
	string srcName;

	string name;
	string description;
	unsigned costMana;
	unsigned price;
		
public:
	Card();
	Card(const string &n, const unsigned& dmg, const unsigned& costmana);
	~Card();

	//void setStat(const unsigned& dmg, const unsigned& costI);
	void setPrice(const unsigned& pr);
	void setName(const string& n);
	void setDescription(const string& desc);

	int getId() const;
	string getName() const;
	string getDescription() const;
	string getSrc() const;
	unsigned getCostMana() const;
	unsigned getPrice() const; 

	virtual void action(); 		//dla Health i Mana
	virtual void action(Card* card);	//przeciarzenie dla Monster, Removal i Buff
};

#endif // !CARD_H
