#include "Hero.h"


///////////////////////////		KONSTRUTORY

Hero::Hero(): gold(BASICSTATS) {
	changeStrength(BASICSTATS);
	changeIntelligence(BASICSTATS);
	changeVitality(BASICSTATS);
}

Hero::~Hero() {

}

//////////////////////////////////		POZOSTAŁE

void Hero::addGold(int newGold){
	gold += newGold;
}

void Hero::removeGold(int spentGold){
	gold -= spentGold;
}	

int Hero::getGold() {
	return gold;
}

int Hero::getCurrLocationId(){
	return currentLocation;
}

void Hero::setCurrLocationId(int newLocation){
	currentLocation = newLocation;
}