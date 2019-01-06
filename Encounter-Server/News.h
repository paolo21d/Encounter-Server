#ifndef NEWS_H
#define NEWS_H
#include <iostream>
#include <fstream>
#include <vector>
#include "Deck.h"
#include "SFML/Network.hpp"


enum Mode { EXPLORE, FIGHT, DEAL };
enum areaType { EMPTY, IMPASSABLE, INTERACTING};

class News {
public:
	Mode gameMode;

	News();
};

class NewsExplore: public News {
public:
	NewsExplore(Mode mode, int posX, int posY);
	NewsExplore();

	areaType adjacent[4]; //0-góra, 1-prawa, 2-dół, 3-lewa //wysylane z serwera do klienta
	int positionX, positionY; //wysylane od klienta do serwera
	int oponentLocationId;
	int oponentX, oponentY;

	friend std::ostream& operator<<(std::ostream& os, const NewsExplore& x);
	friend sf::Packet& operator<<(sf::Packet& pckt, const NewsExplore& x);
	friend sf::Packet& operator >> (sf::Packet& pckt, NewsExplore& x);
};

class NewsDeal: public News {
public:
	NewsDeal();

	bool accept;
	int areaToGoBackAfterDealX, areaToGoBackAfterDealY;
	double dealerFactor;
	int cardAmount;
	std::vector <int> cardsId;
	int boostStr, boostVit, boostInt;
	int income;		// == 0 jeśli na polu jest handlarz; > 0 jeśli jest skrzynka (i oznacza ilość złota w skrzynce)

	friend sf::Packet& operator<<(sf::Packet& pckt, const NewsDeal& x);
	friend sf::Packet& operator>>(sf::Packet& pckt, NewsDeal& x);
};

class NewsFight: public News {
public:
	// [0] - moje; [1] - przeciwnika
	bool youWon;
	int strength[2];
	int intelligence[2];
	int vitality[2];
	int cardAmount[2];
	std::vector<int> cardsId[2];	// posiadane karty
	int chosenCard;

	NewsFight();
	friend sf::Packet& operator<<(sf::Packet& pckt, const NewsFight& x);
	friend sf::Packet& operator>>(sf::Packet& pckt, NewsFight& x);
};
#endif
