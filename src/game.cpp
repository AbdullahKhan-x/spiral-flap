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

    Bird::Init(bird, 4.0f, 40.0f);

    Vector2 birdPos = {
        mapConfig.center.x + bird.distance * cosf(bird.angle),
        mapConfig.center.y + bird.distance * sinf(bird.angle)
    };

    obstacleCount = 0;
    for (int i = 0; i < 30; i++) {
        obstacles[i].active = false;
    }

    camera.target = birdPos;
    camera.offset = {400, 300};
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

void Game::CheckObstacleCollision()
{
    const float GAP_SIZE = 60.0f;

    for (int i = 0; i < 20; i++) {
        if (!obstacles[i].active) continue;

        float angleDiff = fabs(bird.angle - obstacles[i].angle);

        if (angleDiff < 0.1f) {
            // Calculate bird's perpendicular offset from spiral
            float spiralRadius = mapConfig.growthRate * bird.angle;

            // Get tangent and perpendicular at bird's position
            float r = spiralRadius;
            float dr = mapConfig.growthRate;

            Vector2 tangent = {
                dr * cosf(bird.angle) - r * sinf(bird.angle),
                dr * sinf(bird.angle) + r * cosf(bird.angle)
            };

            float len = sqrtf(tangent.x * tangent.x + tangent.y * tangent.y);
            tangent.x /= len;
            tangent.y /= len;

            Vector2 perp = { -tangent.y, tangent.x };

            // Bird position
            Vector2 birdPos = {
                mapConfig.center.x + bird.distance * cosf(bird.angle),
                mapConfig.center.y + bird.distance * sinf(bird.angle)
            };

            // Spiral center at bird's angle
            Vector2 spiralCenter = {
                mapConfig.center.x + spiralRadius * cosf(bird.angle),
                mapConfig.center.y + spiralRadius * sinf(bird.angle)
            };

            // Calculate bird's perpendicular offset
            Vector2 diff = { birdPos.x - spiralCenter.x, birdPos.y - spiralCenter.y };
            float birdOffset = diff.x * perp.x + diff.y * perp.y;

            float gapTop = obstacles[i].gapCenter + GAP_SIZE / 2.0f;
            float gapBottom = obstacles[i].gapCenter - GAP_SIZE / 2.0f;

            if (birdOffset < gapBottom || birdOffset > gapTop) {
                bird.state = Bird::DEAD;
            }
        }
    }
}

void Game::GenerateObstacles()
{
    const float OBSTACLE_SPACING = 3.14f * 0.8f;

    float lastObstacleAngle = bird.angle;
    for (int i = 0; i < 20; i++) {
        if (obstacles[i].active && obstacles[i].angle > lastObstacleAngle) {
            lastObstacleAngle = obstacles[i].angle;
        }
    }

    while (lastObstacleAngle < bird.angle + 3.14f * 4.0f) {
        for (int i = 0; i < 20; i++) {
            if (!obstacles[i].active) {
                obstacles[i].active = true;
                obstacles[i].angle = lastObstacleAngle + OBSTACLE_SPACING;
                obstacles[i].gapCenter = -30.0f;
                lastObstacleAngle = obstacles[i].angle;
                break;
            }
        }
    }

    for (int i = 0; i < 20; i++) {
        if (obstacles[i].active && obstacles[i].angle < bird.angle - 3.14f * 2.0f) {
            obstacles[i].active = false;
        }
    }
}

