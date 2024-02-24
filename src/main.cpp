#include <raylib.h>

#include "game.hpp"

int main()
{
    Color grey = {29, 29, 29, 255};
    Color yellow = {243, 216, 63, 255};
    int offset = 50;
    int windowWidth = 750;
    int windowHeight = 700;

    InitWindow(windowWidth + offset, windowHeight + 2 * offset, "Invasores do Espaço - by Silvanei Martins");
    Font font = LoadFontEx("Font/monogram.ttf", 64, 0, 0);
    Texture2D spaceshipImage = LoadTexture("graphics/spaceship.png");
    SetTargetFPS(60);

    Game game;

    while (WindowShouldClose() == false)
    {
        game.HandleInput();
        game.Update();
        BeginDrawing();
        ClearBackground(grey);
        DrawRectangleRoundedLines({10, 10, 780, 780}, 0.18f, 20, 2, yellow);
        DrawTextEx(font, "Invasores do Espaco", {220, 30}, 35, 3, yellow);
        DrawLineEx({24, 730}, {775, 730}, 3, yellow);
        
        // Desenhe o texto do nível
        if (game.run) 
        {
            DrawTextEx(font, "Level 01", {600, 740}, 34, 2, yellow);
        } else 
        {
            DrawTextEx(font, "Gamer Over", {580, 740}, 34, 2, yellow);
        }

        // Desenhe a quantidade de vidas do jogador
        float x = 50.0;
        for (int i = 0; i < game.lives; ++i)
        {
            DrawTextureV(spaceshipImage, {x, 745}, yellow);
            x += 50;
        }

        game.Draw();
        EndDrawing();
    }

    CloseWindow();
}