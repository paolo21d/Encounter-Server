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

////////////////////////////////////		KONSTRUKTORY		/////////////////////////////////
Game::Game(): sem1(0), sem2(0)
{
	uwagaNaPodrabianca = false;
	quitThreads[0] = quitThreads[1] = false;
	myOpponent[0] = myOpponent[1] = nullptr;
}

Game::~Game() {
}


void Game::init(int id)			// przesyła dane gry graczom przed rozpoczęciem
{
	try{
		communication.sendMap(map, id);
	}
	catch(...) {
		cout << "Jakiś parszywy podrabianiec wciska nam kit..." << endl;
		uwagaNaPodrabianca = true;
		return;
	}
}

///////////////////////////////////			GŁÓWNY SILNIK GRY		///////////////////////////////

void Game::game(int id, Hero* hero)
{	
	try{

	player[id] = hero;
	playerX[id] = hero -> getX();
	playerY[id] = hero -> getY();

	for(Location* i: map.locations)
		if(i->getId() == hero->getCurrLocationId())
			currentLocation[id] = i;
	

		// poczekaj na kolegę
	if(id){
		sem1.p();
		sem2.v();
	}
	else {
		sem1.v();
		sem2.p();
	}
	
	Packet initialPacket;	// pakiet inicjalizacyjny z podstawowymi informacjami
	initialPacket << player[id]->strength << player[id]->intelligence << player[id]->vitality << player[id]->gold;
	initialPacket << currentLocation[id]->getId() << player[id]->getX() << player[id]->getY();
	initialPacket << currentLocation[1 - id]->getId() << player[1 - id]->getX() << player[1 - id]->getY();
	communication.tabsoc[id].send(initialPacket);


	Packet pckt;			// pierwszy pakiet - wydzielony z pętli dla uproszczenia sekwencji wysyłania-odbierania
	news[id] = &newsE[id];
	newsE[id].gameMode = EXPLORE;
	newsE[id].endGame = KEEP_PLAYING;
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

	int mode;
	while(1)		// nieskończona pętla
	{				// odbierz -> wywołaj odpowiednią funkcję, która wypełni news -> zapakuj news ->  wyślij

		Packet pcktRcv, pcktSnd;	// muszą tworzyć się zawsze od nowa, już tak mają :)
		communication.status[id] = communication.tabsoc[id].receive(pcktRcv);

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
		communication.status[id] = communication.tabsoc[id].send(pcktSnd);

		if(quitThreads[id] == true){
			cout << "Kończę wątek " << id << endl;
			return;
		}
	}
	}//try
	catch(...) {
		cout << "Jakiś parszywy podrabianiec wciska nam kit..." << endl;
		uwagaNaPodrabianca = true;
		return;
	}
}

////////////////////////////////////		EXPLORE			////////////////////////////////

