#include "Character.h"

/*extern int char_id;

Character::Character() {
	id = char_id++;
}
*/

/////////// 	KONSTRUKTORY
Character::Character():strength(0), vitality(0), intelligence(0) {
}

Character::~Character() {
}

Character::Character(int x_, int y_, int s, int i, int v, string fileName): strength(s), intelligence(i), vitality(v){
	setX(x_);
	setY(y_);
	setFileName(fileName);
	myDeck.fill(STARTINGCARDS);
}

///////////////		POZOSTAŁE

void Character::addCards(std::vector<int> v){
	for(int i: v)
	{
		myDeck.addCard(i);
	}
}

void Character::removeCards(std::vector<int> v){
	for(int i: v)
	{
		myDeck.removeCard(i);
	}
}

void Character::changeStrength(int x){
	strength += x;
}

void Character::changeIntelligence(int x){
	intelligence += x;
}

void Character::changeVitality(int x){
	vitality += x;
}

//////////////		VIRTUALNE

areaType Character::checkAdjacent()
{
	return INTERACTING;
}

Mode Character::interaction()
{
	return FIGHT;
}

int Character::freeMoney(){
	return 0;
}
