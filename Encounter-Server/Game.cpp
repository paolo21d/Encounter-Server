#include "Game.h"
#include "Location.h"
#include "Hero.h"
#include "EncException.h"
#include "Object.h"

using namespace std;
using namespace sf;

Game::Game() {
}

Game::~Game() {
}


void Game::game(int num, int socnum) {
	//tutaj jest calutka gra, wymiana informacji itp
}

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
