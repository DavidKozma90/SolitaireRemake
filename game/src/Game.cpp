#include "Game.h"

Solitaire::Game::Game()
{
    InitWindow(Constants::WINDOW_WIDTH, Constants::WINDOW_HEIGHT, "Solitaire Remake by David Kozma");
	SetTargetFPS(60);

    m_Renderer.Initialize();
    m_Deck.ShuffleDeck();
    m_CardFromDeck.clear();
    m_Temp.clear();
    m_Temp.reserve(1);
    m_SelectedCards.clear();

    for(int i = 0; i < Constants::MAX_NUMBER_OF_LANES; ++i)
    {
        m_CardLanes[i] = Lane(i, i, 1);
        m_CardLanes[i].Fill(m_Deck);
    }

    m_SelectedLanePtr = &m_CardLanes[Constants::LANE_NUMBER_ZERO];
}

Solitaire::Game::~Game()
{
    CloseWindow();
}

void Solitaire::Game::OnInput()
{
    int pressedKey = GetKeyPressed();

    m_CursorPosition = GetMousePosition();
    m_IsCursorPressed = IsMouseButtonReleased(MOUSE_LEFT_BUTTON);
    m_IsCursorDown = IsMouseButtonDown(MOUSE_LEFT_BUTTON);
    m_IsCursorUp = IsMouseButtonUp(MOUSE_LEFT_BUTTON);
    m_IsAddingCardsButtonPressed = IsKeyPressed(KEY_I);
    m_IsRemovingCardsButtonPressed = IsKeyPressed(KEY_R);
    m_IsConvertingCardsButtonPressed = IsKeyPressed(KEY_H);
    m_BackgroundColor = getBackgroundColorFromInput(pressedKey);
}

void Solitaire::Game::OnUpdate()
{
    const Utils::IVector2 offset = {(Constants::DECK_ORIGIN_X + Constants::LANE_OFFSET_X), Constants::DECK_ORIGIN_Y};
    int index = laneSelectorFromPosition(m_CursorPosition.x, m_CursorPosition.y);

    if((index != Constants::INVALID_INDEX))
    {
        m_SelectedLanePtr = &m_CardLanes[index];
    }

    //std::cout << "Lane index: " << m_SelectedLanePtr->GetLaneIndexFromPosition(m_CursorPosition.x, m_CursorPosition.y) << " Card index: " << m_SelectedLanePtr->GetPlayingCardIndexFromPosition(m_CursorPosition.x, m_CursorPosition.y) <<std::endl;

    if(m_IsCursorDown)
    {
        selectCardsFromLane();
    }

    if(m_IsCursorPressed)
    {
        if((m_CursorPosition.x >= m_Deck.deckPos.GetX()) && (m_CursorPosition.x < (m_Deck.deckPos.GetX() + m_Deck.deckPos.GetWidth() + (Constants::DECK_DEPTH_OFFSET * 2))) &&
           (m_CursorPosition.y >= m_Deck.deckPos.GetY()) && (m_CursorPosition.y < (m_Deck.deckPos.GetY() + m_Deck.deckPos.GetHeight() + (Constants::DECK_DEPTH_OFFSET * 2))))
        {
            if(!m_Deck.IsEmpty())
            {       
                m_CardFromDeck.push_back(CardFactory::CreatePlayingCard(m_Deck.DrawCard(), offset));
            }
            else
            {
                CardTransfer::TransformPlayingCardsToCards(m_CardFromDeck, m_Deck.GetCards(), static_cast<int>(m_CardFromDeck.size()));
            }
        }
    }

    if(m_IsAddingCardsButtonPressed)
    {
        CardTransfer::TransformPlayingCardsToCards(m_CardFromDeck, m_Temp, 1);
        m_SelectedLanePtr->InsertCards(m_Temp);
        m_Temp.clear();
    }
    else if(m_IsRemovingCardsButtonPressed)
    {
        if(!(m_SelectedLanePtr->IsPlayingCardsEmpty()))
        {
            m_SelectedLanePtr->RemoveCards(1);
        }
    }
    else if(m_IsConvertingCardsButtonPressed)
    {
        m_SelectedLanePtr->ConvertHiddenToPlaying();  
    }
}

