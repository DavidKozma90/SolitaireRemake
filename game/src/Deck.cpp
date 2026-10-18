#include "Deck.h"

namespace Solitaire
{

Deck::Deck()
{
    Deck::create(1);
    deckPos.setOffset({Constants::DECK_ORIGIN_X, Constants::DECK_ORIGIN_Y});
}

void Deck::create(size_t deckNum)
{
    constexpr std::array suits
    {
        Suit::Hearts, Suit::Diamonds, Suit::Clubs, Suit::Spades 
    };

    constexpr std::array ranks
    {
        Rank::Ace, Rank::Two, Rank::Three, Rank::Four, Rank::Five, Rank::Six,
        Rank::Seven, Rank::Eight, Rank::Nine, Rank::Ten, Rank::Jack, Rank::Queen, Rank::King
    };

    m_Cards.clear();
    m_Cards.reserve(deckNum * suits.size() * ranks.size());

    for (size_t n{}; n < deckNum; ++n)
    {
        for (const auto suit : suits)
        {
            for (const auto rank : ranks)
            {
                m_Cards.emplace_back(rank, suit);
            }
        }
    }
}

void Deck::shuffle(ShuffleMethod shuffleMethod)
{
    if (shuffleMethod)
    {
        shuffleMethod(m_Cards);
    }
    else
    {
        // Default shuffle if non provided
        auto seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::shuffle(m_Cards.begin(), m_Cards.end(), std::default_random_engine((uint32_t)seed));
    }
}

CardVector& Deck::getCards()
{
    return m_Cards;
}

Card Deck::drawCardFromTop()
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