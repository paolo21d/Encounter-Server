#include "Deck.h"
#include "Map.h"


Deck::Deck() {
}


Deck::~Deck() {
}

void Deck::addCard(const int cardNum)
{
    for(Card* i: Map::allCards)
    {
        if(cardNum == i->getId())
            deck.push_back(i);
    }
}

void Deck::removeCard(const int cardNum)    // z tym coś chyba jest nie tak...
{
    int x = 0;
    for(Card* i: deck)
    {
        if(i->getId() == cardNum)
            deck.erase(deck.begin() + x);
        ++x;
    }
}
