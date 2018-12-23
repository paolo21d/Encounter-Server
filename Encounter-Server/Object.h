#pragma once
#ifndef OBJECT_H
#define OBJECT_H

class News;
class Hero;

//extern const unsigned mapSizeX, mapSizeY;		//ile pikseli ma lokacja
//extern const unsigned areaSizeX, areaSizeY;		//ile pikseli ma pole

class Object {	
	int x, y;					//współrzędne pola, nie piksela; liczne od lewej góry;
	int width;

public:
	Object();
	~Object();
	
	int getX() const;
	int getY() const;
	void setX(int x_);
	void setY(int y_);
	Object(int x_, int y_, int width_ = 1);
	virtual void interaction(Hero& invader, News& news) = 0; //Hero,Mob - walka, Dealer-handel, reszta - nic
};

#endif // !OBJECT_H
