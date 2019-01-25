#pragma once
/*////////////////////////////////////////////////////////////////////////////
Obiekt klasy game jest całą grą. Istnieje 1 obiekt na grę (lokalny w main) - jest niszczony po zakończeniu
Prawie wszystkie pola są 2-elementowymi tablicami - każdy wątek/klient ma dedykowane dla siebie.

//////////////////////////////////////////////////////////////////////////////*/
#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include "Map.h"
#include "News.h"
#include "Communication.h"
#include "Location.h"
#include "Hero.h"
#include "semafor.h"
#include <SFML/Network.hpp>

extern const unsigned mapSizeX, mapSizeY;
extern const unsigned areaSizeX, areaSizeY;
extern const unsigned areasX, areasY; 
extern const int STATPRICE;

class Game {
	//////////////////////////////
	////////////////////////////// JEST PUBLIcZNE WSZYSTKO
	//////////////////////////////
public:	

	bool uwagaNaPodrabianca;	// zmienne potrzebne do powiązania ze sobą trybów
	std::mutex exploreMutex;
	Semaphore sem1;
	Semaphore sem2;
	Map map;
	std::mutex aaa;
	Hero* gameEndsWinnerIs;
	bool quitThreads[2];

	Communication communication;
	Location *currentLocation[2];

	News* news[2];				// zmienne potrzebne do obsługi komunikacji z klientem
	NewsExplore newsE[2];
	NewsDeal newsD[2];
	NewsFight newsF[2];

	Hero* player[2];			// zmienne potrzebne do obsługi eksploracji
	int locationId[2];
	int playerX[2];
	int playerY[2];

	int dealX[2];				// zmienne potrzebne do obsługi handlu
	int dealY[2];
	int areaAfterDealX[2];
	int areaAfterDealY[2];

<<<<<<< HEAD
	Character* myOpponent[2];	// zmienne potrzebne do obsługi walki
=======
	Hero* gameEndsWinnerIs;
	Character* myOpponent[2];
>>>>>>> parent of 3520968... działa fight z przeciwnikiem
	int fightAreaX[2];
	int fightAreaY[2];
	int mobIndexInLocationArray;
	int mobIndexInObjectArray;

//public:
	Game();
	~Game();

	void init(int socnum);
	void game(int socnum, Hero* hero);

	void explore(int id);
	void fight(int id);
	void deal(int id);

};

