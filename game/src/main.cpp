#include <vector>
#include <iostream>
#include "raylib.h"
#include "Card.h"
#include "Constants.h"
#include "Renderer.h"
#include "PlayingCard.h"

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

int main()
{
    Renderer renderer;
    
    InitWindow(Constants::WINDOW_WIDTH, Constants::WINDOW_HEIGHT, "Solitaire Remake by David Kozma");
	SetTargetFPS(60);

    renderer.Initialize();


    const IVector2 offset = {(Constants::DECK_ORIGIN_X * 2) + Constants::RENDERED_SPRITE_WIDTH , Constants::DECK_ORIGIN_Y};

    std::vector<PlayingCard> cardFromDeck;

    Deck deck;
    renderer.SetDeckBackgroundColor(DeckBackgroundColor::Red, deck);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(DARKGREEN);

        //std::cout << GetMouseX() << " " << GetMouseY() << std::endl;

        const Vector2 mousePos = GetMousePosition();

        if(IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
        {
            if((mousePos.x >= deck.deckPos.GetX()) && (mousePos.x < (deck.deckPos.GetX() + deck.deckPos.GetWidth() + 8)) &&
               (mousePos.y >= deck.deckPos.GetY()) && (mousePos.y < (deck.deckPos.GetY() + deck.deckPos.GetHeight() + 8)))
            {
                if(!deck.IsEmpty())
                {       
                    cardFromDeck.push_back(CardFactory::CreatePlayingCard(deck.DrawCard(), offset));
                }
            }
        }

        if(!cardFromDeck.empty())
        {
            renderer.RenderCard(cardFromDeck.back());
        }

        renderer.RenderDeck(deck);


        EndDrawing();
    }

    CloseWindow();
}