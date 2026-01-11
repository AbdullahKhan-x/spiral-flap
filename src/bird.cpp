#include "bird.h"
#include <cmath>

void Bird::Init(Data& data, float startAngle)
{
    data.angle = startAngle;
    data.radialOffset = 0.0f;
    data.radialVelocity = 0.0f;
    data.state = ALIVE;
    data.flapTimer = 0.0f;
}

void Bird::Update(Data& data, const Config& config, float dt)
{
    if (data.state != ALIVE) return;

    // Move forward along the spiral path at constant angular velocity
    data.angle += config.forwardSpeed * dt;

    // Apply gravity - pulls toward center (inner wall)
    data.radialVelocity -= config.gravity * dt;

    // Update radial position (position within the corridor)
    data.radialOffset += data.radialVelocity * dt;

    // Check collision with corridor walls
    float half = config.corridorWidth * 0.5f;

    // Hit inner wall (too close to center)
    if (data.radialOffset < -half) {
        data.radialOffset = -half;
        data.radialVelocity = 0.0f;
        data.state = DEAD;
    }

    // Hit outer wall (too far from center)
    if (data.radialOffset > half) {
        data.radialOffset = half;
        data.radialVelocity = 0.0f;
        data.state = DEAD;
    }

    // Update flap animation timer
    if (data.flapTimer > 0.0f) {
        data.flapTimer -= dt;
    }
}

void Bird::Flap(Data& data, const Config& config)
{
    if (data.state != ALIVE) return;
    data.radialVelocity = config.flapStrength;
    data.flapTimer = 0.15f;  // Visual flap duration
}

void Bird::Draw(const Data& data, const Config& config, const Vector2& center, float spiralA)
{
    // Calculate the base radius at current angle (center of spiral path)
    float baseRadius = spiralA * data.angle;

    // Calculate position on the spiral
    float cosA = cosf(data.angle);
    float sinA = sinf(data.angle);

    // Get the perpendicular direction (tangent to spiral)
    // This is the direction the bird moves left-right
    float perpAngle = data.angle + PI / 2.0f;
    float perpCosA = cosf(perpAngle);
    float perpSinA = sinf(perpAngle);

    // Bird position = center of spiral + offset perpendicular to spiral
    Vector2 pos = {
        center.x + baseRadius * cosA + data.radialOffset * perpCosA,
        center.y + baseRadius * sinA + data.radialOffset * perpSinA
    };

    // Draw bird body (white dot like in the image)
    Color birdColor = data.state == ALIVE ? WHITE : RED;
    DrawCircleV(pos, config.radius, birdColor);

    // Add a subtle glow effect
    if (data.state == ALIVE) {
        DrawCircleV(pos, config.radius + 2, ColorAlpha(WHITE, 0.3f));
    }

    // Draw flapping indicator
    if (data.flapTimer > 0.0f) {
        DrawCircleV(pos, config.radius + 4, ColorAlpha(YELLOW, 0.5f));
    }
}
