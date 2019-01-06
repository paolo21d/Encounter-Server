#include "Character.h"

/*extern int char_id;

Character::Character() {
	id = char_id++;
}
*/

Character::Character() {

}

Character::~Character() {
}

int Character::getId() const{
	return id;
}

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

areaType Character::checkAdjacent()
{
	return INTERACTING;
}

Mode Charater::interaction()
{
	return FIGHT;
}
