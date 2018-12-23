#pragma once
#include "Object.h"

class Nature :public Object {
	//uchwyt do Slider - obrazek
	int posX, posY; //wspolrzedne dolnego lewego naroznika - pixele
	int x, y; //wspolrzedne pola w ktorym sie znajduje dany objekt, nie pixela
public:
	Nature();
	~Nature();
	
	virtual void interaction(const Hero& invader); 		//nie pozwól wejść
	virtual void draw(); //rysuje dany elemnt natury w zadanej pozycji
};

