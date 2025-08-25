#pragma once

namespace Solitaire
{
    namespace Constants
    {
        // Window constants
        static inline constexpr int WINDOW_WIDTH = 1094;
        static inline constexpr int WINDOW_HEIGHT = 850;

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
        static inline constexpr int LANE_ORIGIN_X = 40;
        static inline constexpr int LANE_ORIGIN_Y = 250;
        static inline constexpr int LANE_OFFSET_X = 150;
        static inline constexpr int LANE_OFFSET_Y = 30;
        static inline constexpr int HIDDEN_CARD_OFFSET_Y = 10;

        // Game constants
        static inline constexpr int NUMBER_OF_CARDS_IN_DECK = 52;
        static inline constexpr int INVALID_LANE_INDEX = -1;
        static inline constexpr int LANE_NUMBER_ZERO = 0;
        static inline constexpr int LANE_NUMBER_ONE = 1;
        static inline constexpr int LANE_NUMBER_TWO = 2;
        static inline constexpr int LANE_NUMBER_THREE = 3;
        static inline constexpr int LANE_NUMBER_FOUR = 4;
        static inline constexpr int LANE_NUMBER_FIVE = 5;
        static inline constexpr int LANE_NUMBER_SIX = 6;
        static inline constexpr int MAX_NUMBER_OF_LANES = 7;
    }
}