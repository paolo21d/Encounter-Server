#pragma once
#include <string>
using namespace std;
class Card {
	string name;
	string description;
	unsigned costMana;
	unsigned price;
	//uchwyt do Slider - obrazek
	
public:
	Card(const string &n, const unsigned& dmg, const unsigned& costmana);
	~Card();

	//void setStat(const unsigned& dmg, const unsigned& costI);
	void setPrice(const unsigned& pr);
	void setName(const string& n);
	void setDescription(const string& desc);
};

