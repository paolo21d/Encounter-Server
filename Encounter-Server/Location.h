#pragma once
#ifndef  LOCATION_H
#define LOCATION_H
#include <SFML\Graphics.hpp>
#include <SFML\Window.hpp>
#include <string>
class Location {
	sf::Texture texture;
	sf::Sprite sprite;
	//ptr na Sprite- grafike lokacji
public:
	Location(std::string addres);
	~Location();
};

#endif // ! LOCATION_H