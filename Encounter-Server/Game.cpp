#include "Game.h"
#include "Location.h"
#include "Hero.h"
#include "EncException.h"
#include "Object.h"
#include "Dealer.h"
#include "Chest.h"
#include <iostream>

using namespace std;
using namespace sf;

Game::Game(): sem1(0), sem2(0)
{
	myOpponent[0] = myOpponent[1] = nullptr;
}

Game::~Game() {
}

void Game::init(int id)
{
	communication.sendMap(map, id);
}

void Game::game(int id, Hero* hero)
{
	player[id] = hero;
	playerX[id] = hero -> getX();
	playerY[id] = hero -> getY();

	for(Location* i: map.locations)
		if(i->getId() == hero->getCurrLocationId())
			currentLocation[id] = i;
	
	//sleep(milliseconds(2000));

	if(id){
		sem1.p();
		sem2.v();
	}
	else {
		sem1.v();
		sem2.p();
	}
	
	Packet initialPacket;
	initialPacket << player[id]->strength << player[id]->intelligence << player[id]->vitality << player[id]->gold;
	initialPacket << currentLocation[id]->getId() << player[id]->getX() << player[id]->getY();
	initialPacket << currentLocation[1 - id]->getId() << player[1 - id]->getX() << player[1 - id]->getY();
	communication.tabsoc[id].send(initialPacket);

	Packet pckt;		// pierwszy pakiet z exploreNews
	news[id] = &newsE[id];
	newsE[id].gameMode = EXPLORE;
	newsE[id].endGame = 0;
	newsE[id].adjacent[0] = IMPASSABLE;
	newsE[id].adjacent[1] = EMPTY;
	newsE[id].adjacent[2] = EMPTY;
	newsE[id].adjacent[3] = IMPASSABLE;
	newsE[id].oponentLocationId = locationId[1 - id];
	newsE[id].oponentX = player[1 - id] -> getX();
	newsE[id].oponentY = player[1 - id] -> getY();
	newsE[id].positionX = player[id] -> getX();
	newsE[id].positionY = player[id] -> getY();
	pckt << newsE[id];
	communication.tabsoc[id].send(pckt);
			cout << "Gracz " << id << " dostał pakiety inicjalizacyjne" << endl;

	int mode;
	while(1)		// główna nieskończona pętla
	{
		//////////////////// SPRAWDŹ, CZY KTOŚ SIĘ NIE ROZŁĄCZYŁ
		Packet pcktRcv, pcktSnd;
		communication.tabsoc[id].receive(pcktRcv);
		switch(news[id]->gameMode)
		{
			case 0:
				pcktRcv >> newsE[id];
				news[id] = &newsE[id];
				explore(id);	// w środku muszę ustawić gameMode w zależności od posX, posY
				pcktSnd << newsE[id];
				break;
			case 1:
				pcktRcv >> newsF[id];
				news[id] = &newsF[id];
				fight(id);	// w środku muszę ustawić gameMode w zależności od posX, posY
				pcktSnd << newsF[id];
				break;
			case 2:
				pcktRcv >> newsD[id];
				news[id] = &newsD[id];
				deal(id);		// w środku muszę ustawić gameMode w zależności od posX, posY
				pcktSnd << newsD[id];
				break;
		}
		communication.tabsoc[id].send(pcktSnd);
		// sprawdzić jakoś, czy gra się nie kończy
	}
}

////////////////////////////////////		EXPLORE			////////////////////////////////

