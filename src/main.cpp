#include <memory>
#include <raylib.h>
#include "screens/Game.hpp"
#include "core/Window.hpp"

int main() {
    auto window = std::make_unique<Window>(1280, 720, 120, "Unnamed Game");
    Game game;
    game.Init();

    while (!WindowShouldClose()) {
        game.Update();
        game.Draw();
    }

    CloseWindow();
    return 0;
}