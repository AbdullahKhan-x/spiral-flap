#include "gameloop.h"
#include "raylib.h"

void GameLoop::Draw() {
	BeginDrawing();
	ClearBackground({255, 3, 62});
	EndDrawing();
}

void GameLoop::Update() {}

void GameLoop::Input() {
	if (IsKeyPressed(KEY_ESCAPE)) CloseWindow();
}
