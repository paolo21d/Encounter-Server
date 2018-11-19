#pragma once
#include "Object.h"


class Character : public Object{
	
public:
	Character();
	~Character();

	virtual void interaction(const Hero& invader) = 0;
};

