#include <vector>
#include <array>
#include <iostream>
#include "raylib.h"
#include "Card.h"
#include "Constants.h"
#include "Renderer.h"
#include "PlayingCard.h"
#include "Utils.hpp"
#include "Game.h"
using namespace Solitaire;

Texture2D texture;

void placeCardAnywhere(PlayingCard& card, Vector2& offset)
{
    const Vector2 mousePos = GetMousePosition();
    static bool isCardGrabbed = false;

    if(IsMouseButtonDown(MOUSE_LEFT_BUTTON))
    {
        if((mousePos.x > card.GetCoordinates().GetX()) && (mousePos.x < card.GetCoordinates().GetX() + card.GetCoordinates().GetWidth()) &&
           (mousePos.y > card.GetCoordinates().GetY()) && (mousePos.y < card.GetCoordinates().GetY() + card.GetCoordinates().GetHeight()))
        {            
            isCardGrabbed = true;
        }
    }
    else
    {
        isCardGrabbed = false;
    }

    if(isCardGrabbed)
    {
        offset = {mousePos.x - (card.GetCoordinates().GetWidth() / 2), mousePos.y - (card.GetCoordinates().GetHeight() / 2)};
    }
}


void placeCardInsideTarget(PlayingCard& card, Vector2& offset, Rectangle& rectangle)
{
    const Vector2 mousePos = GetMousePosition();
    static bool isCardGrabbed = false;
    static Vector2 saveOriginal = {0,0};

    if(IsMouseButtonDown(MOUSE_LEFT_BUTTON))
    {
        if((mousePos.x >= card.GetCoordinates().GetX()) && (mousePos.x < (card.GetCoordinates().GetX() + card.GetCoordinates().GetWidth())) &&
           (mousePos.y >= card.GetCoordinates().GetY()) && (mousePos.y < (card.GetCoordinates().GetY() + card.GetCoordinates().GetHeight())))
        {            
            isCardGrabbed = true;
        }
    }

    if(IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
    {   
        if(CheckCollisionRecs(card.GetCoordinates().GetCardPosition(), rectangle))
        {
            offset = {rectangle.x, rectangle.y};
        }
        else
        {
            offset = {0, 0};
        }
        isCardGrabbed = false;
    }

    if(isCardGrabbed)
    {
        offset = {mousePos.x - (card.GetCoordinates().GetWidth() / 2), mousePos.y - (card.GetCoordinates().GetHeight() / 2)};
    }
}

static DeckBackgroundColor getBackgroundColorFromInput(int key)
{
    static DeckBackgroundColor color = DeckBackgroundColor::Red;

    switch(key)
    {
    case KEY_ONE:
        color = DeckBackgroundColor::Red; 
        break;
    case KEY_TWO:
        color = DeckBackgroundColor::Yellow;
        break;
    case KEY_THREE:
        color = DeckBackgroundColor::Pink;
        break;
    case KEY_FOUR:
        color = DeckBackgroundColor::Green;
        break;
    case KEY_FIVE:
        color = DeckBackgroundColor::Purple;
        break;
    case KEY_SIX:
        color = DeckBackgroundColor::Blue;
        break;
    case KEY_SEVEN:
        color = DeckBackgroundColor::Grey;
        break;
    default:
        break;
    }

    return color;
}

typedef std::array<Lane, Constants::MAX_NUMBER_OF_LANES> LaneArray;

static int LaneSelectorFromPosition(const LaneArray& lanes, int x, int y)
{
    int currentLaneIndex = Constants::INVALID_INDEX;

    for(int i = 0; i < Constants::MAX_NUMBER_OF_LANES; ++i)
    {
        int laneIndex = lanes[i].GetLaneIndexFromPosition(x, y);
        if(laneIndex != Constants::INVALID_INDEX)
        {
            currentLaneIndex = laneIndex;
            break;
        }
    }
    
    return currentLaneIndex;
}

int main()
{
    Game game;

    game.Run();
}
