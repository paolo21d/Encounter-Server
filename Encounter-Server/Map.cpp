#include "Map.h"
#include <string>
using namespace std;


vector<Card*> Map::allCards = {};

Map::Map() {

    for(int i = 0; i < CARDSAMOUNT; ++i)
    {
        Map::allCards.push_back(new Card(string("card")+to_string(i)+string(".png"), 1, 1, 1, i));
    }

    char a;
    string s;
    for(int i = 0; i < locationAmount; ++i)
    {
        a = '0' + i;
        s = a;
        locations.push_back(new Location(string("location") + s + string(".png"), i));
    }
    
}


Map::~Map() {
    for(Card* a: allCards)
    {
        delete a;
    }

    for(Location* b: locations)
    {
        delete b;
    }
}
