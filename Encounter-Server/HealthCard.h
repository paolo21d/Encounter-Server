#pragma once
#ifndef HEALTHCARD_H
#define HEALTHCARD_H

#include "Card.h"
class HealthCard : public Card {
	unsigned hpPoints;
public:
	HealthCard();
	~HealthCard();

	//virtual void action();
};

#endif // !HEALTHCARD_H