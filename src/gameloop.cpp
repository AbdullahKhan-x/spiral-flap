#include "gameloop.h"
#include "raylib.h"
#include "map.h"

GameLoop::GameLoop() {
	// Configure the spiral
	config.a = 5.0f;
	config.angleStep = 0.05f;
	config.center = Vector2{ 400.0f, 300.0f };

	// Initialize spiral map
	initSpiralMap(spiralMap, config, 200);
}

void GameLoop::Draw() {
	BeginDrawing();
	ClearBackground({ 255, 3, 62 });

	// Draw the spiral
	drawSpiralMap(spiralMap, BLUE, 3.0f);

	EndDrawing();
}

void GameLoop::Update() {
	// Generate more spiral continuously
	generateNextChunk(spiralMap);
}

void GameLoop::Input() {
	if (IsKeyPressed(KEY_ESCAPE)) CloseWindow();
}
