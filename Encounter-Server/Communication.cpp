#include "Communication.h"
#include <SFML/Network.hpp>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;
using namespace sf;


Communication::Communication() {
}

Communication::~Communication() {
}

void Communication::sendMap(const Map& map, const int num) {

//trzeba dodać wysyłanie grafik

// przesyłanie lokacji i obiektów
	Packet packet;
	packet << mapSizeX << mapSizeY;
	packet << static_cast<int>(map.locations.size());
	packet << areaSizeX << areaSizeY;
	for (int i = 0; i < map.locations.size(); ++i) { //przeslanie lokacji
		packet << map.locations[i]->getId() << map.locations[i]->getSrc();
		vector<Object*> tempObj;
		for (int k = 0; k < areasCountX; ++k) {
			for (int j = 0; j < areasCountY; ++j) {
				if (map.locations[i]->occupation[k][j] != nullptr)
					tempObj.push_back(map.locations[i]->occupation[k][j]);
			}
		}
		packet << static_cast<int>(tempObj.size());
		for (int i = 0; i < tempObj.size(); ++i) { //przeslanie objektow w lokacji
			packet << tempObj[i]->getId() << tempObj[i]->getX() << tempObj[i]->getY() << tempObj[i]->getFileName();
		}
	}

// przeslanie kart
	packet << static_cast<int>(Map::allCards.size());
	for (int i = 0; i < Map::allCards.size(); ++i) {
		packet << Map::allCards[i]->getId() << Map::allCards[i]->getSrc() << Map::allCards[i]->getName() << Map::allCards[i]->getDescription() << Map::allCards[i]->getCostMana() << Map::allCards[i]->getDamage() << Map::allCards[i]->getCostGold();
	}
	tabsoc[num].send(packet);
	cout << "Wyslalem dane mapy do klienta " << num << endl;
}


