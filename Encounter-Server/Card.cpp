#include "Card.h"

Card::Card(){

}

Card::Card(const string &n, const unsigned& dmg, const unsigned& costmana) {
}


Card::~Card() {
}

void Card::action(Card* card){
}

void Card::action(){
}

int Card::getId() const {
	return id;
}

string Card::getName() const {
	return name;
}

string Card::getDescription() const {
	return description;
}

string Card::getSrc() const {
	return srcName;
}

unsigned Card::getCostMana() const {
	return costMana;
}