void Game::explore(int id)
{
	exploreMutex.lock();
	cout << "Start explore" << id << endl; 

	if(gameEndsWinnerIs != nullptr) {
		
	}

	if(myOpponent[1 - id] != nullptr) {
		newsE[id].gameMode = FIGHT;
		exploreMutex.unlock();
		return;
	}
	else {
	//if(id == 0) cout << "Pozycja: " <<newsE[id].positionX << " " << newsE[id].positionY << endl;
		if(currentLocation[id]->occupation[newsE[id].positionX][newsE[id].positionY] != nullptr && currentLocation[id]->occupation[newsE[id].positionX][newsE[id].positionY] != player[id]) {	// ustawiam gameMode w newsE
			newsE[id].gameMode = currentLocation[id]->occupation[newsE[id].positionX][newsE[id].positionY]->interaction();
		}
		else 
			newsE[id].gameMode = EXPLORE;
		

		if(newsE[id].gameMode == DEAL)
		{
			areaAfterDealX[id] = playerX[id];
			areaAfterDealY[id] = playerY[id];
			dealX[id] = newsE[id].positionX;
			dealY[id] = newsE[id].positionY;
		}
		else if(newsE[id].gameMode == FIGHT)
		{
			fightAreaX[id] = newsE[id].positionX;
			fightAreaY[id] = newsE[id].positionY;
			myOpponent[id] = (Character*) currentLocation[id]->occupation[newsE[id].positionX][newsE[id].positionY];
			myOpponent[1-id] = player[id];
			mobIndexInLocationArray = currentLocation[id]->getId();
			int temp=0;
			for (int k = 0; k < areasCountX; ++k) {
				for (int j = 0; j < areasCountY; ++j) {
					if (currentLocation[id]->occupation[k][j] != nullptr && currentLocation[id]->occupation[k][j] != player[id] && currentLocation[id]->occupation[k][j] != player[1 - id]) {
						if(k == newsE[id].positionX && j == newsE[id].positionY){
							mobIndexInObjectArray = temp;
							break;
						}
						++temp;
					}
				}
			}
		}
		else if(newsE[id].gameMode == EXPLORE)
		{
			currentLocation[id]->occupation[playerX[id]][playerY[id]] = nullptr;
			currentLocation[id]->occupation[newsE[id].positionX][newsE[id].positionY] = player[id];
			playerX[id] = newsE[id].positionX;
			playerY[id] = newsE[id].positionY;
		}
	}

	// poniżej wypełniam adjecent zakładając, że liczymy pola od lewego górnego
	if(playerY[id] == 0) //sprawdza zajętość sąsiednich pól
			newsE[id].adjacent[0] = IMPASSABLE;
		else if(currentLocation[id]->occupation[playerX[id]][playerY[id] - 1] == nullptr)
			newsE[id].adjacent[0] = EMPTY;
		else
			newsE[id].adjacent[0] = currentLocation[id]->occupation[playerX[id]][playerY[id] - 1]->checkAdjacent();
	
	if(playerX[id] == areasX - 1)
			newsE[id].adjacent[1] = IMPASSABLE;
		else if(currentLocation[id]->occupation[playerX[id] + 1][playerY[id]] == nullptr) //sprawdza zajętość sąsiednich pól
			newsE[id].adjacent[1] = EMPTY;
		else
			newsE[id].adjacent[1] = currentLocation[id]->occupation[playerX[id] + 1][playerY[id]]->checkAdjacent();
	
	if(playerY[id] == areasY - 1)
			newsE[id].adjacent[2] = IMPASSABLE;
		else if(currentLocation[id]->occupation[playerX[id]][playerY[id] + 1] == nullptr) //sprawdza zajętość sąsiednich pól
			newsE[id].adjacent[2] = EMPTY;
		else
			newsE[id].adjacent[2] = currentLocation[id]->occupation[playerX[id]][playerY[id] + 1]->checkAdjacent();

	if(playerX[id] == 0)
			newsE[id].adjacent[3] = IMPASSABLE;
		else if(currentLocation[id]->occupation[playerX[id] - 1][playerY[id]] == nullptr) //sprawdza zajętość sąsiednich pól
			newsE[id].adjacent[3] = EMPTY;
		else
			newsE[id].adjacent[3] = currentLocation[id]->occupation[playerX[id] - 1][playerY[id]]->checkAdjacent();


	//if(id == 0) cout << "Pozycja: " << playerX[id] << playerY[id] << "	Sasiedzi: " << newsE[id].adjacent[0] << newsE[id].adjacent[1] << newsE[id].adjacent[2] << newsE[id].adjacent[3] << endl;

	newsE[id].oponentLocationId = locationId[1 - id]; // dane przeciwnika
	newsE[id].oponentX = playerX[1 - id];
	newsE[id].oponentY = playerY[1 - id]; 

	exploreMutex.unlock();
}

////////////////////////////////////		FIGHT		///////////////////////////////////

