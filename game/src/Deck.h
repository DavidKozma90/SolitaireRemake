#pragma once
#include <raylib.h>
#include <algorithm>
#include <chrono>
#include <random>
#include <functional>
#include <array>
#include "Card.h"

namespace Solitaire
{
    
class Deck
{
public:
    Deck();

    using ShuffleMethod = std::function<void(CardVector&)>;

    void create(size_t deckNum = 1);
    void shuffle(ShuffleMethod shuffleMethod = {});

    CardVector& getCards();

    Card drawCardFromTop();
    bool isEmpty() const;
    size_t getSize() const;

    void insert(const Card& card);
    void refill(const CardVector& cardsToRefill);

    CardPos deckPos;
private:
    CardVector m_Cards;
};

}