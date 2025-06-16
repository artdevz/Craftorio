#include <memory>
#include <raylib.h>
#include "screens/Game.hpp"
#include "core/WindowManager.hpp"

int main() {
    SetTraceLogLevel(LOG_DEBUG);
    auto window = std::make_unique<WindowManager>(1280, 720, 999999, "Unnamed Game");
    Game game;
    game.Init();

    while (!WindowShouldClose()) {
        game.Update();
        game.Draw();
    }

    CloseWindow();
    return 0;
}