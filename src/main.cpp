#include <raylib.h>

#include "game.hpp"

int main()
{
    Color grey = {29, 29, 29, 255};
    int windowWidth = 750;
    int windowHeight = 700;

    InitWindow(windowWidth, windowHeight, "Invasores do Espaço - by Silvanei Martins");
    SetTargetFPS(60);

    Game game;

    while (WindowShouldClose() == false)
    {
        game.HandleInput();

        BeginDrawing();
        ClearBackground(grey);
        DrawText("Invasores do Espaço", 250, 10, 20, WHITE);
        game.Draw();

        EndDrawing();
    }

    CloseWindow();
}