void Solitaire::Game::OnRender()
{
    ClearBackground(DARKGREEN);

    m_Renderer.SetDeckBackgroundColor(m_BackgroundColor);
    m_Renderer.RenderDeck(m_Deck);

    if(!m_CardFromDeck.empty())
    {
        m_Renderer.RenderCard(m_CardFromDeck.back());
    }

    for(int i = 0; i < Constants::MAX_NUMBER_OF_LANES; ++i)
    {
        m_Renderer.RenderLane(m_CardLanes[i]);
    }
}

void Solitaire::Game::Run()
{
    while(m_IsRunning)
    {
        BeginDrawing();

        OnInput();
        OnUpdate();
        OnRender();

        EndDrawing();
        m_IsRunning = !WindowShouldClose();
    }

}

Solitaire::DeckBackgroundColor Solitaire::Game::getBackgroundColorFromInput(int pressedKey) const
{
    static DeckBackgroundColor color = DeckBackgroundColor::Red;

    switch(static_cast<KeyboardKey>(pressedKey))
    {
    case KEY_ONE:
        color = DeckBackgroundColor::Red; 
        break;
    case KEY_TWO:
        color = DeckBackgroundColor::Yellow;
        break;
    case KEY_THREE:
        color = DeckBackgroundColor::Pink;
        break;
    case KEY_FOUR:
        color = DeckBackgroundColor::Green;
        break;
    case KEY_FIVE:
        color = DeckBackgroundColor::Purple;
        break;
    case KEY_SIX:
        color = DeckBackgroundColor::Blue;
        break;
    case KEY_SEVEN:
        color = DeckBackgroundColor::Grey;
        break;
    default:
        break;
    }

    return color;
}

int Solitaire::Game::laneSelectorFromPosition(int x, int y) const
{
    int currentLaneIndex = Constants::INVALID_INDEX;

    for(int i = 0; i < Constants::MAX_NUMBER_OF_LANES; ++i)
    {
        int laneIndex = m_CardLanes[i].GetLaneIndexFromPosition(x, y);
        if(laneIndex != Constants::INVALID_INDEX)
        {
            currentLaneIndex = laneIndex;
            break;
        }
    }
    
    return currentLaneIndex;
}

void Solitaire::Game::selectCardsFromLane()
{
    int laneIndex = 0;
    int cardIndex = 0;
    static bool wasSelected = false;

    laneIndex = laneSelectorFromPosition(m_CursorPosition.x, m_CursorPosition.y);
    
    if(laneIndex != Constants::INVALID_INDEX)
    {
        m_SelectedLanePtr = &m_CardLanes[laneIndex];
    }
    
    cardIndex = m_SelectedLanePtr->GetPlayingCardIndexFromPosition(m_CursorPosition.x, m_CursorPosition.y);
    
    if(cardIndex != Constants::INVALID_INDEX)
    {
        PlayingCardVector& playingCards = m_SelectedLanePtr->GetAllPlayingCards();
        m_SelectedCards.clear();
        CardTransfer::TransferElements<PlayingCard>(playingCards, m_SelectedCards, static_cast<int>(playingCards.size()) - cardIndex);
        wasSelected = true;
    }

    if(wasSelected)
    {
        for(size_t i = 0; i < m_SelectedCards.size(); ++i)
        {
            int xDelta = static_cast<int>(m_CursorPosition.x) - m_SelectedCards[i].GetCoordinates().GetX();
            int yDelta = static_cast<int>(m_CursorPosition.y) - m_SelectedCards[i].GetCoordinates().GetY();
            int newX = static_cast<int>(m_CursorPosition.x) - xDelta;
            int newY = static_cast<int>(m_CursorPosition.y) - yDelta + (i * Constants::LANE_OFFSET_Y);
            m_SelectedCards[i].GetCoordinates().SetOffset({newX, newY});

            m_SelectedCards[i].GetCoordinates().MoveX(xDelta);
            m_SelectedCards[i].GetCoordinates().MoveY(yDelta);
        }
    }
}
