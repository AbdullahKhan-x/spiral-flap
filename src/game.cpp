#include "game.h"
#include "raymath.h"
#include <cmath>
#include <algorithm>

// Define constants
const float SPIRAL_A = 80.0f;
const float SPIRAL_B = 25.0f;
const float CORRIDOR_WIDTH = 50.0f;

const float OBSTACLE_GAP = 35.0f;
const float OBSTACLE_THICKNESS = 8.0f;
const float OBSTACLE_SPACING = PI * 0.8f;
const float OBSTACLE_VISUAL_WIDTH = 15.0f;
const float OBSTACLE_COLLISION_WIDTH = 10.0f;

const float FORWARD_SPEED = 0.6f;
const float GRAVITY = -200.0f;
const float FLAP_FORCE = 100.0f;
const float RADIAL_DAMPING = 0.98f;

const float CAMERA_SMOOTHING = 0.1f;
const float CAMERA_ZOOM = 2.75f;
const bool ROTATE_CAMERA = true;

// Spiral math functions
float spiralRadius(float theta) {
    return SPIRAL_A + SPIRAL_B * theta;
}

Vector2 spiralToWorld(float theta, float radiusOffset) {
    float r = spiralRadius(theta) + radiusOffset;
    return { r * cosf(theta), r * sinf(theta) };
}

Vector2 spiralTangent(float theta) {
    float r = spiralRadius(theta);
    float dx = SPIRAL_B * cosf(theta) - r * sinf(theta);
    float dy = SPIRAL_B * sinf(theta) + r * cosf(theta);
    float len = sqrtf(dx * dx + dy * dy);
    return { dx / len, dy / len };
}

Vector2 spiralNormal(float theta) {
    return { -sinf(theta), cosf(theta) };
}

// Bird functions
void resetBird(Bird& bird) {
    bird.theta = 0.0f;
    bird.radialVelocity = 0.0f;
    bird.radialOffset = 0.0f;
    bird.position = spiralToWorld(0.0f);
    bird.rotation = 0.0f;
    bird.isAlive = true;
}

void updateBird(Bird& bird, float dt) {
    bird.theta += FORWARD_SPEED * dt;
    bird.radialVelocity += GRAVITY * dt;
    bird.radialVelocity *= powf(RADIAL_DAMPING, dt * 60.0f);
    bird.radialOffset += bird.radialVelocity * dt;
    bird.position = spiralToWorld(bird.theta, bird.radialOffset);

    Vector2 tangent = spiralTangent(bird.theta);
    Vector2 normal = spiralNormal(bird.theta);
    Vector2 velocity = {
        tangent.x * FORWARD_SPEED * spiralRadius(bird.theta) + normal.x * bird.radialVelocity,
        tangent.y * FORWARD_SPEED * spiralRadius(bird.theta) + normal.y * bird.radialVelocity
    };
    bird.rotation = atan2f(velocity.y, velocity.x) * RAD2DEG;
}

void flapBird(Bird& bird) {
    bird.radialVelocity += FLAP_FORCE;
}

// Collision functions
bool checkCollision(const Bird& bird) {
    return fabs(bird.radialOffset) > CORRIDOR_WIDTH;
}

bool checkObstacleCollision(const Bird& bird, const Obstacle& obstacle) {
    float thetaDiff = fabs(bird.theta - obstacle.theta);
    float currentRadius = spiralRadius(obstacle.theta);
    float halfAngularWidth = (OBSTACLE_COLLISION_WIDTH / 2.0f) / currentRadius;

    if (thetaDiff < halfAngularWidth) {
        float birdRadialPos = bird.radialOffset;
        float gapTop = obstacle.gapCenter + OBSTACLE_GAP / 2.0f;
        float gapBottom = obstacle.gapCenter - OBSTACLE_GAP / 2.0f;

        if (birdRadialPos < gapBottom || birdRadialPos > gapTop) {
            return true;
        }
    }
    return false;
}

// Obstacle functions
void generateObstacles(std::vector<Obstacle>& obstacles, float birdTheta) {
    obstacles.erase(
        std::remove_if(obstacles.begin(), obstacles.end(),
            [birdTheta](const Obstacle& obs) {
                return obs.theta < birdTheta - PI * 2.0f;
            }),
        obstacles.end()
    );

    float lastObstacleTheta = 0.0f;
    if (!obstacles.empty()) {
        lastObstacleTheta = obstacles.back().theta;
    }

    while (lastObstacleTheta < birdTheta + PI * 4.0f) {
        Obstacle newObstacle;
        newObstacle.theta = lastObstacleTheta + OBSTACLE_SPACING;
        newObstacle.gapCenter = ((float)GetRandomValue(-20, 20));
        newObstacle.passed = false;
        obstacles.push_back(newObstacle);
        lastObstacleTheta = newObstacle.theta;
    }
}

