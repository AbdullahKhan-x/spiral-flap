#pragma once
#include "map.h"
#include "bird.h"  // CHANGE THIS LINE

struct Game {
    Map::Data map;
    Map::Config mapConfig;

    Bird::Data bird;
    Bird::Config birdConfig;

    void Init();
    void Input();
    void Update(float dt);
    void Draw();
};
