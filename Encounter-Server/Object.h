#pragma once
#ifndef OBJECT_H
#define OBJECT_H

class Hero;

extern const unsigned mapSizeX, mapSizeY;		//ile pikseli ma lokacja
extern const unsigned areaSizeX, areaSizeY;		//ile pikseli ma pole

class Object {	
	int x, y;					//współrzędne pola, nie piksela
	int width;

public:
	Object();
	~Object();

	Object(int x_, int y_, int width_ = 1);
	virtual void interaction(const Hero& invader) = 0; //Hero,Mob - walka, Dealer-handel, reszta - nic
};

#endif // !OBJECT_H
