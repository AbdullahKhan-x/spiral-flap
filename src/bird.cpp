#include "bird.h"
#include <cmath>

void Bird::Init(Data& data, float startAngle, float startDistance)
{
    data.angle = startAngle;
    data.distance = startDistance;
    data.velocity = 0.0f;
    data.state = ALIVE;
}

void Bird::Update(Data& data, const Config& config, float dt)
{
    if (data.state != ALIVE) return;

    // Move forward along spiral
    data.angle += config.forwardSpeed * dt;

    // Gravity pulls inward (negative velocity = toward center)
    data.velocity -= config.gravity * dt;

    // Update distance from center
    data.distance += data.velocity * dt;

    // Don't let bird go to center
    if (data.distance < 10.0f) {
        data.distance = 10.0f;
        data.velocity = 0.0f;
        data.state = DEAD;
    }
}

bool Bird::CheckCollision(const Data& data, float spiralGrowthRate, float safeDistance)
{
    // Calculate where spiral should be at bird's current angle
    float expectedSpiralRadius = spiralGrowthRate * data.angle;

    // Check if bird is too close to the spiral line
    float distanceToSpiral = fabs(data.distance - expectedSpiralRadius);

    if (distanceToSpiral < safeDistance) {
        return true;  // Collision!
    }

    return false;
}

void Bird::Flap(Data& data, const Config& config)
{
    if (data.state != ALIVE) return;
    // Push outward
    data.velocity = config.flapStrength;
}

void Bird::Draw(const Data& data, const Config& config, const Vector2& center)
{
    Vector2 pos = {
        center.x + data.distance * cosf(data.angle),
        center.y + data.distance * sinf(data.angle)
    };

    Color color = data.state == ALIVE ? RED : GRAY;
    DrawCircleV(pos, config.radius, color);
}
