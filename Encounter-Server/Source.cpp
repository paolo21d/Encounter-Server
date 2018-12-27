#include <iostream>
#include <SFML/Network.hpp>

#include "Communication.h"
using namespace std;

const unsigned mapSizeX=1000, mapSizeY=550;
const unsigned areaSizeX=50, areaSizeY=25;
int main() {


	//sf::TcpSocket socket;
	//sf::TcpListener listener;
	//sf::IpAddress ip("192.168.0.172");
	//listener.listen(50000);
	//listener.accept(socket);
	/*Game g;
	g.startConnection(); //po tym juz mamy podlaczone 2 usery
	g.sendGraphics(); // wysy³a grafiki do 2 userow tworzac 2 watki
	g.startGame(); //tworzy 2 watki game dla 2 userow*/

	Communication com;
	com.startConnection();

	return 0;
}
