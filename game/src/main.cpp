#include "raylib.h"
#include <iostream>
#include "Card.h"
#include "Constants.h"
#include <vector>

using namespace Solitaire;

Texture2D texture;

void placeCardAnywhere(Card& card, Vector2& offset)
{
    const Vector2 mousePos = GetMousePosition();
    static bool isCardGrabbed = false;

    if(IsMouseButtonDown(MOUSE_LEFT_BUTTON))
    {
        if((mousePos.x > card.GetCoords().x) && (mousePos.x < card.GetCoords().x + card.GetCoords().width) &&
           (mousePos.y > card.GetCoords().y) && (mousePos.y < card.GetCoords().y + card.GetCoords().height))
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
        offset = {mousePos.x - (card.GetCoords().width / 2), mousePos.y - (card.GetCoords().height / 2)};
    }
}


void placeCardInsideTarget(Card& card, Vector2& offset, Rectangle& rectangle)
{
    const Vector2 mousePos = GetMousePosition();
    static bool isCardGrabbed = false;
    static Vector2 saveOriginal = {0,0};

    if(IsMouseButtonDown(MOUSE_LEFT_BUTTON))
    {
        if((mousePos.x >= card.GetCoords().x) && (mousePos.x < (card.GetCoords().x + card.GetCoords().width)) &&
           (mousePos.y >= card.GetCoords().y) && (mousePos.y < (card.GetCoords().y + card.GetCoords().height)))
        {            
            isCardGrabbed = true;
        }
    }

    if(IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
    {   
        if(CheckCollisionRecs(card.GetCoords(), rectangle))
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
        offset = {mousePos.x - (card.GetCoords().width / 2), mousePos.y - (card.GetCoords().height / 2)};
    }
}

int main()
{
    InitWindow(Constants::WINDOW_WIDTH, Constants::WINDOW_HEIGHT, "Raylib Example");
	SetTargetFPS(60);

    texture = LoadTexture("resources/sprites/spriteSheet.png");

    Card card(Rank::Ace, Suit::Hearts);
    Vector2 offset = {0,0};
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

        card.Render(texture, offset);
        //placeCardAnywhere(card, offset);
        card.SetCoords(offset);
        placeCardInsideTarget(card, offset, rectangleTarget);


        //std::cout << "Offset: " << offset.x << ", " << offset.y << std::endl;

		EndDrawing();
    }
    CloseWindow();

    return 0;
}