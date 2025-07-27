#include "Card.h"

Solitaire::Card::Card(Rank rank, Suit suit) : m_Rank(rank), m_Suit(suit) 
{
    const IVector2 offset = { static_cast<int>(m_Rank) - 1, static_cast<int>(m_Suit) };

    m_Coordinates.SetCardSourceCoordinates(offset);
}

Solitaire::Card::Card(Rank rank, Suit suit, IVector2 offset) : Card(rank, suit)
{
    m_Coordinates.SetCardDestinationCoordinates(offset);
}

Solitaire::Rank Solitaire::Card::GetRank() const 
{ 
    return m_Rank; 
}

Solitaire::Suit Solitaire::Card::GetSuit() const 
{ 
    return m_Suit; 
}

Solitaire::CardCoordinates& Solitaire::Card::GetCoords()
{
    return m_Coordinates;
}
