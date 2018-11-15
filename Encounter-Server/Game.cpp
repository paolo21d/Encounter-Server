#include "Game.h"
using namespace std;


Game::Game() {
}

Game::~Game() {
}

void Game::startConnection() {
	sf::TcpListener listener;
	listener.listen(2000);
	vector<thread> th;
	thread tabth[10];
	unsigned ileSoc = 0;
	while (ileSoc<2) {
		/*sockets.push_back(new sf::TcpSocket);
		soc = sockets.end();*/
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
	}
}

void Game::game(int num, int socnum) {
	//tutaj jest calutka gra, wymiana informacji itp
}
