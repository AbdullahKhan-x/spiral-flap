#include "raylib.h"
#include "gameloop.h"
#include "bird.h"

int main() {
	const int SCREEN_WIDTH = 800;
	const int SCREEN_HEIGHT = 600;
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
