#pragma once

#include "spaceship.hpp"
#include "obstacle.hpp"
#include "alien.hpp"
#include "mysteryship.hpp"

class Game
{
    public:
        Game();
        ~Game();
        void Draw();
        void Update();
        void HandleInput();
        bool run;
        int lives;
        int score;
    private:
        void DeleteInactiveLasers();
        std::vector<Obstacle> GenerateObstacles();
        std::vector<Alien> GenerateAliens();
        void MoveAliens();
        void MoveDownAliens(int distance);
        void AliensShootLaser();
        void CheckForCollisions();
        void GameOver();
        void Reset();
        void InitGame();
        Spaceship spaceship;
        std::vector<Obstacle> obstacles;
        std::vector<Alien> aliens;
        int aliensDirection;
        std::vector<Laser> aliensLasers;
        constexpr static float alienLaserShootInterval = 0.35;
        float timeLastAlienFired;
        MysteryShip mysteryShip;
        float mysteryShipSpawnInterval;
        float timeLastSpawn;
};