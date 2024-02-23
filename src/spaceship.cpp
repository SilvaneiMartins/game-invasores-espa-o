#include "spaceship.hpp"

// Construtor
Spaceship::Spaceship()
{
    image = LoadTexture("graphics/spaceship.png");
    position.x = (GetScreenWidth() / 2 - image.width) / 2;
    position.y = GetScreenHeight() - image.height - 20;
    lastFireTime = 0.0;
}

// Destrutor
Spaceship::~Spaceship()
{
    UnloadTexture(image);
}

// Desenhe a nave
void Spaceship::Draw()
{
    DrawTextureV(image, position, WHITE);
}

// Mova a nave para a esquerda
void Spaceship::MoveLeft()
{
    position.x -= 7;
    if (position.x <= 0) {
        position.x = 0;
    }
}

// Mova a nave para a direita
void Spaceship::MoveRight()
{
    position.x += 7;
    if (position.x >= GetScreenWidth() - image.width) {
        position.x = GetScreenWidth() - image.width;
    }
}

// Atire um laser
void Spaceship::FireLaser()
{
    if (GetTime() - lastFireTime  >= 0.35) {
        Laser laser = Laser({position.x + image.width / 2 - 2, position.y}, -6);
        lasers.push_back(laser);
        lastFireTime = GetTime();
    }
}

// Obtenha o retângulo da nave
Rectangle Spaceship::getRect()
{
    return {position.x, position.y, float(image.width), float(image.height)};
}