#include "Lane.h"

Solitaire::Lane::Lane(int laneIndex, int hidden, int playing) : m_NumberOfHiddenCards(hidden), m_NumberOfPlayingCards(playing), m_LaneIndex(laneIndex)
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
    insertCardsToLane(cardsToInsert, GetNumberOfPlayingCards());

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

int Solitaire::Lane::GetNumberOfHiddenCards() const
{
    return static_cast<int>(m_HiddenCards.size());
}

int Solitaire::Lane::GetNumberOfPlayingCards() const
{
    return static_cast<int>(m_PlayingCards.size());
}

Utils::IVector2 Solitaire::Lane::GetLaneOffset() const
{
    return m_LaneOffset;
}

Solitaire::PlayingCardVector& Solitaire::Lane::GetAllPlayingCards()
{
    return m_PlayingCards;
}

void Solitaire::Lane::ConvertHiddenToPlaying()
{
    if(!m_HiddenCards.empty() && m_PlayingCards.empty())
    {
        CardVector tempCard;
        tempCard.reserve(1);

        CardTransfer::TransferCards(m_HiddenCards, tempCard, 1);
        insertCardsToLane(tempCard, 0);

        --m_NumberOfHiddenCards;
        ++m_NumberOfPlayingCards;   
    }
}

bool Solitaire::Lane::IsLaneEmpty() const
{
    return (m_HiddenCards.empty() && m_PlayingCards.empty());
}

bool Solitaire::Lane::IsPlayingCardsEmpty() const 
{
    return m_PlayingCards.empty();
}

bool Solitaire::Lane::IsHiddenCardsEmpty() const
{
    return m_HiddenCards.empty();
}

int Solitaire::Lane::GetLaneIndex() const
{
    return m_LaneIndex;
}

int Solitaire::Lane::GetLaneIndexFromPosition(int x, int y) const
{
    int currentLaneIndex = Constants::INVALID_LANE_INDEX;
    const int retractedOffsetY = (IsPlayingCardsEmpty()) ? ((IsHiddenCardsEmpty()) ? 0 : Constants::HIDDEN_CARD_OFFSET_Y ) : Constants::LANE_OFFSET_Y;

    if((x >= m_LaneOffset.x) && (x <= (m_LaneOffset.x + Constants::RENDERED_SPRITE_WIDTH)) &&
       (y >= m_LaneOffset.y) && (y <= (m_LaneOffset.y + Constants::RENDERED_SPRITE_HEIGHT + (GetNumberOfHiddenCards() * Constants::HIDDEN_CARD_OFFSET_Y) + (GetNumberOfPlayingCards() * Constants::LANE_OFFSET_Y) - retractedOffsetY)))
    {
        currentLaneIndex = m_LaneIndex;
    }

    return currentLaneIndex;
}

void Solitaire::Lane::insertCardsToLane(const CardVector& cardsToInsert, int elementOffset)
{
    for(int i = 0; i < static_cast<int>(cardsToInsert.size()); ++i)
    {
        Utils::IVector2 offset =
        {
            m_LaneOffset.x,
            m_LaneOffset.y + (Constants::HIDDEN_CARD_OFFSET_Y * GetNumberOfHiddenCards()) + ((i + elementOffset) * Constants::LANE_OFFSET_Y)
        };

        m_PlayingCards.push_back(CardFactory::CreatePlayingCard(cardsToInsert[i], offset));
    }
}
