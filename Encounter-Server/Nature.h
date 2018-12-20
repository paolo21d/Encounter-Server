#pragma once
#include "Object.h"

class Nature :
	public Object {
public:
	Nature();
	~Nature();
	
	virtual void interaction(Hero& invader, News& news); 		//nie pozwól wejść
};

