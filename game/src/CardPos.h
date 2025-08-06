#pragma once

#include <raylib.h>
#include <iostream>
#include "Constants.h"
#include "Utils.h"

namespace Solitaire
{
    class CardPos 
    {
    public:
        CardPos();
        ~CardPos() = default;

        void SetCardSourceCoordinates(IVector2 offset);
        void SetOffset(IVector2 offset);

        Rectangle GetCardPosition() const;
        Rectangle GetCardSourceCoordinates() const;
        void MoveX(int x);
        void MoveY(int y);
        int GetX() const;
        int GetY() const;
        int GetWidth() const;
        int GetHeight() const;
        
        void PrintCardCoordinates() const;
    private:
        Rectangle m_CardPosition;
        Rectangle m_CardSourceCoords;
    };
}
