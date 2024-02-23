#include "block.hpp"

// Construtor
Block::Block(Vector2 position)
{
	this->position = position;
}

// Obtenha o retângulo do bloco
void Block::Draw()
{
	DrawRectangle(position.x, position.y, 3, 3, {243, 216, 63, 255});
}

// Obtenha o retângulo do bloco
Rectangle Block::getRect()
{
	Rectangle rect;
    rect.x = position.x;
    rect.y = position.y;
    rect.width = 3;
    rect.height = 3;
	return rect;
}