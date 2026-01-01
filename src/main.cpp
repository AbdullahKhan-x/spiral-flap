#include "raylib.h"
#include "gameloop.h"

int main() {
	const int SCREEN_WIDTH = 1280;
	const int SCREEN_HEIGHT = 720;
	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "spiral flap");
	SetTargetFPS(30);

	GameLoop game;   // CAPITAL G — must match class name

	while (!WindowShouldClose()) {
		game.Input();
		game.Update();
		game.Draw();
	}

	CloseWindow();
	return 0;
}
