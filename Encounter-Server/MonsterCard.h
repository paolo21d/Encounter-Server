#pragma once
#ifndef MONSTERCARD_H
#define MONSTERCARD_H

#include "Card.h"
class MonsterCard : public Card {
	unsigned damage;
public:
	MonsterCard();
	~MonsterCard();

	//void action(); //argument CardUser
};

#endif // !MONSTERCARD_H