#include <iostream>
#include <thread>
#include "Object.h"
#include "Nature.h"
#include "Character.h"
#include "Hero.h"
#include "News.h"
#include "Dealer.h"
#include "Chest.h"
#include "Card.h"
#include "Deck.h"
#include "Game.h"
#include <SFML/Network.hpp>
#include <time.h>

using namespace std;
using namespace sf;
/*
NewsExplore news;
int char_id = 0;
const unsigned mapSizeX = 100, mapSizeY = 100;
const unsigned areaSizeX = 25, areaSizeY = 25;

int main()
{
	Game game;
	Map map;
	Location location;

	Deck emptyDeck, emptyDeck2, emptyDeck3;
	Hero elfhells(emptyDeck, 10, 12, 8, 100);	
	Mob grishnak(emptyDeck, 6, 13, 4);
	Mob shagrat(emptyDeck, 3, 14, 3);
	Mob gothmog(emptyDeck, 3, 14, 3);
	Mob gorbag(emptyDeck, 3, 14, 3);
	Chest precious(emptyDeck3, 20);
	Dealer elrond(emptyDeck2, 1.3);

	for(int i: {0, 1, 2, 3})
		for(int j: {0, 1, 2, 3})
			location.ocupation[i][j] = nullptr;

	location.ocupation[3][1] = &grishnak;
	location.ocupation[1][2] = &shagrat;
	location.ocupation[0][3] = &gorbag;
	location.ocupation[3][3] = &gothmog;
	location.ocupation[1][2] = &elrond;
	location.ocupation[0][2] = &precious;
	
	game.invalidGame(elfhells, location);
}
*/

const unsigned mapSizeX = 1000, mapSizeY = 550;
const unsigned areaSizeX = 100, areaSizeY = 50;
const unsigned areasX = mapSizeX/areaSizeX, areasY = mapSizeY/areaSizeY;
const int BASICSTATS = 10;
const unsigned locationAmount = 1;
const int STATPRICE = 1;
const unsigned STARTINGCARDS = 5;
const unsigned CARDSAMOUNT = 5;

int main()
{
	srand(time(NULL));

	Game game;
	
	Hero einz;
	einz.setCurrLocationId(0);
	einz.setX(4);
	einz.setY(5);
	Hero tzwei;
	tzwei.setCurrLocationId(0);
	tzwei.setX(5);
	tzwei.setY(5);

	int portNumber = 2012;
	TcpListener listener;

	listener.listen(portNumber);
	for (unsigned i = 0; i < 2; ++i) {
		listener.accept(game.communication.tabsoc[i]);
		cout << "Nawiazano polaczenie z klientem: " << i << endl;
	}
	cout << "Robie watki do wysylania mapy:" << endl;
	thread uno(&Game::init, &game, 0);
	thread due(&Game::init, &game, 1);

	uno.join();
	due.join();

	thread tre(&Game::game, &game, 0, &einz);
	thread quattro(&Game::game, &game, 1, &tzwei);

	tre.join();
	quattro.join();
}