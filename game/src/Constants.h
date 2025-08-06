#pragma once

namespace Solitaire
{
    namespace Constants
    {
        // Window constants
        static inline constexpr int WINDOW_WIDTH = 1300;
        static inline constexpr int WINDOW_HEIGHT = 750;

        // Renderer constants
        static inline constexpr int ORIGIN_X = 2;
        static inline constexpr int ORIGIN_Y = 3;
        static inline constexpr int SPRITE_WIDTH = 57;
        static inline constexpr int SPRITE_HEIGHT = 79;
        static inline constexpr int RENDERED_SPRITE_WIDTH = SPRITE_WIDTH * 2;
        static inline constexpr int RENDERED_SPRITE_HEIGHT = SPRITE_HEIGHT * 2;
        static inline constexpr int SPRITE_OFFSET_X = 59;
        static inline constexpr int SPRITE_OFFSET_Y = 81;
        static inline constexpr int DECK_ORIGIN_X = 40;
        static inline constexpr int DECK_ORIGIN_Y = 40;
        static inline constexpr int DECK_DEPTH_OFFSET = 4;
        static inline constexpr int BACKGROUND_ROW = 4;

        // Game constants
        static inline constexpr int NUMBER_OF_CARDS_IN_DECK = 52;
        static inline constexpr int NUMBER_OF_LANES = 7;
    }
}