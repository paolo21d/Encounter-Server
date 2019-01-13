#include "Card.h"

using namespace std;

Card::Card(){

}

Card::Card(const string src, const int dmg, const int mana, const int money, const int num): srcName(src), damage(dmg), costMana(mana), price(money), id(num) {
	description = "pusty opis";
	name = "czterdziesci i cztery";
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

unsigned Card::getPrice() const {
	return price;
}

unsigned Card::getCostGold() const {
	return price;
}

unsigned Card::getDamage() const {
	return damage;
}
