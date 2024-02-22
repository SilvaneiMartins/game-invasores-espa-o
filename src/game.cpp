#include "game.hpp"
#include <iostream>

// Construtor
Game::Game()
{
}

// Destrutor
Game::~Game()
{
}

void Game::Update()
{
    for (auto& laser : spaceship.lasers) {
        laser.Update();
    }

    DeleteInactiveLasers();
    // std::cout << "Tamanho do vetor" << spaceship.lasers.size() << std::endl;
}

// Desenhe a nave e os lasers
void Game::Draw()
{
    spaceship.Draw();
    
    // Desenhe lasers
    for (auto& laser : spaceship.lasers) {
        laser.Draw();
    }
}

// Tecla de entrada
void Game::HandleInput()
{
    if (IsKeyDown(KEY_LEFT)) {
        spaceship.MoveLeft();
    } else if (IsKeyDown(KEY_RIGHT)) {
        spaceship.MoveRight();
    } else if (IsKeyDown(KEY_SPACE)) {
        spaceship.FireLaser();
    };
}   

// Apague os lasers inativos
void Game::DeleteInactiveLasers()
{
    for (auto it = spaceship.lasers.begin(); it != spaceship.lasers.end();) {
        if (!it -> active) {
            it = spaceship.lasers.erase(it);
        } else {
            ++ it;
        }
    }
}