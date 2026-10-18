#pragma once

#include <raylib.h>
#include <vector>
#include "PlayingCard.h"
#include "Deck.h"
#include "Utils.hpp"

namespace Solitaire
{
class Lane
{
public:
    DEFAULT_CTOR(Lane);
    Lane(int32_t laneIndex, size_t hidden, size_t playing);
    void fill(Deck& fromDeck);
    void set(int32_t laneIndex = 0, size_t hidden = 0, size_t playing = 0);

    void insertCards(const CardVector& cardsToInsert);
    CardVector removeCards(size_t howMany);
    
    size_t getNumberOfHiddenCards() const;
    size_t getNumberOfPlayingCards() const;
    Utils::IVector2 getLaneOffset() const;
    PlayingCardVector& getAllPlayingCards();
    const PlayingCardVector& getAllPlayingCards() const;
    void convertTopHiddenCardToPlayingCard();
    bool isLaneEmpty() const;
    bool hasNoPlayingCards() const;
    bool hasNoHiddenCards() const;
    bool hasPlayingCards() const;
    bool hasHiddenCards() const;

    int32_t getLaneIndex() const;
    int32_t getLaneIndexFromPosition(int32_t x, int32_t y) const;
    int32_t getPlayingCardIndexFromPosition(int32_t x, int32_t y) const;

    Rectangle getPlayingCardArea() const;
    Rectangle getMovedPlayingCardArea(int32_t cardIndex) const;

    void printInfo() const;
private:
    int32_t m_laneIndex{};
    CardVector m_hiddenCards{};
    PlayingCardVector m_playingCards{};
    Utils::IVector2 m_laneOffset{};

    void insertCardsToLane(const CardVector& cardsToInsert, int32_t elementOffset);
};

}