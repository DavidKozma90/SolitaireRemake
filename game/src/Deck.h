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

        void CreateDeck();
        void ShuffleDeck();

        Card DrawCard();
        bool IsEmpty() const;
        size_t GetSize() const;

        CardPos deckPos;
    private:
        std::vector<Card> m_Cards;
    };
}