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

std::string Card::getCardCode() const
{
    char code[3];

    switch (m_suit)
    {
        case Suit::Hearts : code[0] = 'H'; break;
        case Suit::Diamonds : code[0] = 'D'; break;
        case Suit::Clubs : code[0] = 'C'; break;
        case Suit::Spades : code[0] = 'S'; break;
        default : code[0] = '?'; break;
    }

    switch (m_rank)
    {
        case Rank::Ace   : code[1] = 'A'; break;
        case Rank::Two   : code[1] = '2'; break;
        case Rank::Three : code[1] = '3'; break;
        case Rank::Four  : code[1] = '4'; break;
        case Rank::Five  : code[1] = '5'; break;
        case Rank::Six   : code[1] = '6'; break;
        case Rank::Seven : code[1] = '7'; break;
        case Rank::Eight : code[1] = '8'; break;
        case Rank::Nine  : code[1] = '9'; break;
        case Rank::Ten   : code[1] = 'T'; break;
        case Rank::Jack  : code[1] = 'J'; break;
        case Rank::Queen : code[1] = 'Q'; break;
        case Rank::King  : code[1] = 'K'; break;
        default : code[1] = '?'; break;
    }

    code[2] = '\0';

    return std::string{code};
}

} // namespace Solitaire
