#include "Location.h"
#include "Character.h"
#include "Dealer.h"
#include "Chest.h"
#include "Nature.h"
#include <string>

using namespace std;


Location::Location(string fileName, int newId): backgroundSource(fileName), id(newId) {
	for (int i = 0; i < areasCountX; ++i)
		for (int k = 0; k < areasCountY; ++k)
			occupation[i][k] = nullptr;

	Character* mob = new Character(/* x, y, s, i, v, name*/ 7, 5, 1, 10, 3, "mob1.png");
	occupation[7][5] = mob;

	Dealer* dealer = new Dealer(/* x, y, saleFactor, name*/5, 3, 0.5, "dealer1.png");
	occupation[5][3] = dealer;

	Chest* chest = new Chest(/* x, y, gold, name */4, 8, 20, "chest1.png");
	occupation[4][8] = chest;

	Nature* nature = new Nature(/* x, y, name */ 7, 7, "nature1.png");
	occupation[7][7] = nature;
}

Location::Location() {

}
Location::~Location() {
}

int Location::getId() const{
	return id;
}

string Location::getSrc() const{
	return backgroundSource;
}
