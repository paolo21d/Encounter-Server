#include "News.h"

using namespace std;

////////////////////// KONSTRUKTORY

News::News()
{	
}

NewsExplore::NewsExplore()
{
}

NewsDeal::NewsDeal()
{
}

NewsFight::NewsFight()
{
}

NewsExplore::NewsExplore(Mode mode = EXPLORE, int posX = 0, int posY = 0){
	gameMode = mode;
	for(int i:{1,2,3,4}) {
		adjacent[i] = EMPTY;
	}
	//positionX = positionY = 0;
	positionX = posX;
	positionY = posY;
}

//////////////////////// OPERATORY

ostream& operator<<(ostream& os, const NewsExplore& x) {
	if(x.gameMode == FIGHT)
		os << "FIGHT " /*<<  x.firstFighter->getId() << " " << x.secondFighter->getId()*/ << endl;
	else if(x.gameMode == DEAL)
		os << "TRADE " <</* x.dealerFactor <<*/ endl;
	else
		os << "EXPLO" << endl;
	cout << "sądziedzi: ";
	for(int i: {0, 1, 2, 3}) cout << " " << x.adjacent[i];
	cout << endl << "pozycja: " << x.positionX << x.positionY << endl << endl;
	
	return os;
}

sf::Packet& operator<<(sf::Packet& pckt, const NewsExplore& x){
	pckt << x.gameMode;
	for(int i: {0, 1, 2, 3}) 
		pckt << x.adjacent[i];
	pckt << x.positionX << x.positionY;
	pckt << x.oponentLocationId << x.oponentX << x.oponentY;

	return pckt;
}

sf::Packet & operator >> (sf::Packet & pckt, NewsExplore & x) {			
	int temp;					 
	pckt >> temp;							 //nowa formuła obsługi game sama ustawia gameMode
	for (int i : {0, 1, 2, 3})
	{
		pckt >> temp;
		x.adjacent[i] = static_cast<areaType>(temp);
	}
	pckt >> x.positionX >> x.positionY;
	pckt >> x.oponentLocationId >> x.oponentX >> x.oponentY;
	return pckt;
}

sf::Packet & operator<<(sf::Packet & pckt, const NewsDeal & x) {
	// TODO: insert return statement here
	return pckt;
}

sf::Packet & operator >> (sf::Packet & pckt, NewsDeal & x) {
	// TODO: insert return statement here
	return pckt;
}

sf::Packet & operator<<(sf::Packet & pckt, const NewsFight & x) {
	// TODO: insert return statement here
	return pckt;
}

sf::Packet & operator >> (sf::Packet & pckt, NewsFight & x) {
	// TODO: insert return statement here
	return pckt;
}
