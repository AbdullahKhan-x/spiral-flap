#include "menu.h"
#include "raylib.h"

void drawMainMenu(int screenWidth, int screenHeight, int highScore) {
    DrawRectangle(0, 0, screenWidth, screenHeight, Fade(BLACK, 0.4f));

    const char* title = "SPIRAL FLAPPY BIRD";
    DrawText(title,
        screenWidth / 2 - MeasureText(title, 50) / 2,
        screenHeight / 3,
        50,
        WHITE);

    const char* startText = "Press SPACE to Start";
    DrawText(startText,
        screenWidth / 2 - MeasureText(startText, 30) / 2,
        screenHeight / 2,
        30,
        LIGHTGRAY);

    const char* highScoreText = TextFormat("High Score: %d", highScore);
    DrawText(highScoreText,
        screenWidth / 2 - MeasureText(highScoreText, 30) / 2,
        screenHeight / 2 + 50,
        30,
        GOLD);
}

void drawGameOverScreen(int screenWidth, int screenHeight, int score, int highScore) {
    const char* gameOverText = "GAME OVER";
    DrawText(gameOverText,
        screenWidth / 2 - MeasureText(gameOverText, 50) / 2,
        screenHeight / 3,
        50,
        RED);

    const char* scoreText = TextFormat("Score: %d", score);
    DrawText(scoreText,
        screenWidth / 2 - MeasureText(scoreText, 40) / 2,
        screenHeight / 2,
        40,
        WHITE);

    const char* highScoreText = TextFormat("High Score: %d", highScore);
    DrawText(highScoreText,
        screenWidth / 2 - MeasureText(highScoreText, 30) / 2,
        screenHeight / 2 + 50,
        30,
        GOLD);

    const char* restartText = "Press SPACE to Restart";
    DrawText(restartText,
        screenWidth / 2 - MeasureText(restartText, 20) / 2,
        screenHeight / 2 + 100,
        20,
        LIGHTGRAY);

    const char* menuText = "Press M for Main Menu";
    DrawText(menuText,
        screenWidth / 2 - MeasureText(menuText, 20) / 2,
        screenHeight / 2 + 130,
        20,
        LIGHTGRAY);
}

void drawPlayingUI(int screenWidth, int screenHeight, int score, int highScore) {
    DrawText(TextFormat("Score: %d", score),
        screenWidth / 2 - 50,
        50,
        40,
        WHITE);

    DrawText(TextFormat("High Score: %d", highScore),
        10,
        10,
        20,
        GOLD);
}