#ifndef GAME_H
#define GAME_H

#include "raylib.h"
#include <vector>

// Spiral parameters
extern const float SPIRAL_A;
extern const float SPIRAL_B;
extern const float CORRIDOR_WIDTH;

// Obstacle parameters
extern const float OBSTACLE_GAP;
extern const float OBSTACLE_THICKNESS;
extern const float OBSTACLE_SPACING;
extern const float OBSTACLE_VISUAL_WIDTH;
extern const float OBSTACLE_COLLISION_WIDTH;

// Physics constants
extern const float FORWARD_SPEED;
extern const float GRAVITY;
extern const float FLAP_FORCE;
extern const float RADIAL_DAMPING;

// Camera settings
extern const float CAMERA_SMOOTHING;
extern const float CAMERA_ZOOM;
extern const bool ROTATE_CAMERA;

// Game States
enum GameState {
    MENU,
    PLAYING,
    GAME_OVER
};

// Obstacle definition
struct Obstacle {
    float theta;
    float gapCenter;
    bool passed;
};

// Bird state
struct Bird {
    float theta;
    float radialVelocity;
    float radialOffset;
    Vector2 position;
    float rotation;
    bool isAlive;
};

// Spiral math functions
float spiralRadius(float theta);
Vector2 spiralToWorld(float theta, float radiusOffset = 0.0f);
Vector2 spiralTangent(float theta);
Vector2 spiralNormal(float theta);

// Bird functions
void resetBird(Bird& bird);
void updateBird(Bird& bird, float dt);
void flapBird(Bird& bird);

// Collision functions
bool checkCollision(const Bird& bird);
bool checkObstacleCollision(const Bird& bird, const Obstacle& obstacle);

// Obstacle functions
void generateObstacles(std::vector<Obstacle>& obstacles, float birdTheta);

// Rendering functions
void drawSpiral(float startTheta, float endTheta, int segments, Camera2D camera);
void drawObstacle(const Obstacle& obstacle, Camera2D camera);
void drawBird(const Bird& bird, Camera2D camera, Texture2D birdTexture);

#endif