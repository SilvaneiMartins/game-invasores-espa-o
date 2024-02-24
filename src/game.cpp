#include <iostream>
#include <fstream>

#include "game.hpp"

// Construtor
Game::Game()
{
    music = LoadMusicStream("sounds/music.ogg");
    explosionSound = LoadSound("sounds/explosion.ogg");
    PlayMusicStream(music);
    InitGame();
}

// Destrutor
Game::~Game()
{
    Alien::UnloadImages();
    UnloadMusicStream(music);
    UnloadSound(explosionSound);
}

void Game::Update()
{
    if (run) {
        double currentTime = GetTime();
        if(currentTime - timeLastSpawn > mysteryShipSpawnInterval) {
            mysteryShip.Spawn();
            timeLastSpawn = GetTime();
            mysteryShipSpawnInterval = GetRandomValue(10, 20);
        }

        for (auto& laser : spaceship.lasers) {
            laser.Update();
        }

        MoveAliens();
        AliensShootLaser();
        
        for (auto& laser : aliensLasers) {
            laser.Update();
        }

        DeleteInactiveLasers();
        mysteryShip.Update();
        CheckForCollisions();
    } else {
        if (IsKeyPressed(KEY_ENTER)) {
            Reset();
            InitGame();
        }
    }
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

    for (auto& alien : aliens) {
        alien.Draw();
    }

    for (auto& laser : aliensLasers) {
        laser.Draw();
    }

    mysteryShip.Draw();
}

