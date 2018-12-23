#pragma once
#include "Object.h"
#include "News.h"
#include "Hero.h"
class Nature :public Object {
	//uchwyt do Slider - obrazek
	int posX, posY; //wspolrzedne dolnego lewego naroznika - pixele
	int x, y; //wspolrzedne pola w ktorym sie znajduje dany objekt, nie pixela
public:
	Nature();
	~Nature();
	
	virtual void interaction(Hero& invader, News& news); 		//nie pozwól wejść
	virtual void draw(); //rysuje dany elemnt natury w zadanej pozycji
};

