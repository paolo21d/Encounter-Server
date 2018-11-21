#ifndef NEWS_H
#define NEWS_H
#include <iostream>
#include <fstream>
#include "Character.h"

enum Mode{EXPLORE, FIGHT, DEAL};

struct News{

	Mode gameMode;
	const Character* firstFighter;
	const Character* secondFighter;
	double SALEFACTOR;
	
	friend std::ostream& operator<<(std::ostream& os, const News& x);

};

#endif
