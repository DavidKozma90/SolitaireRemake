#pragma once

#include <raylib.h>
#include <vector>
#include "Card.h"

namespace Solitaire
{
    class Lane
    {

    public:
        Lane() = default;
        ~Lane() = default;

        Lane(int laneNumber, Card& card);

        void addCard(const Card& card);
        void removeCard();
        void drawCardsOnLane(Texture2D& texture, Vector2 offset);
    private:
        int m_NumOfHiddenCards = 0;
        std::vector<Card> m_Cards;
    };
}