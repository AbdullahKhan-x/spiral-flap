#pragma once
#include "raylib.h"

namespace Map {

    struct Config {
        float growthRate;
        float angleStep;
        int pointCount;
        Vector2 center;
    };

    struct Data {
        Vector2* points;
        int count;
    };

    void Init(Data& data, const Config& config);
    void Draw(const Data& data);

}
