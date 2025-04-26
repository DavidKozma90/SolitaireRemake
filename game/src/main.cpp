#include "raylib.h"
#include <iostream>
#include "Card.h"

using namespace Solitaire;

const int x0 = 2;
const int y0 = 3;
const float spriteWidth = 57.0f;
const float spriteHeight = 79.0f;
const int spriteOffsetX = 59;
const int spriteOffsetY = 81;

Texture2D texture;

void testDraw()
{
    int offsetX = 0;
    int offsetY = 0;

    if(IsKeyPressed(KEY_RIGHT))
    {
        if(offsetX < 12)
        {
            offsetX++;
        }   
    }
    else if(IsKeyPressed(KEY_LEFT))
    {
        if(offsetX > 0)
        {
            offsetX--;
        }
    }
    else if(IsKeyPressed(KEY_UP))
    {
        if(offsetY > 0)
        {
            offsetY--;
        }
    }
    else if(IsKeyPressed(KEY_DOWN))
    {
        if(offsetY < 4)
        {
            offsetY++;
        }
    }

    Rectangle source = {x0 + (offsetX * spriteOffsetX), y0 + (offsetY * spriteOffsetY), spriteWidth, spriteHeight};
    Rectangle dest = {x0 + (offsetX * spriteOffsetX), y0 + (offsetY * spriteOffsetY), spriteWidth, spriteHeight};

    DrawTexturePro(texture, source, dest, {0, 0}, 0.0f, WHITE);
}

int main()
{
    Card c1(Rank::Ace, Suit::Hearts);
    Card c2(Rank::Two, Suit::Diamonds);
    Card c3(Rank::Three, Suit::Clubs);
    Card c4(Rank::Four, Suit::Spades);
    Card c5;

    InitWindow(800, 600, "Raylib Example");
	SetTargetFPS(60);

    texture = LoadTexture("resources/sprites/spriteSheet.png");
    while (!WindowShouldClose())
    {
        BeginDrawing();
		ClearBackground(DARKGREEN);

        std::cout << GetMouseX() << " " << GetMouseY() << std::endl;

        int cardOffsetX = 0;
    
        c1.DrawCard(texture, (cardOffsetX * Constants::SPRITE_OFFSET_X), 0);
        cardOffsetX++;
        c2.DrawCard(texture, (cardOffsetX * Constants::SPRITE_OFFSET_X), 0);
        cardOffsetX++;
        c3.DrawCard(texture, (cardOffsetX * Constants::SPRITE_OFFSET_X), 0);
        cardOffsetX++;
        c4.DrawCard(texture, (cardOffsetX * Constants::SPRITE_OFFSET_X), 0);
        cardOffsetX++;
        c5.DrawCard(texture, (cardOffsetX * Constants::SPRITE_OFFSET_X), 0);
      

		EndDrawing();
    }
    CloseWindow();

    return 0;
}