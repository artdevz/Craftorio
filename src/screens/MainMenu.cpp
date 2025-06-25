#include "screens/MainMenu.hpp"
#include <raylib.h>

MainMenu::MainMenu() {}

void MainMenu::Init() { 
    startGame = false; 
    buttons = {
        { {100, 160, 220, 40}, "Singleplayer", [this]() { startGame = true; } },
        { {100, 220, 220, 40}, "Multiplayer", [this]() {  } },
        { {100, 280, 220, 40}, "Quit Game", [this]() { shouldClose = true; } }
    };
}

void MainMenu::Update() { 
    if (IsKeyPressed(KEY_ENTER)) startGame = true; 
    for (auto& button : buttons) button.Update();
}

void MainMenu::Draw() {
    int width = GetScreenWidth(), height = GetScreenHeight();

    ClearBackground(BLACK);
    DrawText("Craftorio", width / 2 - MeasureText("Craftorio", width/15) / 2, height/24, width/15, WHITE);
    DrawText("Press ENTER to Play", width / 2 - MeasureText("Press ENTER to Play", width/60) / 2, height/2, width/60, WHITE);
    for (auto& button : buttons) button.Draw();
}

bool MainMenu::ShouldStartGame() const { return startGame; }

bool MainMenu::ShouldClose() const { return shouldClose; }