void Game::explore(int id)
{
	cout << "Przed mutexem " << endl;
	exploreMutex.lock();
	cout << "Po mutexie" << endl;

	if(gameEndsWinnerIs == player[id]) {		// sprawdzam warunek końca gry - wygrana
		newsE[id].endGame = LONG_LIVE_THE_WINNER;
		newsE[id].gameMode = EXPLORE;
		quitThreads[id] = true;
		exploreMutex.unlock();
		return;
	}
	if(gameEndsWinnerIs == player[1 - id]) {	// sprawdzam warunek końca gry - przegrana
		newsE[id].endGame = LOOSER;
		newsE[id].gameMode = EXPLORE;
		quitThreads[id] = true;
		exploreMutex.unlock();
		return;
	}
	if(communication.status[1 - id] == 3)			// sprawdzam warunek końca gry - rozłączenie przeciwnika
	{												// korzystam tu z danych współdzielonych, ale tylko czytam, więc bez mutexów
		newsE[id].endGame = COWARD_RUN_AWAY;
		quitThreads[id] = true;
		exploreMutex.unlock();
		return;	
	}
	if(communication.status[id] == 3)			// sprawdzam warunek końca gry - rozłączenie przeciwnika
	{												
		quitThreads[id] = true;
		exploreMutex.unlock();
		return;
	}

	if(myOpponent[1 - id] != nullptr) {			// czy przeciwnik się nie bije
		newsE[id].gameMode = FIGHT;
		exploreMutex.unlock();
		return;
	}
	else {										// zewnętrzne warunki w normie, biegaj sobie do woli

		if(currentLocation[id]->occupation[newsE[id].positionX][newsE[id].positionY] != nullptr && currentLocation[id]->occupation[newsE[id].positionX][newsE[id].positionY] != player[id]) {	// ustawiam gameMode w newsE w zależności od zawartości odwiedzanego pola
			newsE[id].gameMode = currentLocation[id]->occupation[newsE[id].positionX][newsE[id].positionY]->interaction();
		}
		else 
			newsE[id].gameMode = EXPLORE;		// jeśli pole jest szczerym polem
		
		// ustaliliśmy właśnie, że ...

		if(newsE[id].gameMode == DEAL)			// ... będziemy handlować
		{
			areaAfterDealX[id] = playerX[id];
			areaAfterDealY[id] = playerY[id];
			dealX[id] = newsE[id].positionX;
			dealY[id] = newsE[id].positionY;
		}
		else if(newsE[id].gameMode == FIGHT)	// ... będziemy się bić
		{
			fightAreaX[id] = newsE[id].positionX;
			fightAreaY[id] = newsE[id].positionY;
			myOpponent[id] = (Character*) currentLocation[id]->occupation[newsE[id].positionX][newsE[id].positionY];
			myOpponent[1-id] = player[id];
			
			// to są dwa indexy potrzebne klientowi do usunięcia pokonanego mob'a z mapy
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
		else if(newsE[id].gameMode == EXPLORE)	// ... będziemy biegać dalej
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



	newsE[id].oponentLocationId = locationId[1 - id]; // dane przeciwnika
	newsE[id].oponentX = playerX[1 - id];
	newsE[id].oponentY = playerY[1 - id]; 

	exploreMutex.unlock();
}

////////////////////////////////////		FIGHT		///////////////////////////////////

void Game::fight(int id)
{
	// pamiętamy, że odebrany przed chwilą newsF jest pusty

		// poczekaj na kolegę
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
	s[0] = myself->strength;		// moje wyjściowe statystyki 
	v[0] = myself->vitality;
	i[0] = myself->intelligence;
	s[1] = enemy->strength;			// przeciwnika wyjściowe statystyki
	v[1] = enemy->vitality;
	i[1] = enemy->intelligence;


		//ustaw wstępne news
	newsF[id].endFight = 0; 
	newsF[id].strength[0] = s[0];
	newsF[id].intelligence[0] = newsF[id].mana[0] = i[0];
	newsF[id].hp[0] = v[0];	// vitality będzie służyć do czegoś innego (to z usuwaniem mobków)

	newsF[id].strength[1] = enemy->strength;
	newsF[id].intelligence[1] = newsF[id].mana[1] = enemy->intelligence;
	newsF[id].hp[1] = enemy->vitality; // vitality będzie służyć do czegoś innego (to z usuwaniem mobków)

	newsF[id].cardAmount[0] = newsF[id].cardAmount[1] = 5;
	myself->gimmieSomeCardsBabe(newsF[id].cardsId);
	if(id)
		newsF[id].chosenCard = -1;
	else
		newsF[id].chosenCard = 0;

	newsF[id].vitality[0] = mobIndexInLocationArray;
	newsF[id].vitality[1] = mobIndexInObjectArray;


		// teraz wyślij wstępne info
	pcktSnd << newsF[id];
	communication.tabsoc[id].send(pcktSnd);

		// popraw vitality, już na normalne
	newsF[id].hp[0] = v[0];
	newsF[id].hp[1] = v[1];
	newsF[id].vitality[0] = v[0];
	newsF[id].vitality[1] = v[1];

		// poprośc gracza, który zaczyna (zawsze 1) o kartę
	if(id){
		Packet pcktSnd1;
		newsF[id].chosenCard = -1;
		pcktSnd1 << newsF[id];
		communication.tabsoc[id].send(pcktSnd1);
	}

		// poczekaj na kolegę
		if(id){
			sem1.p();
			sem2.v();
		}
		else {
			sem1.v();
			sem2.p();
		}

	while(1) {				// sekwencja:
							// odbierz kartę od 1 -> wyślij do obu stan grys -> odbierz kartę od 0 -> wyślij do obu graczy stan gry
		Card* mightyCardThatsGonnabeatYouAll;
		Packet pcktRcv, pcktSnd;
		Packet pcktRcv1, pcktSnd1;

	// odbierz kartę od 1
		if(id) {			
			communication.tabsoc[id].receive(pcktRcv);
			pcktRcv >> newsF[id];
	// rozpatrz jej efekt					
			mightyCardThatsGonnabeatYouAll = myself->kovalskiCardAnalysys(newsF[id].chosenCard);
			if(mightyCardThatsGonnabeatYouAll == nullptr || mightyCardThatsGonnabeatYouAll->getCostMana() > myself->intelligence)
					throw GotInvalidCard();
			myself->intelligence -= mightyCardThatsGonnabeatYouAll->getCostMana();
			enemy->vitality -= mightyCardThatsGonnabeatYouAll->getDamage();
			myself->myDeck.removeCard(newsF[id].chosenCard);
			newsF[1 - id].chosenCard = newsF[id].chosenCard;	// w szczególności ustaw przeciwnikowi, jaką kartę wybrałeś
		}

			// poczekaj na kolegę
			if(id){
				sem1.p();
				sem2.v();
			}
			else {
				sem1.v();
				sem2.p();
			}

		if(myself->vitality == 0 || enemy->vitality == 0) {
			break;	// jeśli ktoś zginie, to kończymy
		}
	// wyślij stan gry obu graczom
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

		pcktSnd << newsF[id];
		communication.tabsoc[id].send(pcktSnd);

	// odbierz kartę od 0
		if(!id) {
			communication.tabsoc[id].receive(pcktRcv1);
			pcktRcv1 >> newsF[id];
	// rozpatrz jej efekt
			mightyCardThatsGonnabeatYouAll = myself->kovalskiCardAnalysys(newsF[id].chosenCard);
			cout << mightyCardThatsGonnabeatYouAll->getId() << endl;
			if(mightyCardThatsGonnabeatYouAll == nullptr || mightyCardThatsGonnabeatYouAll->getCostMana() > myself->intelligence)
				throw GotInvalidCard();
			myself->intelligence -= mightyCardThatsGonnabeatYouAll->getCostMana();
			enemy->vitality -= mightyCardThatsGonnabeatYouAll->getDamage();
			myself->myDeck.removeCard(newsF[id].chosenCard);
			newsF[1 - id].chosenCard = newsF[id].chosenCard;
		}
			// poczekaj na kolegę
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

	// wyślij obu graczom stan gry
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

		pcktSnd1 << newsF[id];
		cout << " News " << newsF[id].endFight << " "<< id  << endl << newsF[id].chosenCard << " " << newsF[id].hp[0] << " " << newsF[id].mana[0] << " Przeciwnik: " << newsF[id].hp[1] << newsF[id].mana[1] << endl;
		communication.tabsoc[id].send(pcktSnd1);
		cout << "Po wysłaniu" << endl;
	}

	// poniższe robi wygrany

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
			if(myOpponent[id] == player[1 - id])
				gameEndsWinnerIs = player[id];

		}
		myOpponent[id] = nullptr;
		myOpponent[1 - id] = nullptr;
		newsF[1 - id].endFight = 2;
	}
		// poczekaj na kolegę
			if(id){
				sem1.p();
				sem2.v();
			}
			else {
				sem1.v();
				sem2.p();
			}
}

		
//////////////////////////////////		DEAL		///////////////////////////////////

