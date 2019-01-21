#include "Map.h"
#include <string>
using namespace std;


vector<Card*> Map::allCards = {};

Map::Map() {

    for(int i = 0; i < CARDSAMOUNT; ++i)
    {
        Map::allCards.push_back(new Card(string("card")+to_string(i)+string(".png"), 1, 1, 1, i));
    }

    Location* location;
    char a;
    string s;
    for(int i = 0; i < locationAmount; ++i)
    {
        a = '0' + i;
        s = a;
        location = new Location(string("location") + s + string(".png"), i);
        locations.push_back(location);
    }
    
}


Map::~Map() {
    //for(int i = locations.size() - 1; i >= 0; --i)
        //delete &locations[i];
}
