#pragma once
#ifndef  LOCATION_H
#define LOCATION_H
//#include <SFML\Graphics.hpp>
//#include <SFML\Window.hpp>
#include <string>
#include "Object.h"

extern const unsigned mapSizeX, mapSizeY;
extern const unsigned areaSizeX, areaSizeY;
const unsigned areasCountX = 4;
const unsigned areasCountY = 4;

class Location {
	int id;

public:
	Object* ocupation[areasCountX][areasCountY];

	Location();
	~Location();

};

#endif // ! LOCATION_H
