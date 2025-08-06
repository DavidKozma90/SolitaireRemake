#pragma once
#include "Card.h"
#include "CardPos.h"

namespace Solitaire
{
    class PlayingCard
    {
    public:
        PlayingCard() = delete;
        PlayingCard(Rank rank, Suit suit, IVector2 offset);

        Card& GetCard();
        CardPos& GetCoordinates();

        Card CopyCard() const;
    private:
        Card m_Card;
        CardPos m_Coordinates;
    };

    class CardFactory
    {
    public:
        static PlayingCard CreatePlayingCard(const Card& card, IVector2 offset);
        static Card CreateCardFromPlayingCard(const PlayingCard& playingCard);
    };
}