#include "PlayingCard.h"

Solitaire::PlayingCard::PlayingCard(Rank rank, Suit suit, Utils::IVector2 offset) : m_Card(rank, suit), m_Coordinates()
{
    const Utils::IVector2 sourceOffset = { static_cast<int>(rank) - 1, static_cast<int>(suit) };

    m_Coordinates.setCardSourceCoordinates(sourceOffset);
    m_Coordinates.setOffset(offset);
}

Solitaire::Card Solitaire::PlayingCard::getCard() const
{
    return m_Card;
}

Solitaire::CardPos Solitaire::PlayingCard::getCardPosition() const
{
    return m_Coordinates;
}

Solitaire::PlayingCard Solitaire::CardFactory::createPlayingCard(const Card& card, Utils::IVector2 offset)
{
    return PlayingCard(card.getRank(), card.getSuit(), offset);
}

Solitaire::Card Solitaire::CardFactory::createCardFromPlayingCard(const PlayingCard& playingCard)
{
    return playingCard.getCard();
}

Solitaire::CardVector Solitaire::CardFactory::createCardVectorFromPlayingCardVector(const PlayingCardVector& playingCardVector)
{
    CardVector cardsToBeCreated;
    cardsToBeCreated.reserve(playingCardVector.size());

    for(size_t i{}; i < playingCardVector.size(); ++i)
    {
        cardsToBeCreated.push_back(createCardFromPlayingCard(playingCardVector[i]));
    }

    return cardsToBeCreated;
}

template<typename T>
void Solitaire::CardTransfer::TransferElements(std::vector<T>& source, std::vector<T>& destination, size_t howMany)
{
    for (size_t i{}; (i < howMany) && (!source.empty()); ++i)
    {
        destination.push_back(source.back());
        source.pop_back();
    }
}

template void Solitaire::CardTransfer::TransferElements<Solitaire::Card>(std::vector<Solitaire::Card>& source,
                                                                         std::vector<Solitaire::Card>& destination,
                                                                         size_t howMany);
template void Solitaire::CardTransfer::TransferElements<Solitaire::PlayingCard>(std::vector<Solitaire::PlayingCard>& source,
                                                                                std::vector<Solitaire::PlayingCard>& destination,
                                                                                size_t howMany);

void Solitaire::CardTransfer::TransformPlayingCardsToCards(PlayingCardVector &source, CardVector &destination, size_t howMany)
{
    for (size_t i{}; (i < howMany) && (!source.empty()); ++i)
    {
        destination.push_back(CardFactory::createCardFromPlayingCard(source.back()));
        source.pop_back();
    }
}
