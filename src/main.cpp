#include <raylib.h>
#include <string>

#include "game.hpp"

std::string FormatWidthLeadingZeros(int number, int width)
{
    std::string numberText = std::to_string(number);
    int leadingZeros = width - numberText.length();
    return numberText = std::string(leadingZeros, '0') + numberText;
}

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
        DrawTextEx(font, "Invasores do Espaco", {230, 20}, 30, 3, yellow);
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

        // Desenhe a pontuação do jogador
        DrawTextEx(font, "Pontos", {50, 20}, 20, 2, yellow);
        std::string scoreText = FormatWidthLeadingZeros(game.score, 5);
        DrawTextEx(font, scoreText.c_str(), {50, 40}, 25, 2, yellow);

        game.Draw();
        EndDrawing();
    }

    CloseWindow();
}