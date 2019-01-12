#pragma once
#ifndef OBJECT_H
#define OBJECT_H

#include <string>
#include "News.h"


class Hero;

//extern const unsigned mapSizeX, mapSizeY;		//ile pikseli ma lokacja
//extern const unsigned areaSizeX, areaSizeY;		//ile pikseli ma pole

class Object {	
	//int id;
	int x, y;					//współrzędne pola, nie piksela; liczne od lewej góry;
	int width;
	std::string fileName;
public:
	Object();
	~Object();
	
	
	int getX() const;
	int getY() const;
	int getId() const;
	std::string getFileName() const;
	void setFileName(std::string newFileName);
	void setX(int x_);
	void setY(int y_);
	Object(int x_, int y_, int width_ = 1);

	virtual Mode interaction() = 0; //Hero,Mob - walka, Dealer-handel, reszta - nic
	virtual areaType checkAdjacent() = 0;
	virtual int freeMoney();
};

#endif // !OBJECT_H
