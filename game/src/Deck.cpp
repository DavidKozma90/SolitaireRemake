#include "Deck.h"

Solitaire::Deck::Deck()
{
    createDeck();
    shuffleDeck();
}

void Solitaire::Deck::createDeck()
{
    m_Cards.clear();
    m_Cards.reserve(52);
    for (int suit = static_cast<int>(Suit::Hearts); suit <= static_cast<int>(Suit::Spades); ++suit)
    {
        for (int rank = static_cast<int>(Rank::Ace); rank <= static_cast<int>(Rank::King); ++rank)
        {
            m_Cards.emplace_back(static_cast<Rank>(rank), static_cast<Suit>(suit));
        }
    }
}
void Solitaire::Deck::shuffleDeck()
{
    auto seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::shuffle(m_Cards.begin(), m_Cards.end(), std::default_random_engine((const unsigned int)seed));
}

Solitaire::Card Solitaire::Deck::drawCard()
{
    if (!isEmpty())
    {
        Card card = m_Cards.back();
        m_Cards.pop_back();
        return card;
    }
    else
    {
        return Card(Rank::Ace, Suit::Clubs);
    }
}
bool Solitaire::Deck::isEmpty() const
{
    return m_Cards.empty();
}

void Solitaire::Deck::renderDeck(Texture2D &texture)
{
}
