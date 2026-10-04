#include "Lane.h"
#include "utils.h"

Solitaire::Lane::Lane(int laneIndex, int hidden, int playing) : m_laneIndex(laneIndex)
{
    m_hiddenCards.clear();
    m_playingCards.clear();
    m_hiddenCards.reserve(hidden);
    m_playingCards.reserve(playing);
    m_laneOffset = {Constants::LANE_ORIGIN_X + (laneIndex * Constants::LANE_OFFSET_X), Constants::LANE_ORIGIN_Y};
}

void Solitaire::Lane::fill(Deck& fromDeck)
{
    CardVector& deckCards = fromDeck.getCards();
    CardVector tempPlayingCards;

    tempPlayingCards.reserve(m_playingCards.capacity());

    CardTransfer::TransferElements<Card>(deckCards, m_hiddenCards, m_hiddenCards.capacity());
    CardTransfer::TransferElements<Card>(deckCards, tempPlayingCards, m_playingCards.capacity());

    insertCardsToLane(tempPlayingCards, 0);
}

void Solitaire::Lane::insertCards(const CardVector& cardsToInsert)
{
    insertCardsToLane(cardsToInsert, getNumberOfPlayingCards());
}


Solitaire::CardVector Solitaire::Lane::removeCards(size_t howMany)
{
    CardVector removedCards;

    if ((howMany != 0) && (howMany <= getNumberOfPlayingCards()))
    {
        removedCards.reserve(howMany);
        CardTransfer::TransformPlayingCardsToCards(m_playingCards, removedCards, howMany);
    }
    else
    {
        removedCards.clear();
        TRACELOG(LOG_WARNING, "GAME: You are trying to remove [%d] cards cards from a lane that has currently [%d] playing cards!", howMany, getNumberOfPlayingCards());
    }

    return removedCards;
}

size_t Solitaire::Lane::getNumberOfHiddenCards() const
{
    return m_hiddenCards.size();
}

size_t Solitaire::Lane::getNumberOfPlayingCards() const
{
    return m_playingCards.size();
}

Utils::IVector2 Solitaire::Lane::getLaneOffset() const
{
    return m_laneOffset;
}

Solitaire::PlayingCardVector& Solitaire::Lane::getAllPlayingCards()
{
    return m_playingCards;
}

const Solitaire::PlayingCardVector& Solitaire::Lane::getAllPlayingCards() const
{
    return m_playingCards;
}

void Solitaire::Lane::convertTopHiddenCardToPlayingCard()
{
    if(hasHiddenCards() && hasNoPlayingCards())
    {
        CardVector tempCard;
        tempCard.reserve(1);

        CardTransfer::TransferElements<Card>(m_hiddenCards, tempCard, 1);
        insertCardsToLane(tempCard, 0);
    }
}

bool Solitaire::Lane::isLaneEmpty() const
{
    return (m_hiddenCards.empty() && m_playingCards.empty());
}

bool Solitaire::Lane::hasNoPlayingCards() const 
{
    return m_playingCards.empty();
}

bool Solitaire::Lane::hasNoHiddenCards() const
{
    return m_hiddenCards.empty();
}

bool Solitaire::Lane::hasPlayingCards() const
{
    return (m_playingCards.empty() == false);
}

bool Solitaire::Lane::hasHiddenCards() const
{
    return (m_hiddenCards.empty() == false);
}

int32_t Solitaire::Lane::getLaneIndex() const
{
    return m_laneIndex;
}

int32_t Solitaire::Lane::getLaneIndexFromPosition(int32_t x, int32_t y) const
{
    int32_t currentLaneIndex = Constants::INVALID_INDEX;
    const int32_t retractedOffsetY = (hasNoPlayingCards()) ? ((hasNoHiddenCards()) ? 0 : Constants::HIDDEN_CARD_OFFSET_Y ) : Constants::LANE_OFFSET_Y;

    if((x >= m_laneOffset.x) && (x <= (m_laneOffset.x + Constants::RENDERED_SPRITE_WIDTH)) &&
       (y >= m_laneOffset.y) && (y <= (m_laneOffset.y + Constants::RENDERED_SPRITE_HEIGHT + (getNumberOfHiddenCards() * Constants::HIDDEN_CARD_OFFSET_Y) + (getNumberOfPlayingCards() * Constants::LANE_OFFSET_Y) - retractedOffsetY)))
    {
        currentLaneIndex = m_laneIndex;
    }

    return currentLaneIndex;
}

int32_t Solitaire::Lane::getPlayingCardIndexFromPosition(int32_t x, int32_t y) const
{
    int32_t currentPlayingCardIndex = Constants::INVALID_INDEX;

    if(hasPlayingCards())
    {
        if((x >= m_laneOffset.x) && 
           (x <= (m_laneOffset.x + Constants::RENDERED_SPRITE_WIDTH)) &&
           (y >= (m_laneOffset.y + (getNumberOfHiddenCards() * Constants::HIDDEN_CARD_OFFSET_Y))) && 
           (y <= (m_laneOffset.y + Constants::RENDERED_SPRITE_HEIGHT + (getNumberOfHiddenCards() * Constants::HIDDEN_CARD_OFFSET_Y) + (getNumberOfPlayingCards() * Constants::LANE_OFFSET_Y) - Constants::LANE_OFFSET_Y)))
        {
            const int32_t relativeY = y - (m_laneOffset.y + (getNumberOfHiddenCards() * Constants::HIDDEN_CARD_OFFSET_Y));
            currentPlayingCardIndex = relativeY / Constants::LANE_OFFSET_Y;
            if(currentPlayingCardIndex >= getNumberOfPlayingCards())
            {
                currentPlayingCardIndex = getNumberOfPlayingCards() - 1;
            }
        }
    }

    return currentPlayingCardIndex;
}

Rectangle Solitaire::Lane::getPlayingCardArea() const
{
    return 
    {
        static_cast<float>(m_laneOffset.x), 
        static_cast<float>(m_laneOffset.y + (getNumberOfHiddenCards() * Constants::HIDDEN_CARD_OFFSET_Y)), 
        static_cast<float>(Constants::RENDERED_SPRITE_WIDTH), 
        static_cast<float>(Constants::RENDERED_SPRITE_HEIGHT + (getNumberOfPlayingCards() * Constants::LANE_OFFSET_Y) - Constants::LANE_OFFSET_Y)
    };
}

Rectangle Solitaire::Lane::getMovedPlayingCardArea(int32_t cardIndex) const
{
    return 
    {
        static_cast<float>(m_laneOffset.x), 
        static_cast<float>(m_laneOffset.y + (getNumberOfHiddenCards() * Constants::HIDDEN_CARD_OFFSET_Y) + (cardIndex * Constants::LANE_OFFSET_Y)), 
        static_cast<float>(Constants::RENDERED_SPRITE_WIDTH), 
        static_cast<float>(Constants::RENDERED_SPRITE_HEIGHT + ((getNumberOfPlayingCards() - cardIndex - 1) * Constants::LANE_OFFSET_Y))
    };
}

void Solitaire::Lane::insertCardsToLane(const CardVector& cardsToInsert, int32_t elementOffset)
{
    for(size_t i{}; i < cardsToInsert.size(); ++i)
    {
        const int32_t laneElementOffset = (Constants::HIDDEN_CARD_OFFSET_Y * getNumberOfHiddenCards()) + ((i + elementOffset) * Constants::LANE_OFFSET_Y);
        m_playingCards.push_back(CardFactory::createPlayingCard(cardsToInsert[i], { m_laneOffset.x, (m_laneOffset.y + laneElementOffset) }));
    }
}
