#pragma once
#ifndef BUFFCARD_H
#define BUFFCARD_H

#include "Card.h"
class BuffCard : public Card {
	unsigned addDamage;
public:
	BuffCard();
	~BuffCard();

	void action(); //argument CardUser
};

#endif // !BUFFCARD_H