#include <vector>
#include <array>
#include <iostream>
#include "raylib.h"
#include "Card.h"
#include "Constants.h"
#include "Renderer.h"
#include "PlayingCard.h"
#include "Utils.hpp"

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

static void setBackgroundColorWithInput(DeckBackgroundColor& color)
{
    if(IsKeyPressed(KEY_ONE))
    {
        color = DeckBackgroundColor::Red;
    }
    else if(IsKeyPressed(KEY_TWO))
    {
        color = DeckBackgroundColor::Yellow;
    }
    else if(IsKeyPressed(KEY_THREE))
    {
        color = DeckBackgroundColor::Pink;
    }
    else if(IsKeyPressed(KEY_FOUR))
    {
        color = DeckBackgroundColor::Green;
    }
    else if(IsKeyPressed(KEY_FIVE))
    {
        color = DeckBackgroundColor::Purple;
    }
    else if(IsKeyPressed(KEY_SIX))
    {
        color = DeckBackgroundColor::Blue;
    }
    else if(IsKeyPressed(KEY_SEVEN))
    {
        color = DeckBackgroundColor::Grey;
    }
}

int main()
{
    Renderer renderer;
    
    InitWindow(Constants::WINDOW_WIDTH, Constants::WINDOW_HEIGHT, "Solitaire Remake by David Kozma");
	SetTargetFPS(60);

    renderer.Initialize();


    const Utils::IVector2 offset = {(Constants::DECK_ORIGIN_X + Constants::LANE_OFFSET_X), Constants::DECK_ORIGIN_Y};

    PlayingCardVector cardFromDeck;
    Deck deck;
    DeckBackgroundColor backgroundColor = DeckBackgroundColor::Red;

    std::array<Lane, Constants::NUMBER_OF_LANES> lanes = 
    {
        Lane(0, 0, 1),
        Lane(1, 1, 1),
        Lane(2, 2, 1),
        Lane(3, 3, 1),
        Lane(4, 4, 1),
        Lane(5, 5, 1),
        Lane(6, 6, 1)
    };

    for(int i = 0; i < Constants::NUMBER_OF_LANES; ++i)
    {
        lanes[i].Fill(deck);
    }

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(DARKGREEN);
        setBackgroundColorWithInput(backgroundColor);
        renderer.SetDeckBackgroundColor(backgroundColor);

        Vector2 mousePos = GetMousePosition();
        std::cout << mousePos.x << " " << mousePos.y << std::endl;

        if(IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
        {
            if((mousePos.x >= deck.deckPos.GetX()) && (mousePos.x < (deck.deckPos.GetX() + deck.deckPos.GetWidth() + (Constants::DECK_DEPTH_OFFSET * 2))) &&
               (mousePos.y >= deck.deckPos.GetY()) && (mousePos.y < (deck.deckPos.GetY() + deck.deckPos.GetHeight() + (Constants::DECK_DEPTH_OFFSET * 2))))
            {
                if(!deck.IsEmpty())
                {       
                    cardFromDeck.push_back(CardFactory::CreatePlayingCard(deck.DrawCard(), offset));
                }
                else
                {
                    CardTransfer::TransferPlayingCardsToCards(cardFromDeck, deck.GetCards(), static_cast<int>(cardFromDeck.size()));
                }
            }
        }

        if(!cardFromDeck.empty())
        {
            renderer.RenderCard(cardFromDeck.back());
        }

        renderer.RenderDeck(deck);
        
        for(int i = 0; i < Constants::NUMBER_OF_LANES; ++i)
        {
            renderer.RenderLane(lanes[i]);
        }

        EndDrawing();
    }

    CloseWindow();
}