#pragma once
#include "Object.h"
#include "News.h"
#include "Hero.h"
class Nature :public Object {

public:
	Nature();
	Nature(int x_, int y_, string fileName);
	~Nature();
	
	virtual Mode interaction();
	virtual areaType checkAdjacent();
	virtual int freeMoney();
};

