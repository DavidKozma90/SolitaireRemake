#include "Card.h"

Solitaire::Card::Card(Rank rank, Suit suit) : m_Rank(rank), m_Suit(suit) {}

Solitaire::Rank Solitaire::Card::getRank() const 
{ 
    return m_Rank; 
}

Solitaire::Suit Solitaire::Card::getSuit() const 
{ 
    return m_Suit; 
}

void Solitaire::Card::DrawCard(Texture2D& texture, int pixelOffsetX, int pixelOffsetY) const
{
    const int cardOffsetX = static_cast<int>(m_Rank) - 1;
    const int cardOffsetY = static_cast<int>(m_Suit);

    const Rectangle source = 
    {
        Constants::ORIGIN_X + (cardOffsetX * Constants::SPRITE_OFFSET_X), 
        Constants::ORIGIN_Y + (cardOffsetY * Constants::SPRITE_OFFSET_Y), 
        Constants::SPRITE_WIDTH, 
        Constants::SPRITE_HEIGHT
    };

    const Rectangle dest = 
    {
        pixelOffsetX, 
        pixelOffsetY, 
        Constants::SPRITE_WIDTH,
        Constants::SPRITE_HEIGHT
    };
        
    DrawTexturePro(texture, source, dest, {0, 0}, 0.0f, WHITE);
}
