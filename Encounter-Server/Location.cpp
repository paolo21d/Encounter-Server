#include "Location.h"
#include <SFML\Graphics.hpp>
#include <SFML\Network.hpp>
#include <SFML\Window.hpp>
using namespace std;


Location::Location(string addres) {
	sf::Texture texture;
	texture.loadFromFile(addres);
	sf::Sprite sprite;
	sprite.setTexture(texture);
}


Location::~Location() {
}