// Tecla de entrada
void Game::HandleInput()
{
    if (run) {
        if (IsKeyDown(KEY_LEFT)) {
            spaceship.MoveLeft();
        } else if (IsKeyDown(KEY_RIGHT)) {
            spaceship.MoveRight();
        } else if (IsKeyDown(KEY_SPACE)) {
            spaceship.FireLaser();
        };
    }
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

    for (auto it = aliensLasers.begin(); it != aliensLasers.end();) {
        if (!it -> active) {
            it = aliensLasers.erase(it);
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
        obstacles.push_back(Obstacle({offsetX, float(GetScreenHeight() - 200)}));
    }

    return obstacles;
}

// Gere alienígenas
std::vector<Alien> Game::GenerateAliens()
{
    std::vector<Alien> aliens;
    for (int row = 0; row < 5; ++row) {
        for (int column = 0; column < 11; ++column) {

            int alienType;
            if (row == 0) {
                alienType = 3;
            } else if (row == 1 || row == 2) {
                alienType = 2;
            } else {
                alienType = 1;
            }

            float x = 75 + column * 55;
            float y = 110 + row * 55;
            aliens.push_back(Alien(alienType, {x, y}));
        }
    }

    return aliens;
}

// Mova os alienígenas
void Game::MoveAliens()
{
    for (auto& alien : aliens) {
        if (alien.position.x + alien.alienImages[alien.type - 1].width > GetScreenWidth() - 25) {
            aliensDirection = -1;
            MoveDownAliens(4);
        }

        if (alien.position.x < 25) {
            aliensDirection = 1;
            MoveDownAliens(4);
        }
        alien.Update(aliensDirection);
    }
}

// Mova os alienígenas para baixo
void Game::MoveDownAliens(int distance)
{
    for (auto& alien : aliens) {
        alien.position.y += distance;
    }
}

// Alienígenas atiram laser
void Game::AliensShootLaser()
{
    double currentTime = GetTime();
    if (currentTime - timeLastAlienFired >= alienLaserShootInterval && !aliens.empty()) {
        int randomIndex = GetRandomValue(0, aliens.size() - 1);
        Alien& alien = aliens[randomIndex];
        aliensLasers.push_back(Laser({alien.position.x + alien.alienImages[alien.type -1].width / 2, 
                                    alien.position.y + alien.alienImages[alien.type - 1].height}, 6));
        timeLastAlienFired = GetTime();
    }
}

// Verifique colisões
void Game::CheckForCollisions()
{
    // Spaceship lasers
    for (auto& laser: spaceship.lasers)
    {
        auto it = aliens.begin();
        while (it != aliens.end())
        {
            if (CheckCollisionRecs(it -> getRect(), laser.getRect()))
            {
                // Tocar som de explosão
                PlaySound(explosionSound);

                // Adicione pontos ao jogador
                if (it -> type == 1) 
                {
                    score += 100;
                } else if (it -> type == 2)
                {
                    score += 200;
                } else if (it -> type == 3)
                {
                    score += 300;
                }

                // Verifique se o jogador atingiu a pontuação mais alta
                checkForHighscore();
                
                it = aliens.erase(it);
                laser.active = false;
            }
            else
            {
                ++it;
            }
        }

        for (auto& obstacle : obstacles)
        {
            auto it = obstacle.blocks.begin();
            while (it != obstacle.blocks.end())
            {
                if (CheckCollisionRecs(it -> getRect(), laser.getRect()))
                {
                    it = obstacle.blocks.erase(it);
                    laser.active = false;
                }
                else
                {
                    ++it;
                }
            }
        }

        if (CheckCollisionRecs(mysteryShip.getRect(), laser.getRect()))
        {
            mysteryShip.alive = false;
            laser.active = false;
            score += 500;
            checkForHighscore();
            PlaySound(explosionSound);
        }
    }

    // Alien lasers
    for (auto& laser: aliensLasers)
    {
        if (CheckCollisionRecs(laser.getRect(), spaceship.getRect()))
        {
            laser.active = false;
            lives --;
            if (lives == 0) {
                GameOver();
            }
        }

        for (auto& obstacle : obstacles)
        {
            auto it = obstacle.blocks.begin();
            while (it != obstacle.blocks.end())
            {
                if (CheckCollisionRecs(it -> getRect(), laser.getRect()))
                {
                    it = obstacle.blocks.erase(it);
                    laser.active = false;
                }
                else
                {
                    ++it;
                }
            }
        }
    }

    // Alien colide com obstáculos
    for (auto& alien : aliens)
    {
        for (auto& obstacle : obstacles)
        {
            auto it = obstacle.blocks.begin();
            while (it != obstacle.blocks.end())
            {
                if (CheckCollisionRecs(it -> getRect(), alien.getRect()))
                {
                    it = obstacle.blocks.erase(it);
                }
                else
                {
                    ++it;
                }
            }
        }

        if (CheckCollisionRecs(alien.getRect(), spaceship.getRect()))
        {
            GameOver();
        }
    }
}

// Fim do jogo
void Game::GameOver()
{
    run = false;
}

// Inicializa o Game
void Game::InitGame()
{
    obstacles = GenerateObstacles();
    aliens = GenerateAliens();
    aliensDirection = 1;
    timeLastAlienFired = 0.0;
    timeLastSpawn = 0.0;
    lives = 3;
    score = 0;
    highscore = loadHighscoreFromFile();
    run = true;
    mysteryShipSpawnInterval = GetRandomValue(10, 20);
}

// Verifique a pontuação mais alta
void Game::checkForHighscore()
{
    if (score > highscore) {
        highscore = score;
        saveHighscoreToFile(highscore);
    }
}

// Salve a pontuação mais alta no arquivo
void Game::saveHighscoreToFile(int highscore)
{
    std::ofstream highscoreFile("highscore.txt");
    
    if(highscoreFile.is_open()) {
        highscoreFile << highscore;
        highscoreFile.close();
    } else {
        std::cerr << "Não foi possível salvar pontuação no arquivo." << std::endl;
    }
}

// Carregar pontuação mais alta do arquivo
int Game::loadHighscoreFromFile() 
{
    int loadedHighscore = 0;
    std::ifstream highscoreFile("highscore.txt");

    if(highscoreFile.is_open()) {
        highscoreFile >> loadedHighscore;
        highscoreFile.close();
    } else {
        std::cerr << "Não foi possível carregar pontuação do arquivo." << std::endl;
    }

    return loadedHighscore;
}

// Reiniciar o jogo
void Game::Reset()
{
    spaceship.Reset();
    aliens.clear();
    aliensLasers.clear();
    obstacles.clear();
}