void Game::fight(int id)
{
	cout << "1 " << id << endl;
		//	*	poczekaj na kolegę
		if(id){
			sem1.p();
			sem2.v();
		}
		else {
			sem1.v();
			sem2.p();
		}

	Packet pcktRcv, pcktSnd;
	Character* enemy = myOpponent[id];
	Character* myself = myOpponent[1 - id];
	bool IamMyself = myOpponent[1-id] == player[id];
	
	int v[2], s[2], i[2];
	s[0] = myself->strength;		// po walce ustawię na nie moje statystyki
	v[0] = myself->vitality;
	i[0] = myself->intelligence;
	s[1] = enemy->strength;		// po walce ustawię na nie moje statystyki
	v[1] = enemy->vitality;
	i[1] = enemy->intelligence;
		// odebrany przed chwilą newsF jest pusty
		//ustaw wstępne news
	newsF[id].endFight = 0; 
	newsF[id].strength[0] = s[0];
	newsF[id].intelligence[0] = newsF[id].mana[0] = i[0];
	newsF[id].hp[0] = v[0];	// vitality będzie służyć do czegoś innego

	newsF[id].strength[1] = enemy->strength;
	newsF[id].intelligence[1] = newsF[id].mana[1] = enemy->intelligence;
	newsF[id].hp[1] = enemy->vitality; // vitality będzie służyć do czegoś innego

	newsF[id].cardAmount[0] = newsF[id].cardAmount[1] = 5;
	myself->gimmieSomeCardsBabe(newsF[id].cardsId);
	if(id)
		newsF[id].chosenCard = -1;
	else
		newsF[id].chosenCard = 0;

	newsF[id].vitality[0] = mobIndexInLocationArray;
	newsF[id].vitality[1] = mobIndexInObjectArray;

		// wyślij wstępne info
	pcktSnd << newsF[id];
	communication.tabsoc[id].send(pcktSnd);

		// popraw vitality, już na normalne
	newsF[id].hp[0] = v[0];
	newsF[id].hp[1] = v[1];
	newsF[id].vitality[0] = v[0];
	newsF[id].vitality[1] = v[1];

		// wyśli do gracza 1
	if(id){
		newsF[id].chosenCard = -1;
		pcktSnd << newsF[id];
		communication.tabsoc[id].send(pcktSnd);
	}

		//	*	poczekaj na kolegę
		if(id){
			sem1.p();
			sem2.v();
		}
		else {
			sem1.v();
			sem2.p();
		}

	while(1) {
		Card* mightyCardThatsGonnabeatYouAll;
		
		if(id) {
			communication.tabsoc[id].receive(pcktRcv);
			pcktRcv >> newsF[id];
			
			mightyCardThatsGonnabeatYouAll = myself->kovalskiCardAnalysys(newsF[id].chosenCard);
				if(mightyCardThatsGonnabeatYouAll == nullptr || mightyCardThatsGonnabeatYouAll->getCostMana() > myself->intelligence)
					{}	//jakiś błąd
			myself->intelligence -= mightyCardThatsGonnabeatYouAll->getCostMana();
			enemy->vitality -= mightyCardThatsGonnabeatYouAll->getDamage();
			myself->myDeck.removeCard(newsF[id].chosenCard);
				// ustaw przeciwnikowi, jaką kartę wybrałeś
			newsF[1 - id].chosenCard = newsF[id].chosenCard;

			cout << id << " wybrał kartę" << newsF[id].chosenCard << endl << ". Nowe hp " << id << ": " << myself->vitality << ". Nowe hp " << 1 - id << ": " << enemy->vitality << endl;

			newsF[id].chosenCard = 0;
		}

			//	*	poczekaj na kolegę
			if(id){
				sem1.p();
				sem2.v();
			}
			else {
				sem1.v();
				sem2.p();
			}

		if(myself->vitality == 0 || enemy->vitality == 0) {
			break;
		}
		newsF[id].endFight = 0; 
		newsF[id].strength[0] = s[0];
		newsF[id].intelligence[0] = i[0];
		newsF[id].vitality[0] = v[0];
		newsF[id].strength[1] = s[1];
		newsF[id].intelligence[1] = i[1];
		newsF[id].vitality[1] = v[1];
		newsF[id].hp[0] = myself->vitality;
		newsF[id].mana[0] = myself->intelligence;
		newsF[id].hp[1] = enemy->vitality;
		newsF[id].mana[1] = enemy->intelligence;
		*find(newsF[id].cardsId.begin(), newsF[id].cardsId.end(), newsF[id].chosenCard) = myself->randomCard();
		newsF[id].cardAmount[0] = newsF[id].cardsId.size();
		newsF[id].cardAmount[1] = enemy->myDeck.deck.size();

		cout << id << " News: " << newsF[id].chosenCard << newsF[id].hp[0] << newsF[id].mana[0] << " " << newsF[id].hp[1] << newsF[id].mana[1] << endl;
		pcktSnd << newsF[id];
		communication.tabsoc[id].send(pcktSnd);

		if(!id) {
			communication.tabsoc[id].receive(pcktRcv);
			pcktRcv >> newsF[id];

			mightyCardThatsGonnabeatYouAll = myself->kovalskiCardAnalysys(newsF[id].chosenCard);
				if(mightyCardThatsGonnabeatYouAll == nullptr || mightyCardThatsGonnabeatYouAll->getCostMana() > myself->intelligence)
					{}	//jakiś błąd
			myself->intelligence -= mightyCardThatsGonnabeatYouAll->getCostMana();
			enemy->vitality -= mightyCardThatsGonnabeatYouAll->getDamage();
			myself->myDeck.removeCard(newsF[id].chosenCard);
			newsF[1 - id].chosenCard = newsF[id].chosenCard;

			cout << id << " wybrał kartę" << newsF[id].chosenCard << endl << ". Nowe hp " << id << ": " << myself->vitality << ". Nowe hp " << 1 - id << ": " << enemy->vitality << endl;
			
			newsF[id].chosenCard = 0;
		}
			//	*	poczekaj na kolegę
			if(id){
				sem1.p();
				sem2.v();
			}
			else {
				sem1.v();
				sem2.p();
			}
		if(myself->vitality <= 0 || enemy->vitality <= 0) {
			break;
		}
		newsF[id].endFight = 0; 
		newsF[id].strength[0] = s[0];
		newsF[id].intelligence[0] = i[0];
		newsF[id].vitality[0] = v[0];
		newsF[id].strength[1] = s[1];
		newsF[id].intelligence[1] = i[1];
		newsF[id].vitality[1] = v[1];
		newsF[id].hp[0] = myself->vitality;
		newsF[id].mana[0] = myself->intelligence;
		newsF[id].hp[1] = enemy->vitality;
		newsF[id].mana[1] = enemy->intelligence;
		*find(newsF[id].cardsId.begin(), newsF[id].cardsId.end(), newsF[id].chosenCard) = myself->randomCard();
		newsF[id].cardAmount[0] = newsF[id].cardsId.size();
		newsF[id].cardAmount[1] = enemy->myDeck.deck.size();
		newsF[id].chosenCard = 0;

		pcktSnd << newsF[id];
		communication.tabsoc[id].send(pcktSnd);
	}

	// to robi wygrany

	newsF[id].gameMode = EXPLORE;
	if(enemy->vitality <= 0)
	{
		myself->intelligence = i[0];
		myself->vitality = v[0];
		myself->strength = s[0];
		newsF[id].endFight = 1;

		if(IamMyself){
			currentLocation[id]->occupation[fightAreaX[id]][fightAreaY[id]] = myself;
			currentLocation[id]->occupation[playerX[id]][playerY[id]] = nullptr;
			playerX[id] = fightAreaX[id];
			playerY[id] = fightAreaY[id];
		}
		myOpponent[id] = nullptr;
		myOpponent[1 - id] = nullptr;
		newsF[1 - id].endFight = 2;
		//gameEndsWinnerIs = ...
	}
		//	*	poczekaj na kolegę
			if(id){
				sem1.p();
				sem2.v();
			}
			else {
				sem1.v();
				sem2.p();
			}
	cout << "Kończymy walczenie " << id << endl;
}

		

	
/*			stary fight

	while( enemy->vitality != 0 && player[id]->vitality != 0 )
	{
	//		wyślij dane moje 
		newsF[id].strength[0] = player[id]->strength;		
		newsF[id].vitality[0] = player[id]->vitality;			
		newsF[id].intelligence[0] = player[id]->intelligence;
		for(Card* i: player[id]->myDeck.deck)
			newsF[id].cardsId[0].push_back(i->getId());
	//		i przeciwnika
		newsF[id].strength[1] = enemy->strength;	
		newsF[id].vitality[1] = enemy->vitality;	
		newsF[id].intelligence[1] = enemy->intelligence;
		for(Card* i: enemy->myDeck.deck)
			newsF[id].cardsId[1].push_back(i->getId());

		pcktSnd << newsF[id];
		communication.tabsoc[id].send(pcktSnd);
	//		odbierz wybraną kartę
		communication.tabsoc[id].receive(pcktRcv);
		pcktRcv >> newsF[id];

///////////////// WYSYŁAM ZAWSZE 5 KART - 4 stare i jedną nową
	//		usuń użytą kartę, zaktualizuj i, v, s
		for(Card* j: player[id]->myDeck.deck)
			if(j->getId() == newsF[id].chosenCard)
			{
				player[id]->intelligence -= j->getCostMana();
				enemy->intelligence -= j->getDamage();
			}
		player[id]->myDeck.removeCard(newsF[id].chosenCard);


	}
	// ustaw w newsF gameMode == EXPLORE i info kto wygrał (nie wysyłaj)
	// usuń przegranego z gry
	newsF[id].gameMode = EXPLORE;

	////////// NIE WYSYŁAM GAMEMODE, TYLKO INFO KTO WYGRAŁ
	
	if(enemy->vitality == 0)
	{
		player[id]->intelligence = i;
		player[id]->vitality = v;
		player[id]->strength = s;
		newsF[id].endFight = 1;
		delete enemy;
		currentLocation[id]->occupation[playerX[id]][playerY[id]] = player[id];
		myOpponent[id] = nullptr;
	}
	else
	{
		newsF[id].endFight = 2;
		gameEndsWinnerIs = player[1 - id];
	}
*/

