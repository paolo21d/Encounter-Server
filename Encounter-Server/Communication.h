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


#include "Game.h"
#include "Location.h"

extern const unsigned mapSizeX, mapSizeY;
extern const unsigned areaSizeX, areaSizeY;
extern const unsigned areasCountX;
extern const unsigned areasCountY;

using namespace std;
class Communication {

	mutex mm;
	sf::TcpSocket tabsoc[2];

public:
	Communication();
	~Communication();

	void srdata(int num, int socnum);
	void sendMap(const Map& map, const int &num);

	void sendData(int num, int socnum);
	void receiveData(int num, int socnum);
	void sendMap(int socnum);
	
	///////		testowe:
	
	void startConnection();
	void testSendImg();
};

#endif // !COMMUNICATION_H
