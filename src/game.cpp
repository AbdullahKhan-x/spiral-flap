#include "game.h"
#include "raylib.h"

void Game::Init()
{
    // Map
    mapConfig.growthRate = 20.0f;
    mapConfig.angleStep = 0.1f;
    mapConfig.pointCount = 500;
    mapConfig.center = {400, 300};
    Map::Init(map, mapConfig);

    // Bird
    birdConfig.gravity = 200.0f;
    birdConfig.flapStrength = 150.0f;
    birdConfig.forwardSpeed = 0.8f;
    birdConfig.radius = 8.0f;

    Bird::Init(bird, 4.0f, 40.0f);  // start at angle 3, distance 60 from center
}

void Game::Input()
{
    if (IsKeyPressed(KEY_SPACE)) {
        Bird::Flap(bird, birdConfig);
    }
}

void Game::Update(float dt)
{
    Bird::Update(bird, birdConfig, dt);

    // Check collision with spiral
    if (Bird::CheckCollision(bird, mapConfig.growthRate, 12.0f)) {
        bird.state = Bird::DEAD;
    }
}
void Game::Draw()
{
    BeginDrawing();
    ClearBackground(BLACK);
    Map::Draw(map);
    Bird::Draw(bird, birdConfig, mapConfig.center);
    EndDrawing();
}
