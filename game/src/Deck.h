#pragma once
#include <raylib.h>
#include <vector>
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
        ~Deck() = default;

        void createDeck();
        void shuffleDeck();

        Card drawCard();
        bool isEmpty() const;

    private:
        std::vector<Card> m_Cards;
    };
}