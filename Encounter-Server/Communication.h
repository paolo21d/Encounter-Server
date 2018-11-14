#pragma once
#include <iostream>
#include <thread>
#include <string>
#include <mutex>
#include <vector>
#include <SFML/Network.hpp>
using namespace std;
class Communication {
public:
	Communication();
	~Communication();

	void startListenning() {
		sf::TcpListener listener;
		listener.listen(2000);
		vector<thread> th;
		thread tabth[10];
		int ileSoc = 0;
		while (ileSoc<10) {
			/*sockets.push_back(new sf::TcpSocket);
			soc = sockets.end();*/
			sf::TcpSocket soc;
			if (listener.accept(tabsoc[ileSoc]) == sf::Socket::Done) {
				cout << "Wlaczam watek: " << th.size() + 1 << endl;
				//vecsoc.push_back(soc);

				//thread t(srdata, th.size() + 1, ileSoc);
				//th.push_back(t);

				th.push_back(thread(srdata, th.size() + 1, ileSoc));
				ileSoc++;
			}

		}
		for (unsigned i = 0; i < th.size(); ++i) {
			th[i].join();
		}
		return true;
	}
};

