#pragma once

#include <raylib.h>
#include <iostream>
#include <cstdint>
#include "Constants.h"
#include "Utils.hpp"

namespace Solitaire
{
class CardPos 
{
public:
    CardPos();

    void setCardSourceCoordinates(Utils::IVector2 offset);
    void setOffset(Utils::IVector2 offset);

    Rectangle getCardPosition() const;
    Rectangle getCardSourceCoordinates() const;
    void moveX(int32_t x);
    void moveY(int32_t y);
    int32_t getX() const;
    int32_t getY() const;
    int32_t getWidth() const;
    int32_t getHeight() const;
    
    void printCardCoordinates() const;
private:
    Rectangle m_CardPosition;
    Rectangle m_CardSourceCoords;
};

} // namespace Solitaire
