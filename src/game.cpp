#include "game.hpp"
#include <iostream>

// Construtor
Game::Game()
{
    obstacles = GenerateObstacles();
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
}

// Desenhe a nave e os lasers
void Game::Draw()
{
    spaceship.Draw();
    
    // Desenhe lasers
    for (auto& laser : spaceship.lasers) {
        laser.Draw();
    }

    for (auto& obstacle : obstacles) {
        obstacle.Draw();
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

// Gere obstáculos
std::vector<Obstacle> Game::GenerateObstacles()
{
    int obstacleWidth = Obstacle::grid[0].size() * 3;
    float gap = (GetScreenWidth() - (4 * obstacleWidth)) / 5;

    for (int i = 0; i < 4; ++i) {
        float offsetX = (i + 1) * gap + i * obstacleWidth;
        obstacles.push_back(Obstacle({offsetX, float(GetScreenHeight() - 100)}));
    }

    return obstacles;
}