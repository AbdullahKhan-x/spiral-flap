#pragma once
#include "raylib.h"

namespace Bird {
    enum States {
        ALIVE,
        DEAD
    };

    struct Config {
        float gravity;        // pulls inward
        float flapStrength;   // pushes outward
        float radius;         // bird size
        float forwardSpeed;   // angular speed around spiral
    };

    struct Data {
        float angle;          // position along spiral
        float distance;       // distance from center
        float velocity;       // radial velocity (in/out)
        States state;
    };

    void Init(Data& data, float startAngle, float startDistance);
    void Update(Data& data, const Config& config, float dt);
    bool CheckCollision(const Data& data, float spiralGrowthRate, float safeDistance);
    void Flap(Data& data, const Config& config);
    void Draw(const Data& data, const Config& config, const Vector2& center);
}
