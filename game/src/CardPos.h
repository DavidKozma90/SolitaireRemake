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
    ~CardPos() = default;

    void setCardSourceCoordinates(Utils::IVector2 offset);
    void setOffset(Utils::IVector2 offset);

    Rectangle getCardPosition() const;
    Rectangle getCardSourceCoordinates() const;
    void moveX(int x);
    void moveY(int y);
    int getX() const;
    int getY() const;
    int getWidth() const;
    int getHeight() const;
    
    void printCardCoordinates() const;
private:
    Rectangle m_CardPosition;
    Rectangle m_CardSourceCoords;
};

}