void Game::DrawObstacles()
{
    const float GAP_SIZE = 60.0f;
    for (int i = 0; i < 20; i++) {
        if (!obstacles[i].active) continue;
        float spiralRadius = mapConfig.growthRate * obstacles[i].angle;
        float gapTopOffset = obstacles[i].gapCenter + GAP_SIZE / 2.0f;
        float gapBottomOffset = obstacles[i].gapCenter - GAP_SIZE / 2.0f;
        // Calculate tangent direction at this angle
        float r = spiralRadius;
        float dr = mapConfig.growthRate;
        Vector2 tangent = {
            dr * cosf(obstacles[i].angle) - r * sinf(obstacles[i].angle),
            dr * sinf(obstacles[i].angle) + r * cosf(obstacles[i].angle)
        };
        // Normalize tangent
        float len = sqrtf(tangent.x * tangent.x + tangent.y * tangent.y);
        tangent.x /= len;
        tangent.y /= len;
        // Perpendicular direction (rotate tangent 90 degrees)
        Vector2 perp = { -tangent.y, tangent.x };
        // Center point on spiral
        Vector2 center = {
            mapConfig.center.x + spiralRadius * cosf(obstacles[i].angle),
            mapConfig.center.y + spiralRadius * sinf(obstacles[i].angle)
        };
        float barWidth = 20.0f;
        // Bottom bar
        Vector2 inner = {
            center.x + (gapBottomOffset - 40) * perp.x - barWidth * tangent.x,
            center.y + (gapBottomOffset - 40) * perp.y - barWidth * tangent.y
        };
        Vector2 gapBot = {
            center.x + gapBottomOffset * perp.x - barWidth * tangent.x,
            center.y + gapBottomOffset * perp.y - barWidth * tangent.y
        };
        Vector2 gapBotEnd = {
            center.x + gapBottomOffset * perp.x + barWidth * tangent.x,
            center.y + gapBottomOffset * perp.y + barWidth * tangent.y
        };
        Vector2 innerEnd = {
            center.x + (gapBottomOffset - 40) * perp.x + barWidth * tangent.x,
            center.y + (gapBottomOffset - 40) * perp.y + barWidth * tangent.y
        };
        DrawTriangle(inner, gapBot, gapBotEnd, RED);
        DrawTriangle(inner, gapBotEnd, innerEnd, RED);
        // Top bar
        Vector2 gapTop = {
            center.x + gapTopOffset * perp.x - barWidth * tangent.x,
            center.y + gapTopOffset * perp.y - barWidth * tangent.y
        };
        Vector2 outer = {
            center.x + (gapTopOffset + 40) * perp.x - barWidth * tangent.x,
            center.y + (gapTopOffset + 40) * perp.y - barWidth * tangent.y
        };
        Vector2 outerEnd = {
            center.x + (gapTopOffset + 40) * perp.x + barWidth * tangent.x,
            center.y + (gapTopOffset + 40) * perp.y + barWidth * tangent.y
        };
        Vector2 gapTopEnd = {
            center.x + gapTopOffset * perp.x + barWidth * tangent.x,
            center.y + gapTopOffset * perp.y + barWidth * tangent.y
        };
        DrawTriangle(gapTop, outer, outerEnd, RED);
        DrawTriangle(gapTop, outerEnd, gapTopEnd, RED);

        // DEBUG: Visualize collision detection
        DrawCircleV(center, 5.0f, YELLOW);  // Obstacle center

        Vector2 topLine = {
            center.x + gapTopOffset * perp.x,
            center.y + gapTopOffset * perp.y
        };
        Vector2 bottomLine = {
            center.x + gapBottomOffset * perp.x,
            center.y + gapBottomOffset * perp.y
        };

        DrawCircleV(topLine, 3.0f, GREEN);     // Gap top boundary
        DrawCircleV(bottomLine, 3.0f, BLUE);   // Gap bottom boundary
    }
}
void Game::Update(float dt)
{
    Bird::Update(bird, birdConfig, dt);

    if (Bird::CheckCollision(bird, mapConfig.growthRate, 2.0f)) {
        bird.state = Bird::DEAD;
    }

    Vector2 birdPos = {
        mapConfig.center.x + bird.distance * cosf(bird.angle),
        mapConfig.center.y + bird.distance * sinf(bird.angle)
    };

    float CAMERA_SMOOTHING = 0.1f;
    smoothTarget.x += (birdPos.x - smoothTarget.x) * CAMERA_SMOOTHING;
    smoothTarget.y += (birdPos.y - smoothTarget.y) * CAMERA_SMOOTHING;
    camera.target = smoothTarget;

    float r = mapConfig.growthRate * bird.angle;
    float dr = mapConfig.growthRate;

    Vector2 tangent = {
        dr * cosf(bird.angle) - r * sinf(bird.angle),
        dr * sinf(bird.angle) + r * cosf(bird.angle)
    };

    float targetRotation = atan2f(tangent.y, tangent.x) * RAD2DEG - 90.0f;

    float rotDiff = targetRotation - smoothRotation;
    while (rotDiff > 180.0f) rotDiff -= 360.0f;
    while (rotDiff < -180.0f) rotDiff += 360.0f;

    smoothRotation += rotDiff * CAMERA_SMOOTHING;
    camera.rotation = smoothRotation;

    GenerateObstacles();
    CheckObstacleCollision();
}

void Game::Draw()
{
    BeginDrawing();
    ClearBackground(BLACK);

    BeginMode2D(camera);
    Map::Draw(map);
    Bird::Draw(bird, birdConfig, mapConfig.center);
    DrawObstacles();

    EndMode2D();
    EndDrawing();
}
