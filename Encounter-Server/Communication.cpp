#include "Communication.h"
#include <SFML/Network.hpp>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;
using namespace sf;


Communication::Communication() {
}


Communication::~Communication() {
}

void Communication::srdata(int num, int socnum) {
	cout << "Melduje watek: " << num << endl;
	//sf::TcpSocket socket = vecsoc.end();
	//socket.create(vecsoc.end());
	int i = 0;
	string msgSerwer, msgClient;
	//char buffer[200];
	//size_t received;
	while (1) {
		Packet recPacket, sendPacket;
		msgSerwer = "Dane z serwera " + to_string(num) + ": " + to_string(i);
		i++;
		sendPacket << msgSerwer;
		tabsoc[socnum].send(sendPacket);
		//tabsoc[socnum].send(msgSerwer.c_str(), msgSerwer.length() + 1);
		//Sleep(1);

		//tabsoc[socnum].receive(buffer, sizeof(buffer), received);
		tabsoc[socnum].receive(recPacket);
		recPacket >> msgClient;
		cout << msgClient << "Klient: " << num << endl;
	}
}

void Communication::sendMap(const Map& map, const int num) {

	//trzeba dodać wysyłanie grafik

	Packet packet;
	packet << mapSizeX << mapSizeY;
	packet << static_cast<int>(map.locations.size());
	packet << areaSizeX << areaSizeY;
	for (int i = 0; i < map.locations.size(); ++i) { //przeslanie lokacji
		packet << map.locations[i].getId() << map.locations[i].getSrc();
		vector<Object*> tempObj;
		for (int k = 0; k < areasCountX; ++k) {
			for (int j = 0; j < areasCountY; ++j) {
				if (map.locations[i].occupation[k][j] != nullptr)
					tempObj.push_back(map.locations[i].occupation[k][j]);
			}
		}
		packet << static_cast<int>(tempObj.size());
		for (int i = 0; i < tempObj.size(); ++i) { //przeslanie objektow w lokacji
			packet << tempObj[i]->getId() << tempObj[i]->getX() << tempObj[i]->getY() << tempObj[i]->getFileName();
		}
	}

	//przeslanie kart
	packet << static_cast<int>(map.allCards.size());
	for (int i = 0; i < map.allCards.size(); ++i) {
		packet << map.allCards[i]->getId() << map.allCards[i]->getSrc() << map.allCards[i]->getName() << map.allCards[i]->getDescription() << map.allCards[i]->getCostMana();
	}
	tabsoc[num].send(packet);
}
