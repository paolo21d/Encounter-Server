#include "Location.h"
using namespace std;


Location::Location(string addres) {
	texture.loadFromFile(addres);
	sprite.setTexture(texture);
}


Location::~Location() {
}
