#pragma once
#include <raylib.h>
#include <algorithm>
#include <chrono>
#include <random>
#include "Card.h"

namespace Solitaire
{
    
class Deck
{
public:
    Deck();

    void create();
    void shuffle();

    CardVector& getCards();

    Card drawCard();
    bool isEmpty() const;
    size_t getSize() const;

    void insert(const Card& card);
    void refill(const CardVector& cardsToRefill);

    CardPos deckPos;
private:
    CardVector m_Cards;
};

}