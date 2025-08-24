#pragma once

#include <raylib.h>
#include <iostream>
#include <vector>
#include "Constants.h"
#include "CardPos.h"
#include "Utils.hpp"


namespace Solitaire
{
    enum class Suit { Hearts, Diamonds, Clubs, Spades };
    enum class Rank { Ace = 1, Two, Three, Four, Five, Six, Seven, Eight, Nine, Ten, Jack = 11, Queen = 12, King = 13 };

    class Card
    {
    public:
        Card() = default;
        ~Card() = default;
        Card(Rank rank, Suit suit);
        
        Rank GetRank() const;
        Suit GetSuit() const;
    private:
        Rank m_Rank = Rank::Ace;
        Suit m_Suit = Suit::Hearts;
    };
    
    typedef std::vector<Card> CardVector;
}