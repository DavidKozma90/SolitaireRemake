#pragma once
#include <raylib.h>


namespace Solitaire
{
    class Game
    {
    public:
        Game();
        ~Game();

        void Start();
        void Update();
        void Draw();
        void Run();
        void End();

    private:
        void Initialize();
        void LoadResources();
        void UnloadResources();

        bool m_IsRunning = true;
    };
}