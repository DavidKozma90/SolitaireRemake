#pragma once

#include <raylib.h>
#include <iostream>
#include "Constants.h"
#include "Utils.h"

namespace Solitaire
{
    class CardCoordinates 
    {
    public:
        CardCoordinates();
        ~CardCoordinates() = default;

        void SetCardSourceCoordinates(IVector2 offset);
        void SetCardDestinationCoordinates(IVector2 offset);

        Rectangle GetCardDestinationCoordinates() const;
        Rectangle GetCardSourceCoordinates() const;
        void SetX(int x);
        void SetY(int y);
        int GetX() const;
        int GetY() const;
        int GetWidth() const;
        int GetHeight() const;
        
        void PrintCardCoordinates() const;
    private:
        Rectangle m_CardDestinationCoords;
        Rectangle m_CardSourceCoords;
    };
}
