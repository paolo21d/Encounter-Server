#pragma once
#ifndef  LOCATION_H
#define LOCATION_H
#include <string>
#include "Object.h"

extern const unsigned mapSizeX, mapSizeY;
extern const unsigned areaSizeX, areaSizeY;
const unsigned areasCountX = 4;
const unsigned areasCountY = 4;

class Location {
	int id;
	//Object* ocupation[ mapSizeX/areaSizeX ][ mapSizeY/areaSizeY ];

public:
	Object* ocupation[areasCountX][areasCountY];

	//Location(string addres);
	Location();
	~Location();

};

#endif // ! LOCATION_H
