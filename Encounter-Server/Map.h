#pragma once
#ifndef MAP_H
#define MAP_H
#include "Location.h"
#include "Card.h"
#include <vector>
//#include <SFML\Graphics.hpp>

extern const unsigned mapSizeX, mapSizeY;
extern const unsigned areaSizeX, areaSizeY;

using namespace std;
class Map {
	friend class Game;
	friend class Communication;
	
	vector <Location> locations;
	
public:
	static vector <Card*> allCards;

	Map();
	~Map();

	//void receiveMap(); // pobiera pliki mapy- grafiki lokacji, skrzynek, handlarzy, kart i zapisuje to w folderze na komputerze, ale z kazdym uruchomieniem aplikacji usuwa ten folder i pobiera od nowa te grafiki
};

#endif // !MAP_H
