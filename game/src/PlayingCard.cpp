#include "PlayingCard.h"

Solitaire::PlayingCard::PlayingCard(Rank rank, Suit suit, Utils::IVector2 offset) : m_Card(rank, suit), m_Coordinates()
{
    const Utils::IVector2 sourceOffset = { static_cast<int>(rank) - 1, static_cast<int>(suit) };

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

Solitaire::PlayingCard Solitaire::CardFactory::CreatePlayingCard(const Card& card, Utils::IVector2 offset)
{
    return PlayingCard(card.GetRank(), card.GetSuit(), offset);
}

Solitaire::Card Solitaire::CardFactory::CreateCardFromPlayingCard(const PlayingCard& playingCard)
{
    return playingCard.CopyCard();
}

Solitaire::CardVector Solitaire::CardFactory::CreateCardVectorFromPlayingCardVector(const PlayingCardVector &playingCardVector)
{
    CardVector cardsToBeCreated;
    cardsToBeCreated.reserve(playingCardVector.size());

    for(size_t i = 0; i < playingCardVector.size(); ++i)
    {
        cardsToBeCreated.push_back(CreateCardFromPlayingCard(playingCardVector[i]));
    }

    return cardsToBeCreated;
}

void Solitaire::CardTransfer::TransferCards(CardVector &source, CardVector &destination, int howMany)
{    
    for(int i = 0; (i < howMany) && (!source.empty()); ++i)
    {
        destination.push_back(source.back());
        source.pop_back();
    }   
}

void Solitaire::CardTransfer::TransferPlayingCardsToCards(PlayingCardVector &source, CardVector &destination, int howMany)
{
    for(int i = 0; (i < howMany) && (!source.empty()); ++i)
    {
        destination.push_back(CardFactory::CreateCardFromPlayingCard(source.back()));
        source.pop_back();
    }
}
