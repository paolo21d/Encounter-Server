#pragma once
#ifndef MANACARD_H
#define MANACARD_H

#include "Card.h"
class ManaCard : public Card {
	unsigned manaPoints;
public:
	ManaCard();
	~ManaCard();

	void action(); 
};

#endif // !MANACARD_H