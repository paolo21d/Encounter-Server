#include <iostream>
#include "Object.h"
#include "Nature.h"
#include "Character.h"
#include "Hero.h"
#include "Mob.h"
#include "Dealer.h"
#include "Chest.h"
#include "Card.h"
#include "Deck.h"
#include "News.h"

using namespace std;

News news;
int char_id = 0;

int main()
{
	
	Deck emptyDeck;
	Hero elfhells(emptyDeck, 10, 12, 8, 100);	
	Mob grishnak(emptyDeck, 6, 13, 4);

	cout << elfhells.getId() << " " << grishnak.getId() << endl;
	cout << news;
	grishnak.interaction(elfhells);
	cout << news;







	//////////////////////	Hero tests
	
}
