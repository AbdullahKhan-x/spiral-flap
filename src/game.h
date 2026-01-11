#pragma once
#include "map.h"
#include "bird.h"

struct Game {
    Map::Data map;
    Bird::Data bird;

    Map::Config mapConfig;
    Bird::Config birdConfig;

    void Init();
    void Input();
    void Update(float dt);
    void Draw();
};
