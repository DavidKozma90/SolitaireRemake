#include "CardPos.h"

namespace Solitaire
{

CardPos::CardPos()
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

void CardPos::setCardSourceCoordinates(Utils::IVector2 offset)
{
    m_CardSourceCoords.x = static_cast<float>(Constants::ORIGIN_X + (offset.x * Constants::SPRITE_OFFSET_X));
    m_CardSourceCoords.y = static_cast<float>(Constants::ORIGIN_Y + (offset.y * Constants::SPRITE_OFFSET_Y));
}

void CardPos::setOffset(Utils::IVector2 offset)
{
    m_CardPosition.x = static_cast<float>(offset.x);
    m_CardPosition.y = static_cast<float>(offset.y);
}

Rectangle CardPos::getCardPosition() const
{
    return m_CardPosition;
}

Rectangle CardPos::getCardSourceCoordinates() const
{
    return m_CardSourceCoords;
}

void CardPos::moveX(int32_t dx)
{
    m_CardPosition.x += static_cast<float>(dx);
}

void CardPos::moveY(int32_t dy)
{
    m_CardPosition.y += static_cast<float>(dy);
}

int32_t CardPos::getX() const
{
    return static_cast<int32_t>(m_CardPosition.x);
}

int32_t CardPos::getY() const
{
    return static_cast<int32_t>(m_CardPosition.y);
}

int32_t CardPos::getWidth() const
{
    return static_cast<int32_t>(m_CardPosition.width);
}

int32_t CardPos::getHeight() const
{
    return static_cast<int32_t>(m_CardPosition.height);
}

void CardPos::printCardCoordinates() const
{
    std::cout << "Card (x0, y0, width, height): " << m_CardPosition.x << ", " << m_CardPosition.y << ", " 
              << m_CardPosition.width << ", " << m_CardPosition.height << std::endl;
}

} // namespace Solitaire