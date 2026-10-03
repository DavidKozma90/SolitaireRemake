#include "Card.h"

Solitaire::Card::Card(Rank rank, Suit suit) : m_rank(rank), m_suit(suit) {}

Solitaire::Rank Solitaire::Card::getRank() const 
{ 
    return m_rank; 
}

Solitaire::Suit Solitaire::Card::getSuit() const 
{ 
    return m_suit; 
}
