#include <iostream>
#include <SFML/Network.hpp>
using namespace std;
int main() {
	sf::TcpSocket socket;
	sf::TcpListener listener;
	sf::IpAddress ip("192.168.0.172");
	listener.listen(50000);
	listener.accept(socket);


	return 0;
}