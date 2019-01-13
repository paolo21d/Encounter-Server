#include "Deck.h"
#include "Map.h"
#include <chrono>

////////////////////////        KONSTRUKTORY

Deck::Deck() {
    deck = {};
}


Deck::~Deck() {
}

///////////////////////     POZOSTAŁE

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

void Deck::fill(int amount)
{
    Card* card;
    for(int i = 0; i < amount; ++i) {
        card = Map::allCards[rand()%Map::allCards.size()];
        deck.push_back(card);
    }
}
