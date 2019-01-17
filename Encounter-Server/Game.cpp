#include "Game.h"
#include "Location.h"
#include "Hero.h"
#include "EncException.h"
#include "Object.h"
#include "Dealer.h"
#include "Chest.h"

using namespace std;
using namespace sf;

Game::Game()
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
	
	sleep(milliseconds(2000));
	//dodać mutexowe czekanie na kolegę

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

void Game::explore(int id)
{
	exploreMutex.lock();

	if(gameEndsWinnerIs != nullptr) {
		
	}

	if(myOpponent[1 - id] != nullptr) {
		newsE[id].gameMode = FIGHT;
		myOpponent[id] = player[1 - id];
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
			myOpponent[id] = (Character*) currentLocation[id]->occupation[newsE[id].positionX][newsE[id].positionY];
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

void Game::fight(int id)
{
	Packet pcktRcv, pcktSnd;
	int v, s, i;
	Character* enemy = (Character*) currentLocation[id]->occupation[playerX[id]][playerY[id]];

		s = newsF[id].strength[0] = player[id]->strength;
		v = newsF[id].vitality[0] = player[id]->vitality;
		i = newsF[id].intelligence[0] = player[id]->intelligence;

	// odebrany przed chwilą newsF jest pusty
	
	newsF[id].endFight = 0;
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
}
	
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

/*//////////////////		testowe:

int Game::giveMeDirection(TcpSocket& socket)	//odbiera info o ruchu gracza
{							//wysyła dane o grze
	int x;
	size_t received;
	char pseudoBuffer[100];


	Packet packet;
	packet << news;
	socket.send(packet);

	socket.receive(pseudoBuffer, sizeof(pseudoBuffer), received);

	x = pseudoBuffer[0] - '0';

	return x;
}

void Game::invalidGame(Hero& myHero, Location& currentLocation)
{	
	int portNumber = 2003;
	int direction;
	int newX, newY;

				sf::IpAddress ip = sf::IpAddress::getLocalAddress();	//nawiązuje komunikację
				sf::TcpSocket socket;

				sf::TcpListener listener;
				listener.listen(portNumber);
				listener.accept(socket);				//połączenie przez socket 

	while(1){try{					//w pętli czekam na zgłoszenia klienta
		news.gameMode = EXPLORE;
		direction = giveMeDirection(socket);		
		switch(direction){			//sprawdzam, czy nie wychodzi poza mapę
			case 0: newX = myHero.getX(); newY = myHero.getY()-1; break;
			case 1: newX = myHero.getX()+1; newY = myHero.getY(); break;
			case 2: newX = myHero.getX(); newY = myHero.getY()+1; break;
			case 3: newX = myHero.getX()-1; newY = myHero.getY(); break;
			default: throw LeavingMap();
		}
		if(newX >= areasCountX || newX < 0 || newY >= areasCountY || newY < 0)
			throw LeavingMap();
		if(currentLocation.ocupation[newX][newY] != nullptr) 		// wywołaj interaction dla zajmowanego pola
			currentLocation.ocupation[newX][newY] -> interaction(myHero, news);
		if(news.gameMode == EXPLORE){			//zaktualizuj info o pozycji gracza
			myHero.setX(newX);			//jeśli gameMode != EXPLORE, to próbował wejść na zajęte pole
			news.positionX = newX;
			myHero.setY(newY);
			news.positionY = newY;
		}
		if(currentLocation.ocupation[myHero.getX()][myHero.getY() - 1] == nullptr && myHero.getY() != 0) //sprawdza zajętość sąsiednich pól
			news.adjacent[0] = true;
		else	news.adjacent[0] = false;
		if(currentLocation.ocupation[myHero.getX() + 1][myHero.getY()] == nullptr && myHero.getX() != 3)
			news.adjacent[1] = true;
		else	news.adjacent[1] = false;
		if(currentLocation.ocupation[myHero.getX()][myHero.getY() + 1] == nullptr && myHero.getY() != 3)
			news.adjacent[2] = true;
		else	news.adjacent[2] = false;
		if(currentLocation.ocupation[myHero.getX() - 1][myHero.getY()] == nullptr && myHero.getX() != 0)
			news.adjacent[3] = true;
		else	news.adjacent[3] = false;
	   }//try
	   catch(LeavingMap){
	   	cout << "Ziomek, nawet nie próbuj uciekać..." << endl;
	   }
	}//while
}
*/