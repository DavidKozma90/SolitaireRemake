#pragma once

#include <raylib.h>
#include <iostream>
#include <vector>
#include "Constants.h"
#include "CardPos.h"
#include "Utils.hpp"


namespace Solitaire
{

enum class Suit : uint8_t { Hearts, Diamonds, Clubs, Spades };
enum class Rank : uint8_t { Ace = 1, Two, Three, Four, Five, Six, Seven, Eight, Nine, Ten, Jack = 11, Queen = 12, King = 13 };

class Card
{
public:
    DEFAULT_CTOR(Card);
    Card(Rank rank, Suit suit);
    
    Rank getRank() const;
    Suit getSuit() const;
private:
    Rank m_rank;
    Suit m_suit;
};

using CardVector = std::vector<Card>;

}