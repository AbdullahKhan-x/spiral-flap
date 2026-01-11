#include "raylib.h"
#include "game.h"
#include "menu.h"
#include "score.h"
#include <vector>

int main() {
    // Initialize window
    const int screenWidth = 1200;
    const int screenHeight = 800;

    InitWindow(screenWidth, screenHeight, "Spiral Flappy Bird");
    SetTargetFPS(60);

    // Load bird texture - try multiple paths
    Texture2D birdTexture = LoadTexture("bird.png");
    if (birdTexture.id == 0) birdTexture = LoadTexture("assets/bird.png");
    if (birdTexture.id == 0) birdTexture = LoadTexture("../bird.png");
    if (birdTexture.id == 0) birdTexture = LoadTexture("../../bird.png");

    // Game variables
    Bird bird;
    std::vector<Obstacle> obstacles;
    GameState state = MENU;
    int score = 0;
    int highScore = LoadHighScore();

    // Initialize functionality
    auto resetGame = [&]() {
        resetBird(bird);
        obstacles.clear();
        generateObstacles(obstacles, bird.theta);
        score = 0;
        state = PLAYING;
        };

    resetBird(bird); // Init bird for background

    // Initialize camera
    Camera2D camera = { 0 };
    camera.target = bird.position;
    camera.offset = { screenWidth / 2.0f, screenHeight / 2.0f };
    camera.rotation = 0.0f;
    camera.zoom = CAMERA_ZOOM;

    Vector2 smoothTarget = bird.position;
    float smoothRotation = 0.0f;

    // Game loop
    while (!WindowShouldClose()) {
        float dt = GetFrameTime();

        // --- UPDATE ---
        switch (state) {
        case MENU:
            if (IsKeyPressed(KEY_SPACE) || IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                resetGame();
            }
            // Background animation
            camera.rotation += 10.0f * dt;
            break;

        case PLAYING:
            // Input
            if (IsKeyPressed(KEY_SPACE) || IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                flapBird(bird);
            }

            // Physics
            updateBird(bird, dt);
            generateObstacles(obstacles, bird.theta);

            // Collision
            if (checkCollision(bird)) {
                bird.isAlive = false;
                state = GAME_OVER;
            }

            for (auto& obstacle : obstacles) {
                // Score update
                if (!obstacle.passed && bird.theta > obstacle.theta) {
                    obstacle.passed = true;
                    score++;
                }

                if (checkObstacleCollision(bird, obstacle)) {
                    bird.isAlive = false;
                    state = GAME_OVER;
                    break;
                }
            }

            // Camera follow
            smoothTarget.x += (bird.position.x - smoothTarget.x) * CAMERA_SMOOTHING;
            smoothTarget.y += (bird.position.y - smoothTarget.y) * CAMERA_SMOOTHING;
            camera.target = smoothTarget;

            if (ROTATE_CAMERA) {
                Vector2 tangent = spiralTangent(bird.theta);
                float targetRotation = atan2f(tangent.y, tangent.x) * RAD2DEG - 90.0f;
                float rotDiff = targetRotation - smoothRotation;
                while (rotDiff > 180.0f) rotDiff -= 360.0f;
                while (rotDiff < -180.0f) rotDiff += 360.0f;
                smoothRotation += rotDiff * CAMERA_SMOOTHING;
                camera.rotation = smoothRotation;
            }
            break;

        case GAME_OVER:
            if (score > highScore) {
                highScore = score;
                SaveHighScore(highScore);
            }

            if (IsKeyPressed(KEY_SPACE) || IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                resetGame();
            }

            // Return to Main Menu
            if (IsKeyPressed(KEY_M)) {
                resetBird(bird);
                obstacles.clear();
                generateObstacles(obstacles, bird.theta);
                state = MENU;
            }
            break;
        }

        // --- DRAW ---
        BeginDrawing();
        ClearBackground(SKYBLUE);

        BeginMode2D(camera);
        float spiralStart = fmaxf(0.0f, bird.theta - PI * 2.0f);
        float spiralEnd = bird.theta + PI * 6.0f;
        drawSpiral(spiralStart, spiralEnd, 500, camera);

        for (const auto& obstacle : obstacles) {
            drawObstacle(obstacle, camera);
        }

        if (state == PLAYING || state == GAME_OVER) {
            drawBird(bird, camera, birdTexture);
        }
        EndMode2D();

        // UI based on state
        if (state == MENU) {
            drawMainMenu(screenWidth, screenHeight, highScore);
        }
        else if (state == PLAYING) {
            drawPlayingUI(screenWidth, screenHeight, score, highScore);
        }
        else if (state == GAME_OVER) {
            drawGameOverScreen(screenWidth, screenHeight, score, highScore);
        }

        EndDrawing();
    }

    UnloadTexture(birdTexture);
    CloseWindow();
    return 0;
}