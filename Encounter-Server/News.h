#ifndef NEWS_H
#define NEWS_H
#include <iostream>
#include <fstream>
#include "Deck.h"
#include "SFML/Network.hpp"


enum Mode { EXPLORE, FIGHT, DEAL };
enum areaType { EMPTY, IMPASSABLE, INTERACTING};


class NewsExplore{
public:
	NewsExplore(Mode mode, int posX, int posY);
	NewsExplore();

	Mode gameMode;
	areaType adjacent[4]; //0-góra, 1-prawa, 2-dół, 3-lewa //wysylane z serwera do klienta
	int positionX, positionY; //wysylane od klienta do serwera
	int oponentLocationId;
	int oponentX, oponentY;

	friend std::ostream& operator<<(std::ostream& os, const NewsExplore& x);
	friend sf::Packet& operator<<(sf::Packet& pckt, const NewsExplore& x);
	friend sf::Packet& operator >> (sf::Packet& pckt, NewsExplore& x);
};


class NewsDeal{
public:
	NewsDeal();

	Mode gameMode;
	bool accept;
	int areaToGoBackAfterDealX, areaToGoBackAfterDealY;
	double dealerFactor;
	std::vector <int> cardsId;
	int income;		// == 0 jeśli na polu jest handlarz; > 0 jeśli jest skrzynka (i oznacza ilość złota w skrzynce)

	friend sf::Packet& operator<<(sf::Packet& pckt, const NewsDeal& x);
	friend sf::Packet& operator>>(sf::Packet& pckt, NewsDeal& x);
};

class NewsFight{
public:
	NewsFight();

	Mode gameMode;
	friend sf::Packet& operator<<(sf::Packet& pckt, const NewsFight& x);
	friend sf::Packet& operator>>(sf::Packet& pckt, NewsFight& x);
};
#endif
