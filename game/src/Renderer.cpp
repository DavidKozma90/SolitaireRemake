#include "Renderer.h"

void Solitaire::Renderer::Initialize()
{
    m_Texture = LoadTexture("resources/sprites/spriteSheet.png");
}

void Solitaire::Renderer::RenderCard(Card &card)
{
    DrawTexturePro(m_Texture, card.GetCoords().GetCardSourceCoordinates(), card.GetCoords().GetCardDestinationCoordinates(), {0, 0}, 0.0f, WHITE);
}
