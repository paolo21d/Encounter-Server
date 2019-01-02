#pragma once

#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include "Map.h"
#include "News.h"
#include "Communication.h"
#include <SFML/Network.hpp>

class Game {
	//dane calej gry
	Map map;
	Communication communication;
	NewsExplore news;		//docelowo będą dwa News, po jednym na gracza

	std::mutex mm;

public:
	Game();
	~Game();

	void init(int socnum);
	void game(int socnum);

////////////	testowe:
	void invalidGame(Hero& myHero, Location& currentLocation);
	int giveMeDirection(sf::TcpSocket& socket);
	
};

