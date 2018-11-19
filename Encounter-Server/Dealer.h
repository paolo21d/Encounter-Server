#pragma once
#include "Character.h"
class Dealer :	public Character {
	Deck seldCarts;
	double saleFactor;
	
public:
	Dealer();
	~Dealer();
};

