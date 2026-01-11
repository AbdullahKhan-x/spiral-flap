#include "game.h"
#include "raylib.h"
#include <cmath>

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
    //camera

    Vector2 birdPos = {
        mapConfig.center.x + bird.distance * cosf(bird.angle),
        mapConfig.center.y + bird.distance * sinf(bird.angle)
    };

    camera.target = birdPos;
    camera.offset = {400, 300};  // Screen center
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;

    smoothTarget = birdPos;
    smoothRotation = 0.0f;




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

    if (Bird::CheckCollision(bird, mapConfig.growthRate, 15.0f)) {
        bird.state = Bird::DEAD;
    }

    // Get bird position
    Vector2 birdPos = {
        mapConfig.center.x + bird.distance * cosf(bird.angle),
        mapConfig.center.y + bird.distance * sinf(bird.angle)
    };

    // Smooth camera position
    float CAMERA_SMOOTHING = 0.1f;
    smoothTarget.x += (birdPos.x - smoothTarget.x) * CAMERA_SMOOTHING;
    smoothTarget.y += (birdPos.y - smoothTarget.y) * CAMERA_SMOOTHING;
    camera.target = smoothTarget;

    // Calculate spiral tangent direction
    // Tangent = derivative of (r*cos(θ), r*sin(θ))
    float r = mapConfig.growthRate * bird.angle;
    float dr = mapConfig.growthRate;  // dr/dθ

    Vector2 tangent = {
        dr * cosf(bird.angle) - r * sinf(bird.angle),
        dr * sinf(bird.angle) + r * cosf(bird.angle)
    };

    // Calculate target rotation (tangent points "forward", rotate so it points "up")
    float targetRotation = atan2f(tangent.y, tangent.x) * RAD2DEG - 90.0f;

    // Handle angle wrapping (360° -> 0° transition)
    float rotDiff = targetRotation - smoothRotation;
    while (rotDiff > 180.0f) rotDiff -= 360.0f;
    while (rotDiff < -180.0f) rotDiff += 360.0f;

    smoothRotation += rotDiff * CAMERA_SMOOTHING;
    camera.rotation = smoothRotation;
}


void Game::Draw()
{
    BeginDrawing();
    ClearBackground(BLACK);

    BeginMode2D(camera);
    Map::Draw(map);
    Bird::Draw(bird, birdConfig, mapConfig.center);

    EndMode2D();
    EndDrawing();
}
