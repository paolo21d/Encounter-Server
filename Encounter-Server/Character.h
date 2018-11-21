#pragma once
#include "Object.h"


class Character : public Object{
	int id;				//potrzebne do testów, potem może usuniemy
public:
	Character();
	~Character();
	int getId() const;
	virtual void interaction(const Hero& invader) = 0;
};

