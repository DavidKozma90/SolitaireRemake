#include "PlayingCard.h"

Solitaire::PlayingCard::PlayingCard(Rank rank, Suit suit, IVector2 offset) : m_Card(rank, suit), m_Coordinates()
{
    const IVector2 sourceOffset = { static_cast<int>(rank) - 1, static_cast<int>(suit) };

    m_Coordinates.SetCardSourceCoordinates(sourceOffset);
    m_Coordinates.SetOffset(offset);
}

Solitaire::Card& Solitaire::PlayingCard::GetCard()
{
    return m_Card;
}

Solitaire::CardPos& Solitaire::PlayingCard::GetCoordinates()
{
    return m_Coordinates;
}

Solitaire::Card Solitaire::PlayingCard::CopyCard() const
{
    return m_Card;
}

Solitaire::PlayingCard Solitaire::CardFactory::CreatePlayingCard(const Card& card, IVector2 offset)
{
    return PlayingCard(card.GetRank(), card.GetSuit(), offset);
}

Solitaire::Card Solitaire::CardFactory::CreateCardFromPlayingCard(const PlayingCard& playingCard)
{
    return playingCard.CopyCard();
}
