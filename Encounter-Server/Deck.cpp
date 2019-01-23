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
            return;
    }
    return;
}

void Deck::removeCard(const int cardNum)    // z tym coś chyba jest nie tak...
{
    int x = 0;
    for(Card* i: deck)
    {
        if(i->getId() == cardNum)
            deck.erase(deck.begin() + x);
            return;
        ++x;
    }
    return;
}

void Deck::fill(int amount)
{
    Card* card;
    for(int i = 0; i < amount; ++i) {
        card = Map::allCards[rand()%Map::allCards.size()];
        deck.push_back(card);
    }
}

void Deck::print()
{
    cout << "Karty: " << endl;
    for(Card* x: deck) {
        cout << x->getId() << " ";
    }
    cout << endl;
}

void Deck::fillRandomCards(vector<int>& v)
{
    int x;
    v.clear();
    for(int i = 0; i < 5 && i < deck.size(); ++i) {
        x = deck[i]->getId();
        v.push_back(x);
    }
    return;
}

int Deck::randomCard()
{
    return deck[rand()%deck.size()]->getId();
}

Card* Deck::kovalskiSupport(int i)
{
    cout << "vwesdfc" << endl;
    for(Card* a: deck) {
        if(a->getId() == i) {
            cout << a->getId() << endl;
            return a;
        }
    }
    return nullptr;
}
