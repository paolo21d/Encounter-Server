#include "Game.h"
#include "Location.h"
#include "Hero.h"
#include "EncException.h"
#include "Object.h"
#include <SFML/Network.hpp>

using namespace std;


Game::Game() {
}

Game::~Game() {
}

void Game::startConnection() {
	/*sf::TcpListener listener;
	listener.listen(2000);
	vector<thread> th;
	thread tabth[10];
	unsigned ileSoc = 0;
	while (ileSoc<2) {
		//sockets.push_back(new sf::TcpSocket);
		//soc = sockets.end();
		sf::TcpSocket soc;
		if (listener.accept(tabsoc[ileSoc]) == sf::Socket::Done) {
			cout << "Wlaczam watek: " << th.size() + 1 << endl;

			//th.push_back(thread(&Communication::srdata, th.size() + 1, ileSoc));
			//th.push_back(thread([=] { srdata(th.size() + 1, ileSoc); }));
			th.push_back(thread(&Game::game, this, th.size() + 1, ileSoc));
			ileSoc++;
		}

	}
	for (unsigned i = 0; i < th.size(); ++i) {
		th[i].join();
	}*/
}

void Game::game(int num, int socnum) {
	//tutaj jest calutka gra, wymiana informacji itp
}

void Game::invalidGame(Hero& myHero, Location& currentLocation)
{	
	startConnection();
	int direction;
	int newX, newY;
	cout << news << endl;
	while(1){try{
		news.reset();
		giveMeDirection();
		cin >> direction;	//0-góra, 1-prawo, 2-dół, 3-lewo
		switch(direction){
			case 0: newX = myHero.getX(); newY = myHero.getY()-1; break;
			case 1: newX = myHero.getX()+1; newY = myHero.getY(); break;
			case 2: newX = myHero.getX(); newY = myHero.getY()+1; break;
			case 3: newX = myHero.getX()-1; newY = myHero.getY(); break;
			default: throw LeavingMap();
		}
		cout << "nowe wsp. " << newX << " " << newY << "stare: " << myHero.getX() << myHero.getY() << endl;
		if(newX >= areasCountX || newX < 0 || newY >= areasCountY || newY < 0)
			throw LeavingMap();
		if(currentLocation.ocupation[newX][newY] != nullptr) 
			currentLocation.ocupation[newX][newY] -> interaction(myHero, news);
		if(news.gameMode != EXPLORE)
			cout << "coś się dzieje..." << endl;
		if(news.gameMode == EXPLORE){
			myHero.setX(newX);
			news.positionX = newX;
			myHero.setY(newY);
			news.positionY = newY;
		}
		if(currentLocation.ocupation[myHero.getX()][myHero.getY() - 1] == nullptr && myHero.getY() != 0)
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
	   	cout << "ups..." << endl;
	   }
	   cout << news << endl;
	}//while
}
