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
}

Game::~Game() {
}

void Game::init(int id)
{
	communication.sendMap(map, id);
}

void Game::game(int id) 
{
	
	// pierwsza paczka do klienta
	
	int mode;
	while(1)
	{
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
	//sprawdzić, czy przeciwnik się przypadkiem nie bije

	if(currentLocation[id]->occupation[newsE[id].positionX][newsE[id].positionY] != nullptr)	// ustawiam gameMode w newsE
		newsE[id].gameMode = currentLocation[id]->occupation[newsE[id].positionX][newsE[id].positionY]->interaction();
	else 
		newsE[id].gameMode = EXPLORE;
	
	if(newsE[id].gameMode == DEAL)
	{
		newsD[id].areaToGoBackAfterDealX = playerX[id];
		newsD[id].areaToGoBackAfterDealY = playerY[id];
	}
	else if(newsE[id].gameMode == EXPLORE)
	{
		currentLocation[id]->occupation[playerX[id]][playerY[id]] = player[id];
	}

	playerX[id] = newsE[id].positionX;
	playerY[id] = newsE[id].positionY;

	// poniżej wypełniam adjecent zakładając, że liczymy pola od lewego górnego
	if(currentLocation[id]->occupation[playerX[id]][playerY[id] - 1] == nullptr) //sprawdza zajętość sąsiednich pól
			newsE[id].adjacent[0] = EMPTY;
		else if(playerY[id] == 0)
			newsE[id].adjacent[0] = IMPASSABLE;
		else
			newsE[id].adjacent[0] = currentLocation[id]->occupation[playerX[id]][playerY[id] - 1]->checkAdjacent();
	
	if(currentLocation[id]->occupation[playerX[id] + 1][playerY[id]] == nullptr) //sprawdza zajętość sąsiednich pól
			newsE[id].adjacent[1] = EMPTY;
		else if(playerX[id] == areasX)
			newsE[id].adjacent[1] = IMPASSABLE;
		else
			newsE[id].adjacent[1] = currentLocation[id]->occupation[playerX[id] + 1][playerY[id]]->checkAdjacent();
	
	if(currentLocation[id]->occupation[playerX[id]][playerY[id] + 1] == nullptr) //sprawdza zajętość sąsiednich pól
			newsE[id].adjacent[2] = EMPTY;
		else if(playerY[id] == areasY)
			newsE[id].adjacent[2] = IMPASSABLE;
		else
			newsE[id].adjacent[2] = currentLocation[id]->occupation[playerX[id]][playerY[id] + 1]->checkAdjacent();

	if(currentLocation[id]->occupation[playerX[id] - 1][playerY[id]] == nullptr) //sprawdza zajętość sąsiednich pól
			newsE[id].adjacent[0] = EMPTY;
		else if(playerX[id] == 0)
			newsE[id].adjacent[0] = IMPASSABLE;
		else
			newsE[id].adjacent[0] = currentLocation[id]->occupation[playerX[id] - 1][playerY[id]]->checkAdjacent();


	newsE[id].oponentLocationId = locationId[1 - id]; // dane przeciwnika
	newsE[id].oponentX = playerX[1 - id];
	newsE[id].oponentY = playerY[1 - id]; 

}

void Game::fight(int id)
{
	// odebrany przed chwilą newsF jest pusty
	
	Character* enemy = (Character*) currentLocation[id]->occupation[playerX[id]][playerY[id]];
	//while( obaj żyją )
	//		wyślij dane przeciwnika
	//		odbierz wybraną kartę
	//		zaktualizuj dane graczy
	//
	// ustaw w newsF gameMode == EXPLORE i info kto wygrał (nie wysyłaj)
	// usuń przegranego z gry
	
	// wygrany zajmuje dane pole
	currentLocation[id]->occupation[playerX[id]][playerY[id]] = player[id];
}
	
void Game::deal(int id)
{
	int areaToGoBackAfterDealX = newsD[id].areaToGoBackAfterDealX;
	int areaToGoBackAfterDealY = newsD[id].areaToGoBackAfterDealY;
	bool dealerOrChest;		// 0 => dealer; 1 => chest
	Packet pcktSnd, pcktRcv;
	
	// odebrany przed chwilą newsD jest pusty
	Object* something = currentLocation[id]->occupation[playerX[id]][playerY[id]]; // może to być też skrzynka
	newsD[id].income = something->freeMoney();
	newsD[id].accept = true;
	dealerOrChest = newsD[id].income;
	if(dealerOrChest)
	{
		Chest* chest = (Chest*) something;
		newsD[id].dealerFactor = INFINITY;
		for(Card* x: chest->myDeck.deck)
			newsD[id].cardsId.push_back(x->getId());
	}
	else
	{
		Dealer* dealer = (Dealer*) something;
		newsD[id].dealerFactor = dealer->saleFactor;
		for(Card* x: dealer->soldCards.deck)
			newsD[id].cardsId.push_back(x->getId());
	}
	
	// wyślij dane handlarza
	pcktSnd << newsD[id];
	communication.tabsoc[id].send(pcktSnd);

	// odbierz info, co gracz kupił
	communication.tabsoc[id].receive(pcktRcv);
	pcktRcv >> newsD[id];

	if(dealerOrChest)
	{
		player[id]->addGold(newsD[id].income);
		player[id]->addCards(newsD[id].cardsId);
		// zaktualizuj dane handlarza
		delete something;
		currentLocation[id]->occupation[playerX[id]][playerY[id]] = nullptr;
	}
	else
	{
		int sumPaid = 0;
		for(int i: newsD[id].cardsId)
		{
			for(Card* j: map.allCards)
			{
				if(i == j->getId())
					sumPaid += j->getPrice();
			}
		}
		if(sumPaid > player[id]->getGold())
			newsD[id].accept = false;
		else
		{
			newsD[id].accept = true;
			player[id]->removeGold(sumPaid);
			player[id]->addCards(newsD[id].cardsId);
		}
		Dealer* dealer = (Dealer*) something;
		dealer->removeCards(newsD[id].cardsId);
	}
	// ustaw w newsD gameMode == EXPLORE i każ ziomkowi się cofnąć
	newsD[id].gameMode = EXPLORE;
	newsD[id].areaToGoBackAfterDealX = areaToGoBackAfterDealX;
	newsD[id].areaToGoBackAfterDealY = areaToGoBackAfterDealY;

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