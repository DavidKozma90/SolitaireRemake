#include "Deck.h"

namespace Solitaire
{

Deck::Deck()
{
    Deck::create();
    //Deck::shuffle();
    
    deckPos.setOffset({Constants::DECK_ORIGIN_X, Constants::DECK_ORIGIN_Y});
}

void Deck::create()
{
    m_Cards.clear();
    m_Cards.reserve(Constants::NUMBER_OF_CARDS_IN_DECK);
    for (uint8_t suit = static_cast<uint8_t>(Suit::Hearts); suit <= static_cast<uint8_t>(Suit::Spades); ++suit)
    {
        for (uint8_t rank = static_cast<uint8_t>(Rank::Ace); rank <= static_cast<uint8_t>(Rank::King); ++rank)
        {
            m_Cards.emplace_back(static_cast<Rank>(rank), static_cast<Suit>(suit));
        }
    }
}
void Deck::shuffle()
{
    auto seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::shuffle(m_Cards.begin(), m_Cards.end(), std::default_random_engine((uint32_t)seed));
}

CardVector& Deck::getCards()
{
    return m_Cards;
}

Card Deck::drawCard()
{
    Card card = m_Cards.back();
    m_Cards.pop_back();
    return card;
}

void Deck::insert(const Card& card)
{
    m_Cards.push_back(card);
}

bool Deck::isEmpty() const
{
    return m_Cards.empty();
}

size_t Deck::getSize() const
{
    return m_Cards.size();
}

void Deck::refill(const CardVector& cardsToRefill)
{
    m_Cards.clear();
    m_Cards.insert(m_Cards.end(), cardsToRefill.begin(), cardsToRefill.end());
}

} // namespace Solitaire