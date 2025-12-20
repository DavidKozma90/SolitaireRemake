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

        Lane(const Lane&) = default;
        Lane& operator=(const Lane&) = default;

        // note: had to enable move semantics for std::array initialization :) live and learn
        Lane(Lane&&) noexcept = default;
        Lane& operator=(Lane&&) noexcept = default;

        Lane(int laneIndex, int hidden, int playing);
        void Fill(Deck& fromDeck);

        void InsertCards(const CardVector& cardsToInsert);
        CardVector RemoveCards(int howMany);
        
        int GetNumberOfHiddenCards() const;
        int GetNumberOfPlayingCards() const;
        Utils::IVector2 GetLaneOffset() const;
        PlayingCardVector& GetAllPlayingCards();
        void ConvertHiddenToPlaying();
        bool IsLaneEmpty() const;
        bool IsPlayingCardsEmpty() const;
        bool IsHiddenCardsEmpty() const;

        int GetLaneIndex() const;
        int GetLaneIndexFromPosition(int x, int y) const;
        int GetPlayingCardIndexFromPosition(int x, int y) const;

        Rectangle GetPlayingCardArea() const;
        Rectangle GetMovedPlayingCardArea(int cardIndex) const;

    private:
        int m_LaneIndex = 0;
        CardVector m_HiddenCards;
        PlayingCardVector m_PlayingCards;
        Utils::IVector2 m_LaneOffset = {0, 0};

        void insertCardsToLane(const CardVector& cardsToInsert, int elementOffset);
    };
}