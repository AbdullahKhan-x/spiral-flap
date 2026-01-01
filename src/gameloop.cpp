#include "gameloop.h"
#include "raylib.h"

void GameLoop::Draw() {
	BeginDrawing();
	ClearBackground(WHITE);
	EndDrawing();
}

void GameLoop::Update() {}

void GameLoop::Input() {
	if (IsKeyPressed(KEY_ESCAPE)) CloseWindow();
}
