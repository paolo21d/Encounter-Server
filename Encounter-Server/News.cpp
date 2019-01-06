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
// trzeb je trochę pozmieniać żeby nie czytać zawsze wszystkiego
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
	pckt << x.gameMode;
	pckt << x.accept << x.areaToGoBackAfterDealX << x.areaToGoBackAfterDealY << x.dealerFactor << x.cardAmount;
	for(int i; i < x.cardAmount; ++i)
		pckt << x.cardsId[i];
	pckt << x.income;
	
	return pckt;
}

sf::Packet & operator >> (sf::Packet & pckt, NewsDeal & x) {
	int temp;
	pckt >> temp;
	x.gameMode = static_cast<Mode>(temp);
	pckt >> x.accept >> x.areaToGoBackAfterDealX >> x.areaToGoBackAfterDealY >> x.dealerFactor >> x.cardAmount;
	for(int i; i < x.cardAmount; ++i)
		pckt >> x.cardsId[i];
	pckt >> income;
	
	return pckt;
}

sf::Packet & operator<<(sf::Packet & pckt, const NewsFight & x) {
	pckt << x.youWon;
	pckt << x.strength[0] << x.strength[1];
	pckt << x.intelligence[0] << x.intelligence[1];
	pckt << x.vitality[0] << x.vitality[1];
	pckt << static_cast<int>(x.cardsId[0].size()) << static_cast<int>(x.cardsId[1].size());
	for(int i: {0, 1})
		for(int j; j < x.cardAmount[i]; ++j)
			pckt << x.cardsId[i][j];
	pckt << chosenCard;
	
	return pckt;
}

sf::Packet & operator >> (sf::Packet & pckt, NewsFight & x) {
	pckt >> x.youWon;
	pckt >> x.strength[0] << x.strength[1];
	pckt >> x.intelligence[0] << x.intelligence[1];
	pckt >> x.vitality[0] << x.vitality[1];
	pckt >> x.cardAmount[0] << x.cardAmount[1];
	for(int i: {0, 1})
		for(int j; j < x.cardAmount[i]; ++j)
			pckt >> x.cardsId[i][j];
	pckt >> chosenCard;
	
	return pckt;
}
