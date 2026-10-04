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
#include "LogTrace.h"
using namespace Solitaire;

Texture2D texture;

void placeCardAnywhere(PlayingCard& card, Vector2& offset)
{
    const Vector2 mousePos = GetMousePosition();
    static bool isCardGrabbed = false;
    static bool isCursorSet = false;
    static int xDelta = 0;
    static int yDelta = 0;

    std::cout << "Card: " << card.getCardPosition().getX() << ", " << card.getCardPosition().getY() << " Mouse: " << mousePos.x << ", " << mousePos.y << std::endl;

    if(IsMouseButtonDown(MOUSE_LEFT_BUTTON))
    {
        if((mousePos.x > card.getCardPosition().getX()) && (mousePos.x < card.getCardPosition().getX() + card.getCardPosition().getWidth()) &&
           (mousePos.y > card.getCardPosition().getY()) && (mousePos.y < card.getCardPosition().getY() + card.getCardPosition().getHeight()))
        {            
            isCardGrabbed = true;
        }
    }
    else
    {
        isCardGrabbed = false;
        isCursorSet = false;
        xDelta = 0;
        yDelta = 0;
    }

    if(isCardGrabbed)
    {
        //offset = {mousePos.x - (card.getCardPosition().getWidth() / 2), mousePos.y - (card.getCardPosition().getHeight() / 2)};
        if(!isCursorSet)
        {
            xDelta = static_cast<int>(mousePos.x) - card.getCardPosition().getX();
            yDelta = static_cast<int>(mousePos.y) - card.getCardPosition().getY();
            isCursorSet = true;
        }

        offset = {mousePos.x - xDelta, mousePos.y - yDelta};
        card.getCardPosition().setOffset(Utils::ToIVector2(offset));
    }
}


void placeCardInsideTarget(PlayingCard& card, Vector2& offset, Rectangle& rectangle)
{
    const Vector2 mousePos = GetMousePosition();
    static bool isCardGrabbed = false;
    static Vector2 saveOriginal = {0,0};

    if(IsMouseButtonDown(MOUSE_LEFT_BUTTON))
    {
        if((mousePos.x >= card.getCardPosition().getX()) && (mousePos.x < (card.getCardPosition().getX() + card.getCardPosition().getWidth())) &&
           (mousePos.y >= card.getCardPosition().getY()) && (mousePos.y < (card.getCardPosition().getY() + card.getCardPosition().getHeight())))
        {            
            isCardGrabbed = true;
        }
    }

    if(IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
    {   
        if(CheckCollisionRecs(card.getCardPosition().getCardPosition(), rectangle))
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
        offset = {mousePos.x - (card.getCardPosition().getWidth() / 2), mousePos.y - (card.getCardPosition().getHeight() / 2)};
    }
}

typedef std::array<Lane, Constants::MAX_NUMBER_OF_LANES> LaneArray;

static int LaneSelectorFromPosition(const LaneArray& lanes, int x, int y)
{
    int currentLaneIndex = Constants::INVALID_INDEX;

    for(int i = 0; i < Constants::MAX_NUMBER_OF_LANES; ++i)
    {
        int laneIndex = lanes[i].getLaneIndexFromPosition(x, y);
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

    LOG_INFO("GAME: Starting Main Game Loop...");
    
    game.Run();
}
