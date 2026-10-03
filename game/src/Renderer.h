#pragma once

#include <raylib.h>
#include "PlayingCard.h"
#include "Deck.h"
#include "Lane.h"
#include "Utils.hpp"

namespace Solitaire
{

enum class DeckBackgroundColor { Red, Yellow, Pink, Green, Purple, Blue, Grey };
class Renderer
{
public:
    DEFAULT_CTOR(Renderer);

    COPY_DISABLED(Renderer);
    
    void init();
    void renderCard(const PlayingCard& card);
    void renderPlayingCards(const PlayingCardVector& cards);
    void renderDeck(const Deck& deck);
    void renderLane(const Lane& lane);
    void setDeckBackgroundColor(DeckBackgroundColor color);
private:
    Texture2D m_texture;
    DeckBackgroundColor m_backgroundColor;
    Rectangle m_deckBackgroundSource;
};

}
