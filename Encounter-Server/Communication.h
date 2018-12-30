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
	vector <sf::TcpSocket> vecsoc;
	sf::TcpSocket tabsoc[2];
	Game game;

	//pola do komunikacji miedzy server-klient
	bool readFromBuffSC1, readFromBuffSC2;
	
	sf::TcpListener listener;
	vector<thread> th;
public:
	Communication();
	~Communication();

	void srdata(int num, int socnum);
	void sendMap(const Map& map, const int &num);

	void startConnection();
	void sendData(int num, int socnum);
	void receiveData(int num, int socnum);
	void initialSend(int socnum);
	void testSendImg();
};

#endif // !COMMUNICATION_H