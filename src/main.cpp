#include "raylib.h"
#include "game.h"

int main()
{
    InitWindow(800, 600, "Spiral Flap");
    SetTargetFPS(60);

    Game game;
    game.Init();

    while (!WindowShouldClose()) {
        float dt = GetFrameTime();
        game.Input();
        game.Update(dt);
        game.Draw();
    }

    CloseWindow();
    return 0;
}
