#pragma once

#include <iostream>
#include <SFML\Network.hpp>
#include <thread>
#include <mutex>
#include <vector>
#include "Map.h"
//using namespace std;
class Game {
	//dane calej gry
	Map map;

	std::mutex mm;
	sf::TcpSocket tabsoc[2];
public:
	Game();
	~Game();

	void startConnection();
	void game(int num, int socnum);
	void sendGraphics();
	void sendG(unsigned socnum);
	void startGame();
	//void startG(unsigned socnum);
};



