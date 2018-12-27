#pragma once
#include "Object.h"

class NewsExplore;

class Character : public Object{
	int id;				//potrzebne do testów, potem może usuniemy
public:
	Character();
	~Character();
	int getId() const;
	virtual void interaction(Hero& invader, NewsExplore& news) = 0;
};

