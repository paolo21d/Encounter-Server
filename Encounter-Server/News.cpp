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
	pckt << x.endGame;
	for(int i: {0, 1, 2, 3}) 
		pckt << x.adjacent[i];
	pckt << x.positionX << x.positionY;
	pckt << x.oponentLocationId << x.oponentX << x.oponentY;

	return pckt;
}

sf::Packet & operator >> (sf::Packet & pckt, NewsExplore & x) {			
	int temp;					 
	pckt >> temp;							 //nowa formuła obsługi game sama ustawia gameMode
	pckt >> x.endGame;
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
	pckt << x.accept << x.areaToGoBackAfterDealX << x.areaToGoBackAfterDealY << x.cardAmount;
	for(int i=0; i < x.cardAmount; ++i)
		pckt << x.cardsId[i];
	pckt << x.income;
	return pckt;
}

sf::Packet & operator >> (sf::Packet & pckt, NewsDeal & x) {
	int temp, cardId;
	pckt >> temp;
	//x.gameMode = static_cast<Mode>(temp);
	pckt >> x.cardAmount;
	x.cardsId.clear();
	for(int i=0; i < x.cardAmount; ++i){
		pckt >> cardId;
		x.cardsId.push_back(cardId);
	}
	pckt >> x.areaToGoBackAfterDealX >> x.areaToGoBackAfterDealY >> x.accept << x.income;
	pckt >> x.boostStr >> x.boostInt >> x.boostVit;
	return pckt;
}

sf::Packet & operator<<(sf::Packet & pckt, const NewsFight & x) {
	pckt << x.endFight;
	pckt << x.strength[0] << x.strength[1];
	pckt << x.intelligence[0] << x.intelligence[1];
	pckt << x.vitality[0] << x.vitality[1];
	pckt << x.hp[0] << x.hp[1] << x.mana[0] << x.mana[1];
	pckt << static_cast<int>(x.cardsId[0].size()) << static_cast<int>(x.cardsId[1].size());
	for(int i: {0, 1})
		for(int j = 0; j < x.cardAmount[i]; ++j)
			pckt << x.cardsId[i][j];
	pckt << x.chosenCard;
	
	return pckt;
}

sf::Packet & operator >> (sf::Packet & pckt, NewsFight & x) {
	pckt >> x.endFight;
	pckt >> x.strength[0] >> x.strength[1];
	pckt >> x.intelligence[0] >> x.intelligence[1];
	pckt >> x.vitality[0] >> x.vitality[1];
	pckt >> x.hp[0] >> x.hp[1];
	pckt >> x.mana[0] >> x.mana[1];
	pckt >> x.cardAmount[0] >> x.cardAmount[1];
	for(int i: {0, 1})
		for(int j = 0; j < x.cardAmount[i]; ++j)
			pckt >> x.cardsId[i][j];
	pckt >> x.chosenCard;
	
	return pckt;
}
