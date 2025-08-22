#pragma once
#include "Card.h"
#include "CardPos.h"

namespace Solitaire
{
    class PlayingCard
    {
        public:
        PlayingCard() = delete;
        PlayingCard(Rank rank, Suit suit, Utils::IVector2 offset);
        
        Card& GetCard();
        CardPos& GetCoordinates();
        
        Card CopyCard() const;
        private:
        Card m_Card;
        CardPos m_Coordinates;
    };
    
    typedef std::vector<PlayingCard> PlayingCardVector;
    struct CardFactory
    {
        static PlayingCard CreatePlayingCard(const Card& card, Utils::IVector2 offset);
        static Card CreateCardFromPlayingCard(const PlayingCard& playingCard);
        static CardVector CreateCardVectorFromPlayingCardVector(const PlayingCardVector& playingCardVector);
    };

    struct CardTransfer
    {
        static void TransferCards(CardVector& source, CardVector& destination, int howMany);
        static void TransferPlayingCardsToCards(PlayingCardVector& source, CardVector& destination, int howMany);
    };
}