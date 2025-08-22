#pragma once

#include <raylib.h>
#include <vector>
#include "PlayingCard.h"
#include "Deck.h"
#include "Utils.hpp"

namespace Solitaire
{
    class Lane
    {
    public:
        Lane() = default;
        ~Lane() = default;

        Lane(int laneIndex, int hidden, int playing);
        void Fill(Deck& fromDeck);

        void InsertCards(const CardVector& cardsToInsert);
        CardVector RemoveCards(int howMany);
        
        size_t GetNumberOfHiddenCards() const;
        size_t GetNumberOfPlayingCards() const;
        Utils::IVector2 GetLaneOffset() const;
        PlayingCardVector& GetAllPlayingCards();

    private:
        int m_NumberOfHiddenCards = 0;
        int m_NumberOfPlayingCards = 0;
        CardVector m_HiddenCards;
        PlayingCardVector m_PlayingCards;
        Utils::IVector2 m_LaneOffset = {0, 0};

        void insertCardsToLane(const CardVector& cardsToInsert, int index);
    };
}