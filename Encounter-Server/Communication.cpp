#include "Communication.h"



Communication::Communication() {
}


Communication::~Communication() {
}

void Communication::srdata(int num, int socnum) {
	cout << "Melduje watek: " << num << endl;
	//sf::TcpSocket socket = vecsoc.end();
	//socket.create(vecsoc.end());
	int i = 0;
	string msgserwer;
	char buffer[200];
	size_t received;
	while (1) {
		msgserwer = "Dane z serwera " + to_string(num) + ": " + to_string(i);
		i++;
		tabsoc[socnum].send(msgserwer.c_str(), msgserwer.length() + 1);
		//Sleep(1);

		tabsoc[socnum].receive(buffer, sizeof(buffer), received);
		cout << buffer << "Klient: " << num << endl;
	}
}

void Communication::startListenning() {
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
			th.push_back(thread(&Communication::srdata, this, th.size() + 1, ileSoc));
			ileSoc++;
		}

	}
	for (unsigned i = 0; i < th.size(); ++i) {
		th[i].join();
	}
}