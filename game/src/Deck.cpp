#include "Deck.h"

Solitaire::Deck::Deck()
{
    CreateDeck();
    //ShuffleDeck();
    
    deckPos.SetOffset({Constants::DECK_ORIGIN_X, Constants::DECK_ORIGIN_Y});
}

void Solitaire::Deck::CreateDeck()
{
    m_Cards.clear();
    m_Cards.reserve(Constants::NUMBER_OF_CARDS_IN_DECK);
    for (int suit = static_cast<int>(Suit::Hearts); suit <= static_cast<int>(Suit::Spades); ++suit)
    {
        for (int rank = static_cast<int>(Rank::Ace); rank <= static_cast<int>(Rank::King); ++rank)
        {
            m_Cards.emplace_back(static_cast<Rank>(rank), static_cast<Suit>(suit));
        }
    }
}
void Solitaire::Deck::ShuffleDeck()
{
    auto seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::shuffle(m_Cards.begin(), m_Cards.end(), std::default_random_engine((uint32_t)seed));
}

Solitaire::CardVector& Solitaire::Deck::GetCards()
{
    return m_Cards;
}

Solitaire::Card Solitaire::Deck::DrawCard()
{
    Card card = m_Cards.back();
    m_Cards.pop_back();
    return card;
}

void Solitaire::Deck::InsertCard(const Card& card)
{
    m_Cards.push_back(card);
}

bool Solitaire::Deck::IsEmpty() const
{
    return m_Cards.empty();
}

size_t Solitaire::Deck::GetSize() const
{
    return m_Cards.size();
}

void Solitaire::Deck::RefillDeck(const CardVector& cardsToRefill)
{
    m_Cards.clear();
    m_Cards.insert(m_Cards.end(), cardsToRefill.begin(), cardsToRefill.end());
}
