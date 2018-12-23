#pragma once
#ifndef  LOCATION_H
#define LOCATION_H
#include <SFML\Graphics.hpp>
#include <SFML\Window.hpp>
#include <string>
#include "Object.h"

extern const unsigned mapSizeX = 20, mapSizeY = 15;
extern const unsigned areaSizeX = 50, areaSizeY = 50;

class Location {
	int id;
	Object* ocupation[ mapSizeX/areaSizeX ][ mapSizeY/areaSizeY ];

public:
	Location(std::string addres);
	~Location();
};

#endif // ! LOCATION_H