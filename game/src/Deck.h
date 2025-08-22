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
        ~Deck() = default;

        void CreateDeck();
        void ShuffleDeck();

        CardVector& GetCards();

        Card DrawCard();
        bool IsEmpty() const;
        size_t GetSize() const;

        void InsertCard(const Card& card);
        void RefillDeck(const CardVector& cardsToRefill);

        CardPos deckPos;
    private:
        CardVector m_Cards;
    };
}