#include "map.h"
#include <cmath>

// Initialize the spiral map
void initSpiralMap(SpiralMap& map, const SpiralConfig& config, int chunkSize) {
    map.config = config;
    map.currentAngle = 0.0f;
    map.chunkSize = chunkSize;
    map.points.clear();

    // Generate initial chunks
    generateNextChunk(map);
    generateNextChunk(map);
}

// Generate a single spiral point at a specific angle
SpiralPoint getSpiralPointAtAngle(const SpiralConfig& config, float angle) {
    float r = config.a * angle;

    SpiralPoint point;
    point.x = config.center.x + r * cos(angle);
    point.y = config.center.y + r * sin(angle);
    point.angle = angle;

    return point;
}

// Generate the next chunk of spiral points
void generateNextChunk(SpiralMap& map) {
    for (int i = 0; i < map.chunkSize; i++) {
        SpiralPoint point = getSpiralPointAtAngle(map.config, map.currentAngle);
        map.points.push_back(point);
        map.currentAngle += map.config.angleStep;
    }
}

// Remove old points that are no longer needed (behind the player)
void cleanOldPoints(SpiralMap& map, float minAngle) {
    // Remove points with angle less than minAngle
    size_t removeCount = 0;

    for (size_t i = 0; i < map.points.size(); i++) {
        if (map.points[i].angle < minAngle) {
            removeCount++;
        }
        else {
            break;  // Points are in order, so we can stop
        }
    }

    if (removeCount > 0) {
        map.points.erase(map.points.begin(), map.points.begin() + removeCount);
    }
}

// Draw the spiral map
void drawSpiralMap(const SpiralMap& map, Color color, float thickness) {
    for (size_t i = 0; i < map.points.size() - 1; i++) {
        DrawLineEx(
            Vector2{ map.points[i].x, map.points[i].y },
            Vector2{ map.points[i + 1].x, map.points[i + 1].y },
            thickness,
            color
        );
    }
}