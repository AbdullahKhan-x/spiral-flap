#pragma once
#include "raylib.h"

namespace Bird {
    enum States {
        ALIVE,
        DEAD
    };

    struct Config {
        float gravity;        // inward pull
        float flapStrength;   // outward impulse
        float radius;         // draw size
        float corridorWidth;  // total width
        float forwardSpeed;   // angular speed
    };

    struct Data {
        float angle;
        float radialOffset;
        float radialVelocity;
        States state;
        float flapTimer;      // For visual flapping animation
    };

    void Init(Data& data, float startAngle);
    void Update(Data& data, const Config& config, float dt);
    void Flap(Data& data, const Config& config);
    void Draw(const Data& data, const Config& config, const Vector2& center, float spiralA);
}
