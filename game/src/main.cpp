#include "raylib.h"

int main()
{
    InitWindow(800, 600, "Raylib Example");
	SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        BeginDrawing();
		ClearBackground(RAYWHITE);

		DrawText("Hello Raylib!", 10, 10, 20, BLACK);

		EndDrawing();
    }
    CloseWindow();

    return 0;
}