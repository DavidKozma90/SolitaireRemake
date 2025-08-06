#pragma once

#include <raylib.h>
#include "PlayingCard.h"
#include "Deck.h"

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
        void SetDeckBackgroundColor(DeckBackgroundColor color, Deck &deck);
    private:
        Texture2D m_Texture;
        DeckBackgroundColor m_BackgroundColor = DeckBackgroundColor::Red;
    };
}
