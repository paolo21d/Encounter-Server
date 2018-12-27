#include "News.h"

using namespace std;

/*ostream& operator<<(ostream& os, const NewsExpolore& x) {
	if(x.gameMode == FIGHT)
		os << "FIGHT " <<  x.firstFighter->getId() << " " << x.secondFighter->getId() << endl;
	else if(x.gameMode == DEAL)
		os << "TRADE " << x.dealerFactor << endl;
	else
		os << "EXPLO" << endl;
	cout << "sądziedzi: ";
	for(int i: {0, 1, 2, 3}) cout << " " << x.adjacent[i];
	cout << endl << "zarobiłem: " << x.income << endl << "pozycja: " << x.positionX << x.positionY << endl << endl;
	
	return os;
}*/

sf::Packet& operator<<(sf::Packet& pckt, const NewsExplore& x){
	pckt << x.gameMode;
	for(int i: {0, 1, 2, 3}) pckt << x.adjacent[i];
	pckt << x.positionX << x.positionY;

	return pckt;
}


NewsExplore::NewsExplore(){
	gameMode = EXPLORE;
	/*firstFighter = nullptr;
	secondFighter = nullptr;
	dealerFactor = 0;	
	income = 0;*/
	for(int i:{1,2,3,4}){
		adjacent[i] = 0;
	}
	positionX = positionY = 0;
}

/*void NewsExplore::reset(){
	gameMode = EXPLORE;
	firstFighter = nullptr;
	secondFighter = nullptr;

	dealerFactor = 0;	
	
	income = 0;
}*/
