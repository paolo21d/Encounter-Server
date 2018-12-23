#include "News.h"

using namespace std;

ostream& operator<<(ostream& os, const News& x) {
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
}

void News::reset(){
	gameMode = EXPLORE;
	firstFighter = nullptr;
	secondFighter = nullptr;

	dealerFactor = 0;	
	
	income = 0;
}
