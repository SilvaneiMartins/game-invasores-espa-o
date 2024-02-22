#include <raylib.h>
#include "ball.h"

int main()
{
    Color darkGreen = Color{20, 160, 133, 255};

    const int screenWidth = 800;
    const int screenHeight = 600;

    Ball ball = Ball();

    InitWindow(screenWidth, screenHeight, "Invasores do Spaço - My Silvanei Martins");
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(darkGreen);
        ball.Update();
        ball.Draw();
        EndDrawing();
    }

    CloseWindow();
    return 0;
}