#include "Card.h"

Solitaire::Card::Card(Rank rank, Suit suit) : m_Rank(rank), m_Suit(suit) 
{
    const int cardOffsetX = static_cast<int>(m_Rank) - 1;
    const int cardOffsetY = static_cast<int>(m_Suit);

    m_SourceRectangle = 
    {
        static_cast<float>(Constants::ORIGIN_X + (cardOffsetX * Constants::SPRITE_OFFSET_X)), 
        static_cast<float>(Constants::ORIGIN_Y + (cardOffsetY * Constants::SPRITE_OFFSET_Y)), 
        static_cast<float>(Constants::SPRITE_WIDTH), 
        static_cast<float>(Constants::SPRITE_HEIGHT)
    };
}

Solitaire::Card::Card(Rank rank, Suit suit, Vector2 offset) : Card(rank, suit)
{
    this->SetCoords(offset);
}

Solitaire::Rank Solitaire::Card::GetRank() const 
{ 
    return m_Rank; 
}

Solitaire::Suit Solitaire::Card::GetSuit() const 
{ 
    return m_Suit; 
}

void Solitaire::Card::Render(Texture2D& texture)
{        
    DrawTexturePro(texture, m_SourceRectangle, m_DestinationRectangle, {0, 0}, 0.0f, WHITE);
}

Rectangle Solitaire::Card::GetCoords()
{ 
    return m_DestinationRectangle; 
}

void Solitaire::Card::PrintCardCoordinates() const
{
    std::cout << "Card (x0, y0, width, height): " << m_DestinationRectangle.x << ", " << m_DestinationRectangle.y << ", " 
              << m_DestinationRectangle.width << ", " << m_DestinationRectangle.height << std::endl;
}

void Solitaire::Card::SetCardCoordX(int x)
{
    m_DestinationRectangle.x = x;
}

void Solitaire::Card::SetCardCoordY(int y)
{
    m_DestinationRectangle.y = y;
}

void Solitaire::Card::SetCoords(Vector2 offset)
{
    m_DestinationRectangle.x = offset.x;
    m_DestinationRectangle.y = offset.y;
}
