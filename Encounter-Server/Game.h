#pragma once

#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include "Map.h"
#include "News.h"
#include "Communication.h"
#include "Location.h"
#include "Hero.h"
#include <SFML/Network.hpp>

extern const unsigned mapSizeX, mapSizeY;
extern const unsigned areaSizeX, areaSizeY;
extern const unsigned areasX, areasY; 
extern const int STATPRICE;

class Game {
	//////////////////////////////
	////////////////////////////// UWAGA - JEST PUBLIcZNE WSZYSTKO
	//////////////////////////////
public:	
	// dopisać wszędzie korzystanie z mutexa !!!
	std::mutex exploreMutex;
	
	Map map;
	//vector <Card*> allCards;
	Communication communication;
	Location *currentLocation[2];

	News* news[2];
	NewsExplore newsE[2];		//docelowo będą dwa News, po jednym na gracza
	NewsDeal newsD[2];
	NewsFight newsF[2];

	Hero* player[2];
	int locationId[2];
	int playerX[2];
	int playerY[2];

	int dealX[2];
	int dealY[2];
	
	Hero* gameEndsWinnerIs;
//public:
	Game();
	~Game();

	void init(int socnum);
	void game(int socnum, Hero* hero);

	void explore(int id);
	void fight(int id);
	void deal(int id);

////////////	testowe:

	void invalidGame(Hero& myHero, Location& currentLocation);
	int giveMeDirection(sf::TcpSocket& socket);
	
};

