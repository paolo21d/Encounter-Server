#pragma once
#include "Object.h"
#include "News.h"

class Character : public Object{
	int id;				//potrzebne do testów, potem może usuniemy
public:
	Character();
	~Character();
	int getId() const;
	virtual Mode interaction() = 0;
	virtual areaType checkAdjacent();
};
