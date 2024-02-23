#include "alien.hpp"

Texture2D Alien::alienImages[3] = {};

// Construtor
Alien::Alien(int type, Vector2 position)
{
	this->type = type;
	this->position = position;

	if (alienImages[type - 1].id == 0)
	{
		switch (type)
		{
		case 1:
			alienImages[0] = LoadTexture("Graphics/alien_1.png");
			break;
		case 2:
			alienImages[1] = LoadTexture("Graphics/alien_2.png");
			break;
		case 3:
			alienImages[2] = LoadTexture("Graphics/alien_3.png");
			break;
		default:
			alienImages[0] = LoadTexture("Graphics/alien_1.png");
			break;
		}
	}
}

// Desenhe o alienígena
void Alien::Draw()
{
	DrawTextureV(alienImages[type - 1], position, WHITE);
}

// Obtenha o tipo do alienígena
int Alien::GetType()
{
	return type;
}

// Descarregue as imagens dos alienígenas
void Alien::UnloadImages()
{
	for (int i = 0; i < 4; ++i)
	{
		UnloadTexture(alienImages[i]);
	}
}

// Obtenha o retângulo do alienígena
Rectangle Alien::getRect()
{
	return {
        position.x, position.y,
        float(alienImages[type - 1].width),
        float(alienImages[type - 1].height)
    };
}

// Atualize a posição do alienígena
void Alien::Update(int direction)
{
	position.x += direction;
}