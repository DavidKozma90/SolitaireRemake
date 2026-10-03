#include "Card.h"

namespace Solitaire
{

Card::Card(Rank rank = Rank::Ace, Suit suit = Suit::Hearts) : m_rank(rank), m_suit(suit) {}

Rank Card::getRank() const 
{ 
    return m_rank; 
}

Suit Card::getSuit() const 
{ 
    return m_suit; 
}

} // namespace Solitaire
