#include "CardCoordinates.h"

Solitaire::CardCoordinates::CardCoordinates()
{
    m_CardDestinationCoords = 
    {
        0, 
        0, 
        static_cast<float>(Constants::RENDERED_SPRITE_WIDTH), 
        static_cast<float>(Constants::RENDERED_SPRITE_HEIGHT)
    };

    m_CardSourceCoords = 
    {
        0, 
        0, 
        static_cast<float>(Constants::SPRITE_WIDTH), 
        static_cast<float>(Constants::SPRITE_HEIGHT)
    };
}

void Solitaire::CardCoordinates::SetCardSourceCoordinates(IVector2 offset)
{
    m_CardSourceCoords.x = static_cast<float>(Constants::ORIGIN_X + (offset.x * Constants::SPRITE_OFFSET_X));
    m_CardSourceCoords.y = static_cast<float>(Constants::ORIGIN_Y + (offset.y * Constants::SPRITE_OFFSET_Y));
}

void Solitaire::CardCoordinates::SetCardDestinationCoordinates(IVector2 offset)
{
    m_CardDestinationCoords.x = static_cast<float>(offset.x);
    m_CardDestinationCoords.y = static_cast<float>(offset.y);
}

Rectangle Solitaire::CardCoordinates::GetCardDestinationCoordinates() const
{
    return m_CardDestinationCoords;
}

Rectangle Solitaire::CardCoordinates::GetCardSourceCoordinates() const
{
    return m_CardSourceCoords;
}

void Solitaire::CardCoordinates::SetX(int x)
{
    m_CardDestinationCoords.x = static_cast<float>(x);
}

void Solitaire::CardCoordinates::SetY(int y)
{
    m_CardDestinationCoords.y = static_cast<float>(y);
}

int Solitaire::CardCoordinates::GetX() const
{
    return static_cast<int>(m_CardDestinationCoords.x);
}

int Solitaire::CardCoordinates::GetY() const
{
    return static_cast<int>(m_CardDestinationCoords.y);
}

int Solitaire::CardCoordinates::GetWidth() const
{
    return static_cast<int>(m_CardDestinationCoords.width);
}

int Solitaire::CardCoordinates::GetHeight() const
{
    return static_cast<int>(m_CardDestinationCoords.height);
}

void Solitaire::CardCoordinates::PrintCardCoordinates() const
{
    std::cout << "Card (x0, y0, width, height): " << m_CardDestinationCoords.x << ", " << m_CardDestinationCoords.y << ", " 
              << m_CardDestinationCoords.width << ", " << m_CardDestinationCoords.height << std::endl;
}
