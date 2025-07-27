#pragma once

#include <raylib.h>
#include "Card.h"

namespace Solitaire
{
    class Renderer
    {
    public:
        Renderer() = default;
        ~Renderer() = default;

        void Initialize();
        void RenderCard(Card& card);
    private:
        Texture2D m_Texture;
    };
}
