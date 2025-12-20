#include "Renderer.h"
#include "Game.h"

void Solitaire::Renderer::Initialize()
{
    m_Texture = LoadTexture("resources/sprites/spriteSheet.png");
    m_BackgroundColor = DeckBackgroundColor::Red;
    m_DeckBackgroundSource = 
    {
        static_cast<float>(Constants::ORIGIN_X + (static_cast<int>(m_BackgroundColor) * Constants::SPRITE_OFFSET_X)),
        static_cast<float>(Constants::ORIGIN_Y + (Constants::BACKGROUND_ROW * Constants::SPRITE_OFFSET_Y)), 
        static_cast<float>(Constants::SPRITE_WIDTH), 
        static_cast<float>(Constants::SPRITE_HEIGHT)
    };
}

void Solitaire::Renderer::RenderCard(PlayingCard& card)
{
    DrawTexturePro(m_Texture, card.GetCoordinates().GetCardSourceCoordinates(), card.GetCoordinates().GetCardPosition(), {0, 0}, 0.0F, WHITE);
}

void Solitaire::Renderer::RenderPlayingCards(PlayingCardVector& cards)
{
    for(size_t i = 0; i < cards.size(); ++i)
    {
        RenderCard(cards[i]);
    }
}

void Solitaire::Renderer::RenderDeck(Deck& deck)
{
    if(!deck.IsEmpty())
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
    
        if(deck.GetSize() < Constants::NUMBER_OF_CARDS_IN_DECK / 3)
        {
            DrawTexturePro(m_Texture, m_DeckBackgroundSource, deckBack, {0, 0}, 0.0F, WHITE);
        }
        else if(deck.GetSize() < (2 * Constants::NUMBER_OF_CARDS_IN_DECK) / 3)
        {
            DrawTexturePro(m_Texture, m_DeckBackgroundSource, deckBack, {0, 0}, 0.0F, WHITE);
            DrawTexturePro(m_Texture, m_DeckBackgroundSource, deckMiddle, {0, 0}, 0.0F, WHITE);
        }
        else
        {
            DrawTexturePro(m_Texture, m_DeckBackgroundSource, deckBack, {0, 0}, 0.0F, WHITE);
            DrawTexturePro(m_Texture, m_DeckBackgroundSource, deckMiddle, {0, 0}, 0.0F, WHITE);
            DrawTexturePro(m_Texture, m_DeckBackgroundSource, deckFront, {0, 0}, 0.0F, WHITE);
        }
    }
}

void Solitaire::Renderer::RenderLane(Lane& lane)
{
    for(size_t i = 0; i < lane.GetNumberOfHiddenCards(); ++i)
    {
        Rectangle hiddenCardPos = 
        { 
            static_cast<float>(lane.GetLaneOffset().x), 
            static_cast<float>(lane.GetLaneOffset().y + (i * Constants::HIDDEN_CARD_OFFSET_Y)), 
            static_cast<float>(Constants::RENDERED_SPRITE_WIDTH), 
            static_cast<float>(Constants::RENDERED_SPRITE_HEIGHT) 
        };

        DrawTexturePro(m_Texture, m_DeckBackgroundSource, hiddenCardPos, {0, 0}, 0.0F, WHITE);
    }

    RenderPlayingCards(lane.GetAllPlayingCards());
}

void Solitaire::Renderer::SetDeckBackgroundColor(DeckBackgroundColor color)
{
    m_BackgroundColor = color;
    m_DeckBackgroundSource.x = static_cast<float>(Constants::ORIGIN_X + (static_cast<int>(m_BackgroundColor) * Constants::SPRITE_OFFSET_X));
}
