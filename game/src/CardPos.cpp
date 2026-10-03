#include "CardPos.h"

Solitaire::CardPos::CardPos()
{
    m_CardPosition = 
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

void Solitaire::CardPos::setCardSourceCoordinates(Utils::IVector2 offset)
{
    m_CardSourceCoords.x = static_cast<float>(Constants::ORIGIN_X + (offset.x * Constants::SPRITE_OFFSET_X));
    m_CardSourceCoords.y = static_cast<float>(Constants::ORIGIN_Y + (offset.y * Constants::SPRITE_OFFSET_Y));
}

void Solitaire::CardPos::setOffset(Utils::IVector2 offset)
{
    m_CardPosition.x = static_cast<float>(offset.x);
    m_CardPosition.y = static_cast<float>(offset.y);
}

Rectangle Solitaire::CardPos::getCardPosition() const
{
    return m_CardPosition;
}

Rectangle Solitaire::CardPos::getCardSourceCoordinates() const
{
    return m_CardSourceCoords;
}

void Solitaire::CardPos::moveX(int dx)
{
    m_CardPosition.x += static_cast<float>(dx);
}

void Solitaire::CardPos::moveY(int dy)
{
    m_CardPosition.y += static_cast<float>(dy);
}

int Solitaire::CardPos::getX() const
{
    return static_cast<int>(m_CardPosition.x);
}

int Solitaire::CardPos::getY() const
{
    return static_cast<int>(m_CardPosition.y);
}

int Solitaire::CardPos::getWidth() const
{
    return static_cast<int>(m_CardPosition.width);
}

int Solitaire::CardPos::getHeight() const
{
    return static_cast<int>(m_CardPosition.height);
}

void Solitaire::CardPos::printCardCoordinates() const
{
    std::cout << "Card (x0, y0, width, height): " << m_CardPosition.x << ", " << m_CardPosition.y << ", " 
              << m_CardPosition.width << ", " << m_CardPosition.height << std::endl;
}
