#include "Renderer.h"

void Solitaire::Renderer::Initialize()
{
    m_Texture = LoadTexture("resources/sprites/spriteSheet.png");
}

void Solitaire::Renderer::RenderCard(PlayingCard &card)
{
    DrawTexturePro(m_Texture, card.GetCoordinates().GetCardSourceCoordinates(), card.GetCoordinates().GetCardPosition(), {0, 0}, 0.0F, WHITE);
}

void Solitaire::Renderer::RenderDeck(Deck &deck)
{
    Rectangle deckBack = deck.deckPos.GetCardPosition();
    
    Rectangle deckMiddle = 
    { 
        deckBack.x + Constants::DECK_DEPTH_OFFSET, 
        deckBack.y + Constants::DECK_DEPTH_OFFSET, 
        deckBack.width, 
        deckBack.height 
    };

    Rectangle deckFront  = 
    { 
        deckBack.x + (Constants::DECK_DEPTH_OFFSET * 2), 
        deckBack.y + (Constants::DECK_DEPTH_OFFSET * 2), 
        deckBack.width, 
        deckBack.height 
    };

    deck.deckPos.SetCardSourceCoordinates({static_cast<int>(m_BackgroundColor), Constants::BACKGROUND_ROW});

    if(!deck.IsEmpty())
    {
        if(deck.GetSize() < Constants::NUMBER_OF_CARDS_IN_DECK / 3)
        {
            DrawTexturePro(m_Texture, deck.deckPos.GetCardSourceCoordinates(), deckBack, {0, 0}, 0.0F, WHITE);
        }
        else if(deck.GetSize() < (2 * Constants::NUMBER_OF_CARDS_IN_DECK) / 3)
        {
            DrawTexturePro(m_Texture, deck.deckPos.GetCardSourceCoordinates(), deckBack, {0, 0}, 0.0F, WHITE);
            DrawTexturePro(m_Texture, deck.deckPos.GetCardSourceCoordinates(), deckMiddle, {0, 0}, 0.0F, WHITE);
        }
        else
        {
            DrawTexturePro(m_Texture, deck.deckPos.GetCardSourceCoordinates(), deckBack, {0, 0}, 0.0F, WHITE);
            DrawTexturePro(m_Texture, deck.deckPos.GetCardSourceCoordinates(), deckMiddle, {0, 0}, 0.0F, WHITE);
            DrawTexturePro(m_Texture, deck.deckPos.GetCardSourceCoordinates(), deckFront, {0, 0}, 0.0F, WHITE);
        }
    }
}

void Solitaire::Renderer::SetDeckBackgroundColor(DeckBackgroundColor color, Deck &deck)
{
    m_BackgroundColor = color;
    deck.deckPos.SetCardSourceCoordinates({static_cast<int>(m_BackgroundColor), Constants::BACKGROUND_ROW});
}
