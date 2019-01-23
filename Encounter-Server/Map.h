#pragma once
#ifndef MAP_H
#define MAP_H
#include "Location.h"
#include "Card.h"
#include <vector>

extern const unsigned mapSizeX, mapSizeY;
extern const unsigned areaSizeX, areaSizeY;
extern const unsigned locationAmount;
extern const unsigned CARDSAMOUNT;

using namespace std;
class Map {
	friend class Game;
	friend class Communication;
	
	vector <Location*> locations;
	
public:
	static vector <Card*> allCards;
	Map();
	~Map();

};

#endif // !MAP_H
