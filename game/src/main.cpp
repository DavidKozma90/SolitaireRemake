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
    renderer.SetDeckBackgroundColor(backgroundColor);
    CardVector test;
    test.reserve(1);

    std::array<Lane, Constants::NUMBER_OF_LANES> lanes; 
  
    for(int i = 0; i < Constants::NUMBER_OF_LANES; ++i)
    {
        lanes[i] = Lane(i, i, 1);
        lanes[i].Fill(deck);
    }

    Lane* selectedLane = &lanes[0];

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(DARKGREEN);
    
        //backgroundColor = getBackgroundColorFromInput(GetKeyPressed());
        //renderer.SetDeckBackgroundColor(backgroundColor);

        Vector2 mousePos = GetMousePosition();
        //std::cout << mousePos.x << " " << mousePos.y << std::endl;

        
        switch(GetKeyPressed())
        {
        case KEY_ONE:
            selectedLane = &lanes[0];
            break;
        case KEY_TWO:
            selectedLane = &lanes[1];
            break;
        case KEY_THREE:
            selectedLane = &lanes[2];
            break;
        case KEY_FOUR:
            selectedLane = &lanes[3];
            break;
        case KEY_FIVE:
            selectedLane = &lanes[4];
            break;
        case KEY_SIX:
            selectedLane = &lanes[5];
            break;
        case KEY_SEVEN:
            selectedLane = &lanes[6];
            break;
        default:
            break;
        }

        std::cout << "Selected lane hidden cards: " << selectedLane->GetNumberOfHiddenCards() << " playing cards: " << selectedLane->GetNumberOfPlayingCards() << std::endl;

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

        if(IsKeyPressed(KEY_I))
        {
            CardTransfer::TransferPlayingCardsToCards(cardFromDeck, test, 1);
            selectedLane->InsertCards(test);
            test.clear();
        }
        else if(IsKeyPressed(KEY_R))
        {
            if(!(selectedLane->IsPlayingCardsEmpty()))
            {
                selectedLane->RemoveCards(1);
            }
        }
        else if(IsKeyPressed(KEY_H))
        {
            selectedLane->ConvertHiddenToPlaying();  
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