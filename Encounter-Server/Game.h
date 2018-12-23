#pragma once

#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include "Map.h"
#include "News.h"
#include <SFML/Network.hpp>

class Game {
	//dane calej gry
	Map map;
	News news;		//docelowo będą dwa News, po jednym na gracza

	std::mutex mm;
	//sf::TcpSocket tabsoc[2];
public:
	Game();
	~Game();

	void invalidGame(Hero& myHero, Location& currentLocation);
	//sf::TcpSocket startConnection(int pornNumber);  		//nie używam
	int giveMeDirection(sf::TcpSocket& socket);
	void game(int num, int socnum);
	void sendGraphics();
	void sendG(unsigned socnum);
	void startGame();
	//void startG(unsigned socnum);
};