// Rendering functions
void drawSpiral(float startTheta, float endTheta, int segments, Camera2D camera) {
    for (int i = 0; i < segments; i++) {
        float t1 = startTheta + (endTheta - startTheta) * (float)i / segments;
        float t2 = startTheta + (endTheta - startTheta) * (float)(i + 1) / segments;

        Vector2 inner1 = spiralToWorld(t1, -CORRIDOR_WIDTH);
        Vector2 inner2 = spiralToWorld(t2, -CORRIDOR_WIDTH);
        DrawLineEx(inner1, inner2, 3.0f / camera.zoom, Color{ 255, 100, 100, 150 });

        Vector2 outer1 = spiralToWorld(t1, CORRIDOR_WIDTH);
        Vector2 outer2 = spiralToWorld(t2, CORRIDOR_WIDTH);
        DrawLineEx(outer1, outer2, 3.0f / camera.zoom, Color{ 255, 100, 100, 150 });
    }
}

void drawObstacle(const Obstacle& obstacle, Camera2D camera) {
    float gapTop = obstacle.gapCenter + OBSTACLE_GAP / 2.0f;
    float gapBottom = obstacle.gapCenter - OBSTACLE_GAP / 2.0f;
    int segments = 30;

    float currentRadius = spiralRadius(obstacle.theta);
    float halfAngularWidth = (OBSTACLE_VISUAL_WIDTH / 2.0f) / currentRadius;
    float thetaStart = obstacle.theta - halfAngularWidth;
    float thetaEnd = obstacle.theta + halfAngularWidth;
    float thickness = OBSTACLE_THICKNESS / camera.zoom;

    for (int i = 0; i < segments; i++) {
        float t = thetaStart + (thetaEnd - thetaStart) * (float)i / segments;
        Vector2 inner = spiralToWorld(t, -CORRIDOR_WIDTH);
        Vector2 gap = spiralToWorld(t, gapBottom);
        float distAlongObstacle = (CORRIDOR_WIDTH - gapBottom) * (float)i / segments;
        int stripeIndex = (int)(distAlongObstacle / 10.0f);
        Color color = (stripeIndex % 2 == 0) ? RED : WHITE;
        DrawLineEx(inner, gap, thickness * 2.5f, color);
    }

    for (int i = 0; i < segments; i++) {
        float t = thetaStart + (thetaEnd - thetaStart) * (float)i / segments;
        Vector2 gap = spiralToWorld(t, gapTop);
        Vector2 outer = spiralToWorld(t, CORRIDOR_WIDTH);
        float distAlongObstacle = (CORRIDOR_WIDTH - gapTop) * (float)i / segments;
        int stripeIndex = (int)(distAlongObstacle / 10.0f);
        Color color = (stripeIndex % 2 == 0) ? WHITE : RED;
        DrawLineEx(gap, outer, thickness * 2.5f, color);
    }
}

void drawBird(const Bird& bird, Camera2D camera, Texture2D birdTexture) {
    float size = 30.0f / camera.zoom;

    if (birdTexture.id > 0) {
        Color tint = bird.isAlive ? WHITE : GRAY;
        Rectangle source = { 0, 0, (float)birdTexture.width, (float)birdTexture.height };
        Rectangle dest = { bird.position.x, bird.position.y, size, size };
        Vector2 origin = { size / 2.0f, size / 2.0f };
        DrawTexturePro(birdTexture, source, dest, origin, bird.rotation, tint);
    }
    else {
        float triSize = 15.0f / camera.zoom;
        Color birdColor = bird.isAlive ? YELLOW : GRAY;
        Color outlineColor = bird.isAlive ? ORANGE : DARKGRAY;

        Vector2 forward = { cosf(bird.rotation * DEG2RAD), sinf(bird.rotation * DEG2RAD) };
        Vector2 right = { -forward.y, forward.x };

        Vector2 tip = { bird.position.x + forward.x * triSize, bird.position.y + forward.y * triSize };
        Vector2 left = { bird.position.x - forward.x * triSize * 0.5f + right.x * triSize * 0.6f,
                         bird.position.y - forward.y * triSize * 0.5f + right.y * triSize * 0.6f };
        Vector2 right_pt = { bird.position.x - forward.x * triSize * 0.5f - right.x * triSize * 0.6f,
                             bird.position.y - forward.y * triSize * 0.5f - right.y * triSize * 0.6f };

        DrawTriangle(tip, left, right_pt, birdColor);
        DrawTriangleLines(tip, left, right_pt, outlineColor);
    }

    DrawCircleV(bird.position, 3.0f / camera.zoom, bird.isAlive ? RED : DARKGRAY);
}