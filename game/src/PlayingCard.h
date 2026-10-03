#pragma once
#include <cstdint>
#include "Card.h"
#include "CardPos.h"

namespace Solitaire
{
class PlayingCard
{
public:
    PlayingCard(Rank rank, Suit suit, Utils::IVector2 offset);
    
    Card getCard() const;
    CardPos getCardPosition() const;
    
private:
    Card m_Card;
    CardPos m_Coordinates;
};

using PlayingCardVector = std::vector<PlayingCard>;
struct CardFactory
{
    static PlayingCard createPlayingCard(const Card& card, Utils::IVector2 offset);
    static Card createCardFromPlayingCard(const PlayingCard& playingCard);
    static CardVector createCardVectorFromPlayingCardVector(const PlayingCardVector& playingCardVector);
};

struct CardTransfer
{
    template<typename T>
    static void Solitaire::CardTransfer::TransferElements(std::vector<T>& source, std::vector<T>& destination, size_t howMany);
    static void Solitaire::CardTransfer::TransformPlayingCardsToCards(PlayingCardVector& source, CardVector& destination, size_t howMany);
};

}