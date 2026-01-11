#include "game.h"
#include "raylib.h"

void Game::Init()
{
    // Map
    mapConfig.growthRate = 40.0f;
    mapConfig.angleStep = 0.05f;
    mapConfig.pointCount = 800;
    mapConfig.center = {400, 300};
    Map::Init(map, mapConfig);

    // Bird
    birdConfig.corridorWidth = 80.0f;
    birdConfig.gravity = 60.0f;
    birdConfig.flapStrength = 35.0f;
    birdConfig.forwardSpeed = 0.9f;
    birdConfig.radius = 6.0f;

    Bird::Init(bird, 0.5f);
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
}

void Game::Draw()
{
    BeginDrawing();
    ClearBackground(BLACK);

    Map::Draw(map);
    Bird::Draw(bird, birdConfig, mapConfig.center, mapConfig.growthRate);

    EndDrawing();
}