void Game::deal(int id)
{	
	// pamiętamy, że odebrany przed chwilą newsD jest pusty

	cout << "Zaczynam handel z " << id << endl;
	bool dealerOrChest;		// 0 => dealer; 1 => chest
	Packet pcktSnd, pcktRcv;
	int temp = 0;

	Object* something = currentLocation[id]->occupation[dealX[id]][dealY[id]]; // może to być też skrzynka
	newsD[id].income = something->freeMoney();
	newsD[id].accept = true;
	dealerOrChest = newsD[id].income;	// 0 => dealer; cokolwiek => skrzynka
	if(dealerOrChest != 0)	// jeśli chest
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
	else		// jeśli dealer
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

// odbierz informację, co gracz kupił
	communication.tabsoc[id].receive(pcktRcv);
	pcktRcv >> newsD[id];

	if(dealerOrChest != 0)	//jeśli chest
	{
		player[id]->addGold(newsD[id].income);
		player[id]->addCards(newsD[id].cardsId);
// zaktualizuj dane handlarza
		delete something;
		currentLocation[id]->occupation[dealX[id]][dealY[id]] = nullptr;
	}
	else		//jeśli dealer
	{
// sprawdź, czy było go stać
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
			throw SomeoneIsStealing();
		}
// zaktualizuj dane handlarza
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
		cout << "Po handlu z " << id << endl;
	}
// ustaw w newsD gameMode == EXPLORE i każ ziomkowi się cofnąć
	newsD[id].gameMode = EXPLORE;
	newsD[id].areaToGoBackAfterDealX = areaAfterDealX[id];
	newsD[id].areaToGoBackAfterDealY = areaAfterDealY[id];

}

