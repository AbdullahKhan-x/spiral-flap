#ifndef BIRD_H
#define BIRD_H

#include "raylib.h"

struct Bird {
    Vector2 position;
    float velocityY;
    float gravity;
    float flapStrength;
    float radius;

    // "Constructor"
    Bird(float startX, float startY);

    void Update();   // gravity + movement
    void Flap();     // input
    void Draw();     // rendering

    Rectangle GetBounds() const;
};

#endif

