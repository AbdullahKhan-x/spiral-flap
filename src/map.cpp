#include "map.h"
#include <cmath>

void Map::Init(Data& data, const Config& config)
{
    data.count = config.pointCount;
    data.points = new Vector2[data.count];

    float angle = 0.0f;
    for (int i = 0; i < data.count; i++) {
        float r = config.growthRate * angle;
        data.points[i] = {
            config.center.x + r * cosf(angle),
            config.center.y + r * sinf(angle)
        };
        angle += config.angleStep;
    }
}

void Map::Draw(const Data& data)
{
    for (int i = 0; i < data.count - 1; i++) {
        DrawLineEx(data.points[i], data.points[i + 1], 3.0f, WHITE);
    }
}

void Map::Cleanup(Data& data)
{
    delete[] data.points;
}
