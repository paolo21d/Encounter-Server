#pragma once
#ifndef REMOVALCARD_H
#define REMOVALCARD_H

#include "Card.h"
class RemovalCard : public Card {
	//ptr na karte ktora bedziemy usuwac, chyba 
public:
	RemovalCard();
	~RemovalCard();

	void action(); //argument CardUser
};

#endif // !REMOVALCARD_H