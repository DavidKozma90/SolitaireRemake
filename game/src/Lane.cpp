#include "Lane.h"

Solitaire::Lane::Lane(int laneNumber, Card& card)
{
    m_NumOfHiddenCards = laneNumber;
    m_Cards.push_back(card);
}

void Solitaire::Lane::addCard(const Card& card) 
{ 
    m_Cards.push_back(card); 
}

void Solitaire::Lane::removeCard() 
{ 
    if (!m_Cards.empty())
    {
        m_Cards.pop_back(); 
    }
}

void Solitaire::Lane::drawCardsOnLane(Texture2D &texture, Vector2 offset)
{
}
