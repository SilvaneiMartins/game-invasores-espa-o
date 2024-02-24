#include "mysteryship.hpp"

// Construtor
MysteryShip::MysteryShip()
{
    image = LoadTexture("Graphics/mystery.png");
    alive = false;
}

// Destrutor
MysteryShip::~MysteryShip()
{
    UnloadTexture(image);
}

// Obtenha o retângulo da nave
void MysteryShip::Spawn()
{
    position.y = 90;
    int side = GetRandomValue(0, 1);

    if (side == 0)
    {
        position.x = 25;
        speed = 3;
    }
    else
    {
        position.x = GetScreenWidth() - image.width - 25;
        speed = -3;
    }

    alive = true;
}

// Obtenha o retângulo da nave
Rectangle MysteryShip::getRect()
{
    if (alive) {
        return {position.x, position.y, float(image.width), float(image.height)};
    } else {
        return {position.x, position.y, 0, 0};
    }
}

// Atualize a nave
void MysteryShip::Update()
{
    if (alive)
    {
        position.x += speed;
        if (position.x > GetScreenWidth() - image.width || position.x < 25)
        {
            alive = false;
        }
    }
}

// Desenhe a nave
void MysteryShip::Draw()
{
    if (alive)
    {
        DrawTextureV(image, position, WHITE);
    }
}