//////////////////////////////////		DEAL		///////////////////////////////////

void Game::deal(int id)
{
	cout << id << "handelkujemy" << endl;
	
	bool dealerOrChest;		// 0 => dealer; 1 => chest
	Packet pcktSnd, pcktRcv;
	int temp = 0;

	// odebrany przed chwilą newsD jest pusty
	Object* something = currentLocation[id]->occupation[dealX[id]][dealY[id]]; // może to być też skrzynka
	newsD[id].income = something->freeMoney();
	newsD[id].accept = true;
	dealerOrChest = newsD[id].income;	// 0 => dealer; >0 => skrzynka
	if(dealerOrChest != 0)	//chest
	{
		Chest* chest = (Chest*) something;
		newsD[id].dealerFactor = INFINITY;
		newsD[id].cardsId.clear();
		for(Card* x: chest->myDeck.deck)
		{
			newsD[id].cardsId.push_back(x->getId());
			++temp;
		}
		newsD[id].cardAmount = temp;
	}
	else		//dealer
	{
		Dealer* dealer = (Dealer*) something;
		dealer->printCards();
		newsD[id].dealerFactor = dealer->saleFactor;
		newsD[id].cardsId.clear();
		for(Card* x: dealer->soldCards.deck)
		{
			newsD[id].cardsId.push_back(x->getId());
			++temp;
		}
		newsD[id].cardAmount = temp;
	}
	
	// wyślij dane handlarza
	pcktSnd << newsD[id];
	communication.tabsoc[id].send(pcktSnd);

	// odbierz info, co gracz kupił
	communication.tabsoc[id].receive(pcktRcv);
	pcktRcv >> newsD[id];

	if(dealerOrChest != 0)	//chest
	{
		player[id]->addGold(newsD[id].income);
		player[id]->addCards(newsD[id].cardsId);
		// zaktualizuj dane handlarza
		delete something;
		currentLocation[id]->occupation[dealX[id]][dealY[id]] = nullptr;
	}
	else		//dealer
	{
		int sumPaid = 0;
		for(int i: newsD[id].cardsId)
		{
			for(Card* j: Map::allCards)
			{
				if(i == j->getId())
					sumPaid += j->getPrice();
			}
			sumPaid += (newsD[id].boostStr + newsD[id].boostInt + newsD[id].boostVit) * STATPRICE;
			sumPaid *= newsD[id].dealerFactor;
		}
		if(sumPaid > player[id]->getGold()) {
			newsD[id].accept = false;
		}
		else
		{
			Dealer* dealer = (Dealer*) something;
			dealer->removeCards(newsD[id].cardsId);
			newsD[id].accept = true;
			player[id]->removeGold(sumPaid);
			player[id]->addCards(newsD[id].cardsId);
			player[id]->changeIntelligence(newsD[id].boostInt);
			player[id]->changeStrength(newsD[id].boostStr);
			player[id]->changeVitality(newsD[id].boostVit);
			dealer->printCards();
		}
		
	}
	// ustaw w newsD gameMode == EXPLORE i każ ziomkowi się cofnąć
	newsD[id].gameMode = EXPLORE;
	newsD[id].areaToGoBackAfterDealX = areaAfterDealX[id];
	newsD[id].areaToGoBackAfterDealY = areaAfterDealY[id];

	cout << id << "koniec handelkowania" << endl;

}

