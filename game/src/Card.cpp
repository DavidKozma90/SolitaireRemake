#include "Card.h"

Solitaire::Card::Card(Rank rank, Suit suit) : m_Rank(rank), m_Suit(suit) {}

Solitaire::Rank Solitaire::Card::GetRank() const 
{ 
    return m_Rank; 
}

Solitaire::Suit Solitaire::Card::GetSuit() const 
{ 
    return m_Suit; 
}
