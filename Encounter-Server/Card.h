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
	unsigned damage; // to s� punkty obrazen zadawane
	
	//uchwyt do Slider - obrazek

public:
	Card();
	Card(const string n, const int dmg, const int mana, const int money, const int num);
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
	unsigned getCostGold() const;
	unsigned getDamage() const;

	virtual void action(); 		//dla Health i Mana
	virtual void action(Card* card);	//przeciarzenie dla Monster, Removal i Buff
};

#endif // !CARD_H
