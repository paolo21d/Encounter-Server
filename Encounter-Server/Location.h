#pragma once
#ifndef  LOCATION_H
#define LOCATION_H
#include <SFML\Graphics.hpp>
#include <SFML\Window.hpp>
#include <string>
#include "Object.h"

extern const unsigned mapSizeX, mapSizeY;
extern const unsigned areaSizeX, areaSizeY;

class Location {
	int id;
	Object* ocupation[mapSizeX/areaSizeX][mapSizeY/areaSizeY];

public:
	Location(std::string addres);
	~Location();
};

#endif // ! LOCATION_H