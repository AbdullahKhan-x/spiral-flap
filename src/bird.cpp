#include "bird.h"

Bird::Bird(float startX, float startY) {
    position = { startX, startY };
    velocityY = 0.0f;
    gravity = 900.0f;        // pixels per second²
    flapStrength = -350.0f;  // upward impulse
    radius = 20.0f;
}

void Bird::Update() {
    float dt = GetFrameTime();

    velocityY += gravity * dt;
    position.y += velocityY * dt;
}

void Bird::Flap() {
    velocityY = flapStrength;
}

void Bird::Draw() {
    DrawCircleV(position, radius, YELLOW);
}

Rectangle Bird::GetBounds() const {
    return {
        position.x - radius,
        position.y - radius,
        radius * 2,
        radius * 2
    };
}
