#include "spaceship.hpp"

// Construtor
Spaceship::Spaceship()
{
    image = LoadTexture("graphics/spaceship.png");
    position.x = (GetScreenWidth() / 2 - image.width) / 2;
    position.y = GetScreenHeight() - image.height - 100;
    lastFireTime = 0.0;
    laserSound = LoadSound("sounds/laser.ogg");
}

// Destrutor
Spaceship::~Spaceship()
{
    UnloadTexture(image);
    UnloadSound(laserSound);
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
    if (position.x <= 25) {
        position.x = 25;
    }
}

// Mova a nave para a direita
void Spaceship::MoveRight()
{
    position.x += 7;
    if (position.x >= GetScreenWidth() - image.width - 25) {
        position.x = GetScreenWidth() - image.width - 25;
    }
}

// Atire um laser
void Spaceship::FireLaser()
{
    if (GetTime() - lastFireTime  >= 0.35) {
        Laser laser = Laser({position.x + image.width / 2 - 2, position.y}, -6);
        lasers.push_back(laser);
        lastFireTime = GetTime();
        PlaySound(laserSound);
    }
}

// Obtenha o retângulo da nave
Rectangle Spaceship::getRect()
{
    return {position.x, position.y, float(image.width), float(image.height)};
}

// Reinicie a nave
void Spaceship::Reset()
{
    position.x = (GetScreenWidth() / 2 - image.width) / 2.0f;
    position.y = GetScreenHeight() - image.height - 100;
    lastFireTime = 0.0;
    lasers.clear();
}