#include "laser.hpp"
#include <iostream>

// Construtor
Laser::Laser(Vector2 position, int speed)
{
    this->position = position;
    this->speed = speed;
    active = true;
}

// Obtenha o retângulo do laser
void Laser::Draw()
{
    if (active)
        DrawRectangle(position.x, position.y, 4, 15, {243, 216, 63, 255});
}

// Obtenha o retângulo do laser
void Laser::Update()
{
    position.y += speed;
    if (active) {
        if (position.y > GetScreenHeight() || position.y < 0) {
            active = false;
        }
    }
}

// Obtenha o retângulo do laser
Rectangle Laser::getRect()
{
    Rectangle rect;
    rect.x = position.x;
    rect.y = position.y;
    rect.width = 4;
    rect.height = 15;
    return rect;
}