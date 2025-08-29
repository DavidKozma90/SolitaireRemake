#pragma once
#include <raylib.h>
#include <array>
#include "Lane.h"
#include "Constants.h"
#include "Deck.h"
#include "Renderer.h"

namespace Solitaire
{
    typedef std::array<Lane, Constants::MAX_NUMBER_OF_LANES> LaneArray;
    class Game
    {
    public:
        Game();
        ~Game();

        void OnInput();
        void OnUpdate();
        void OnRender();
        void Run();

    private:
        LaneArray m_CardLanes;
        Deck m_Deck;
        Renderer m_Renderer;
        PlayingCardVector m_CardFromDeck;
        CardVector m_Temp;
        DeckBackgroundColor m_BackgroundColor = DeckBackgroundColor::Red;
        Lane* m_SelectedLanePtr = nullptr;

        Vector2 m_CursorPosition = {0, 0};
        bool m_IsCursorPressed = false;
        bool m_IsAddingCardsButtonPressed = false;
        bool m_IsRemovingCardsButtonPressed = false;
        bool m_IsConvertingCardsButtonPressed = false;

        DeckBackgroundColor getBackgroundColorFromInput() const;
        int laneSelectorFromPosition(int x, int y) const;

        bool m_IsRunning = true;
    };
}