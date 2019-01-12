#pragma once
#ifndef  LOCATION_H
#define LOCATION_H
#include <string>
#include <vector>
#include "Object.h"

extern const unsigned mapSizeX, mapSizeY;
extern const unsigned areaSizeX, areaSizeY;
const unsigned areasCountX = 4;
const unsigned areasCountY = 4;

class Location {
	int id;
	std::string backgroundSource;
	//Object* ocupation[ mapSizeX/areaSizeX ][ mapSizeY/areaSizeY ];

public:
	Object* occupation[areasCountX][areasCountY];

	Location(string fileName, int newId);
	Location();
	~Location(); // usuwać obiekty z occupation !!!
	int getId() const;
	std::string getSrc() const ;

};

#endif // ! LOCATION_H
