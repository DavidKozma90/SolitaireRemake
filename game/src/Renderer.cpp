#include "Renderer.h"
#include "Game.h"
#include <array>

namespace Solitaire
{

void Renderer::init()
{
    InitWindow(Constants::WINDOW_WIDTH, Constants::WINDOW_HEIGHT, "Solitaire Remake by David Kozma");
    SetTargetFPS(60);
    
    m_texture = LoadTexture("resources/sprites/spriteSheet.png");
    m_backgroundColor = DeckBackgroundColor::Red;
    m_deckBackgroundSource = 
    {
        static_cast<float>(Constants::ORIGIN_X + (static_cast<int>(m_backgroundColor) * Constants::SPRITE_OFFSET_X)),
        static_cast<float>(Constants::ORIGIN_Y + (Constants::BACKGROUND_ROW * Constants::SPRITE_OFFSET_Y)), 
        static_cast<float>(Constants::SPRITE_WIDTH), 
        static_cast<float>(Constants::SPRITE_HEIGHT)
    };
}

void Renderer::renderCard(const PlayingCard& card)
{
    DrawTexturePro(m_texture, card.getCardPosition().getCardSourceCoordinates(), card.getCardPosition().getCardPosition(), {0, 0}, 0.0F, WHITE);
}

void Renderer::renderPlayingCards(const PlayingCardVector& cards)
{
    for(size_t i = 0; i < cards.size(); ++i)
    {
        renderCard(cards[i]);
    }
}

void Renderer::renderDeck(const Deck& deck)
{
    if(deck.isEmpty() == false)
    {
        Rectangle deckBack = deck.deckPos.getCardPosition();
    
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
    
        if(deck.getSize() < Constants::NUMBER_OF_CARDS_IN_DECK / 3)
        {
            DrawTexturePro(m_texture, m_deckBackgroundSource, deckBack, {0, 0}, 0.0F, WHITE);
        }
        else if(deck.getSize() < (2 * Constants::NUMBER_OF_CARDS_IN_DECK) / 3)
        {
            DrawTexturePro(m_texture, m_deckBackgroundSource, deckBack, {0, 0}, 0.0F, WHITE);
            DrawTexturePro(m_texture, m_deckBackgroundSource, deckMiddle, {0, 0}, 0.0F, WHITE);
        }
        else
        {
            DrawTexturePro(m_texture, m_deckBackgroundSource, deckBack, {0, 0}, 0.0F, WHITE);
            DrawTexturePro(m_texture, m_deckBackgroundSource, deckMiddle, {0, 0}, 0.0F, WHITE);
            DrawTexturePro(m_texture, m_deckBackgroundSource, deckFront, {0, 0}, 0.0F, WHITE);
        }
    }
}

void Renderer::renderLane(const Lane& lane)
{
    for(size_t i = 0; i < lane.getNumberOfHiddenCards(); ++i)
    {
        Rectangle hiddenCardPos = 
        { 
            static_cast<float>(lane.getLaneOffset().x), 
            static_cast<float>(lane.getLaneOffset().y + (i * Constants::HIDDEN_CARD_OFFSET_Y)), 
            static_cast<float>(Constants::RENDERED_SPRITE_WIDTH), 
            static_cast<float>(Constants::RENDERED_SPRITE_HEIGHT) 
        };

        DrawTexturePro(m_texture, m_deckBackgroundSource, hiddenCardPos, {0, 0}, 0.0F, WHITE);
    }

    renderPlayingCards(lane.getAllPlayingCards());
}

void Renderer::setDeckBackgroundColor(DeckBackgroundColor color)
{
    m_backgroundColor = color;
    m_deckBackgroundSource.x = static_cast<float>(Constants::ORIGIN_X + (static_cast<int32_t>(m_backgroundColor) * Constants::SPRITE_OFFSET_X));
}

} // namespace Solitaire