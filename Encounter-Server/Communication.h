#pragma once
#ifndef COMMUNICATION_H
#define COMMUNICATION_H

#include <iostream>
#include <thread>
#include <string>
#include <mutex>
#include <vector>
#include <thread>
#include <SFML/Network.hpp>


#include "Location.h"
#include "Map.h"

extern const unsigned mapSizeX, mapSizeY;
extern const unsigned areaSizeX, areaSizeY;
extern const unsigned areasCountX;
extern const unsigned areasCountY;


class Communication {
	//////////////////////////////
	////////////////////////////// UWAGA - JEST PUBLIcZNE WSZYSTKO
	//////////////////////////////

public:
	friend class Game;
	mutex mm;
	sf::TcpSocket tabsoc[2];
	sf::Socket::Status status[2];

//public:
	Communication();
	~Communication();

	void sendMap(const Map& map, const int num);

};

#endif // !COMMUNICATION_H
