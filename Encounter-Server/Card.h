#pragma once
class Card {
	string name;
	unsigned strength;
	unsigned intelligence;
	unsigned vitality;
	unsigned value;
public:
	Card(const string &n, const unsigned& str, const unsigned& in, const unsigned& vit, const unsigned& val);
	~Card();

	void setStat(const unsigned& str, const unsigned& in, const unsigned& vit);
	void setValue(const unsigned& val);
	void setName(const string & n);
};

