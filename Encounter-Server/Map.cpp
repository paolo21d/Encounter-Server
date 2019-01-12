#include "Map.h"
#include <string>
using namespace std;

vector<Card*> Map::allCards = {};

Map::Map() {
    Location* location;
    for(int i = 0; i < 4; ++i)
    {
        location = new Location(string sourceName);
        locations[i] = location;
    }
}


Map::~Map() {
}
