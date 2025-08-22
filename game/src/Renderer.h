#pragma once

#include <raylib.h>
#include "PlayingCard.h"
#include "Deck.h"
#include "Lane.h"

namespace Solitaire
{
    enum class DeckBackgroundColor { Red, Yellow, Pink, Green, Purple, Blue, Grey };
    class Renderer
    {
    public:
        Renderer() = default;
        ~Renderer() = default;

        void Initialize();
        void RenderCard(PlayingCard& card);
        void RenderDeck(Deck& deck);
        void RenderLane(Lane& lane);
        void SetDeckBackgroundColor(DeckBackgroundColor color);
    private:
        Texture2D m_Texture;
        DeckBackgroundColor m_BackgroundColor;
        Rectangle m_DeckBackgroundSource;
    };
}
