#pragma once

#include <raylib.h>
#include <iostream>
#include "Constants.h"


namespace Solitaire
{
    enum class Suit { Hearts, Diamonds, Clubs, Spades };
    enum class Rank { Ace = 1, Two, Three, Four, Five, Six, Seven, Eight, Nine, Ten, Jack = 11, Queen = 12, King = 13 };

    class Card
    {
    public:
        Card() = delete; // TODO: for now...
        ~Card() = default;
        Card(Rank rank, Suit suit);
        Card(Rank rank, Suit suit, Vector2 offset);
        Card(Rank rank, Suit suit, Texture2D& texture, Vector2 offset);

        Rank GetRank() const;
        Suit GetSuit() const;

        void Render(Texture2D& texture, Vector2 offset);
        Rectangle GetCoords();
        void PrintCardCoordinates() const;
        void SetCardCoordX(int x);
        void SetCardCoordY(int y);
        void SetCoords(Vector2 offset);

    private:
        Rank m_Rank = Rank::Ace;
        Suit m_Suit = Suit::Hearts;
        Rectangle m_DestinationRectangle = { 0, 0, Constants::RENDERED_SPRITE_WIDTH, Constants::RENDERED_SPRITE_HEIGHT };
    };
}