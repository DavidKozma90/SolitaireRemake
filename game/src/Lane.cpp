#include "Lane.h"

Solitaire::Lane::Lane(int laneIndex, int hidden, int playing) : m_NumberOfHiddenCards(hidden), m_NumberOfPlayingCards(playing)
{
    m_HiddenCards.clear();
    m_PlayingCards.clear();
    m_HiddenCards.reserve(hidden);
    m_PlayingCards.reserve(playing);
    m_LaneOffset = {Constants::LANE_ORIGIN_X + (laneIndex * Constants::LANE_OFFSET_X), Constants::LANE_ORIGIN_Y};
}

void Solitaire::Lane::Fill(Deck& fromDeck)
{
    CardVector& deckCards = fromDeck.GetCards();
    CardVector tempPlayingCards;

    tempPlayingCards.reserve(m_NumberOfPlayingCards);

    CardTransfer::TransferCards(deckCards, m_HiddenCards, m_NumberOfHiddenCards);
    CardTransfer::TransferCards(deckCards, tempPlayingCards, m_NumberOfPlayingCards);

    insertCardsToLane(tempPlayingCards, 0);
}

void Solitaire::Lane::InsertCards(const CardVector& cardsToInsert)
{
    insertCardsToLane(cardsToInsert, m_NumberOfPlayingCards);

    m_NumberOfPlayingCards += static_cast<int>(cardsToInsert.size());
}


Solitaire::CardVector Solitaire::Lane::RemoveCards(int howMany)
{
    CardVector removedCards;
    removedCards.reserve(howMany);

    CardTransfer::TransferPlayingCardsToCards(m_PlayingCards, removedCards, howMany);

    if(howMany <= m_NumberOfPlayingCards)
    {
        m_NumberOfPlayingCards -= howMany;
    }
    else
    {
        m_NumberOfPlayingCards = 0;
    }

    return removedCards;
}

size_t Solitaire::Lane::GetNumberOfHiddenCards() const
{
    return m_HiddenCards.size();
}

size_t Solitaire::Lane::GetNumberOfPlayingCards() const
{
    return m_PlayingCards.size();
}

Utils::IVector2 Solitaire::Lane::GetLaneOffset() const
{
    return m_LaneOffset;
}

Solitaire::PlayingCardVector& Solitaire::Lane::GetAllPlayingCards()
{
    return m_PlayingCards;
}

void Solitaire::Lane::insertCardsToLane(const CardVector &cardsToInsert, int index)
{
    for(int i = 0; i < static_cast<int>(cardsToInsert.size()); ++i)
    {
        Utils::IVector2 offset =
        {
            m_LaneOffset.x,
            m_LaneOffset.y + (Constants::HIDDEN_CARD_OFFSET_Y * static_cast<int>(m_HiddenCards.size())) + ((i + index) * Constants::LANE_OFFSET_Y)
        };

        m_PlayingCards.push_back(CardFactory::CreatePlayingCard(cardsToInsert[i], offset));
    }
}
