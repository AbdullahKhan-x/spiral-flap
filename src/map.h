#ifndef MAP_H
#define MAP_H

#include <vector>
#include <raylib.h>

// Struct to hold a single point on the spiral
struct SpiralPoint {
    float x;
    float y;
    float angle;  // Store angle for reference
};

// Struct to hold spiral configuration
struct SpiralConfig {
    float a;              // Growth rate of spiral
    float angleStep;      // Step size for generating points
    Vector2 center;       // Center point of spiral
};

// Struct to manage infinite spiral generation
struct SpiralMap {
    std::vector<SpiralPoint> points;
    float currentAngle;
    SpiralConfig config;
    int chunkSize;  // How many points to generate at once
};

// Function declarations
void initSpiralMap(SpiralMap& map, const SpiralConfig& config, int chunkSize);
void generateNextChunk(SpiralMap& map);
void cleanOldPoints(SpiralMap& map, float minAngle);
void drawSpiralMap(const SpiralMap& map, Color color, float thickness);
SpiralPoint getSpiralPointAtAngle(const SpiralConfig& config, float angle);

#endif