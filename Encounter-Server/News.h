#ifndef NEWS_H
#define NEWS_H
#include <iostream>
#include <fstream>
#include "Character.h"
#include "Deck.h"
#include "SFML/Network.hpp"


enum Mode{EXPLORE, FIGHT, DEAL};

struct NewsExplore {

	Mode gameMode;
	/*const Character* firstFighter; //przerzucić do klasy game
	const Character* secondFighter;*/
	
	//int income;
	int adjacent[4];			//0-góra, 1-prawa, 2-dół, 3-lewa //0-mozna wejsc, 1-pole nieinteraktywne, 2-pole interaktywne
	int positionX, positionY;
	///
	void reset();
	NewsExplore();

	//friend std::ostream& operator<<(std::ostream& os, const NewsExpolore& x);
	friend sf::Packet& operator<<(sf::Packet& pckt, const NewsExplore& x);
	friend sf::Packet& operator>>(sf::Packet& pckt, const NewsExplore& x);
};

struct NewsDeal {
	Mode gameMode;
	double dealerFactor;
	//Deck cardsForSale; //mozliwe ze zamienic na vector intow czyli id kart
	std::vector <int> cardsId;

	friend sf::Packet& operator<<(sf::Packet& pckt, const NewsDeal& x);
	friend sf::Packet& operator>>(sf::Packet& pckt, const NewsDeal& x);
};

struct NewsFight {
	Mode gameMode;

	friend sf::Packet& operator<<(sf::Packet& pckt, const NewsFight& x);
	friend sf::Packet& operator>>(sf::Packet& pckt, const NewsFight& x);
};
#endif
