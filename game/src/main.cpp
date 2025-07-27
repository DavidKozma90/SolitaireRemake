#include <vector>
#include <iostream>
#include "raylib.h"
#include "Card.h"
#include "Constants.h"
#include "Renderer.h"

using namespace Solitaire;

Texture2D texture;

void placeCardAnywhere(Card& card, Vector2& offset)
{
    const Vector2 mousePos = GetMousePosition();
    static bool isCardGrabbed = false;

    if(IsMouseButtonDown(MOUSE_LEFT_BUTTON))
    {
        if((mousePos.x > card.GetCoords().GetX()) && (mousePos.x < card.GetCoords().GetX() + card.GetCoords().GetWidth()) &&
           (mousePos.y > card.GetCoords().GetY()) && (mousePos.y < card.GetCoords().GetY() + card.GetCoords().GetHeight()))
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
        offset = {mousePos.x - (card.GetCoords().GetWidth() / 2), mousePos.y - (card.GetCoords().GetHeight() / 2)};
    }
}


void placeCardInsideTarget(Card& card, Vector2& offset, Rectangle& rectangle)
{
    const Vector2 mousePos = GetMousePosition();
    static bool isCardGrabbed = false;
    static Vector2 saveOriginal = {0,0};

    if(IsMouseButtonDown(MOUSE_LEFT_BUTTON))
    {
        if((mousePos.x >= card.GetCoords().GetX()) && (mousePos.x < (card.GetCoords().GetX() + card.GetCoords().GetWidth())) &&
           (mousePos.y >= card.GetCoords().GetY()) && (mousePos.y < (card.GetCoords().GetY() + card.GetCoords().GetHeight())))
        {            
            isCardGrabbed = true;
        }
    }

    if(IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
    {   
        if(CheckCollisionRecs(card.GetCoords().GetCardDestinationCoordinates(), rectangle))
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
        offset = {mousePos.x - (card.GetCoords().GetWidth() / 2), mousePos.y - (card.GetCoords().GetHeight() / 2)};
    }
}

int main()
{
    Renderer renderer;

    InitWindow(Constants::WINDOW_WIDTH, Constants::WINDOW_HEIGHT, "Raylib Example");
	SetTargetFPS(60);

    renderer.Initialize();

    Card card(Rank::Ace, Suit::Hearts);
    Vector2 offset = {0,0};
    const IVector2 ivectorOffset = ToIVector2(offset);
    Rectangle rectangleTarget = {(Constants::WINDOW_WIDTH / 2) - (Constants::RENDERED_SPRITE_WIDTH / 2), 
                                 (Constants::WINDOW_HEIGHT / 2) - (Constants::RENDERED_SPRITE_HEIGHT / 2), 
                                  Constants::RENDERED_SPRITE_WIDTH, 
                                  Constants::RENDERED_SPRITE_HEIGHT};

    while (!WindowShouldClose())
    {
        BeginDrawing();
		ClearBackground(DARKGREEN);

        DrawRectangleLines(rectangleTarget.x, rectangleTarget.y, rectangleTarget.width, rectangleTarget.height, WHITE);
                           
        //std::cout << GetMouseX() << " " << GetMouseY() << std::endl;

        //placeCardAnywhere(card, offset);
        card.GetCoords().SetCardDestinationCoordinates(ToIVector2(offset));
        placeCardInsideTarget(card, offset, rectangleTarget);
        
        renderer.RenderCard(card);

        //std::cout << "Offset: " << offset.x << ", " << offset.y << std::endl;

		EndDrawing();
    }
    CloseWindow();

    return 0;
}