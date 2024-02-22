#include <raylib.h>
# include "spaceship.hpp"

int main()
{
    Color grey = {29, 29, 29, 255};
    int windowWidth = 750;
    int windowHeight = 700;

    InitWindow(windowWidth, windowHeight, "Invasores do Espaço - by Silvanei Martins");
    SetTargetFPS(60);

    Spaceship spaceship;

    while (WindowShouldClose() == false)
    {
        BeginDrawing();
        ClearBackground(grey);
        DrawText("Invasores do Espaço", 250, 10, 20, WHITE);
        spaceship.Draw();

        EndDrawing();
    }

    CloseWindow();
}