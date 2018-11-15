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
	
}