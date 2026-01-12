#pragma once
#include "map.h"
#include "bird.h"  // CHANGE THIS LINE


struct Obstacle {
    float angle;        // Angular position on spiral
    float gapCenter;    // Radial offset of the gap center
    bool active;        // Is this obstacle in use?
};

struct Game {
    Map::Data map;
    Map::Config mapConfig;

    Bird::Data bird;
    Bird::Config birdConfig;
    Vector2 smoothTarget;
    float smoothRotation;

    Obstacle obstacles[30];
    int obstacleCount;

    Camera2D camera;

    void Init();
    void Input();
    void Update(float dt);
    void Draw();
    void GenerateObstacles();
    void CheckObstacleCollision();
    void DrawObstacles();
};
