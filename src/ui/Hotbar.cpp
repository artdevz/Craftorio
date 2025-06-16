#include <raylib.h>
#include "ui/Hotbar.hpp"
#include "core/WindowManager.hpp"

Hotbar::Hotbar() {}

void Hotbar::Update() {
    Draw();
}

void Hotbar::Draw() {
    float width = WindowManager::resolution.x, height = WindowManager::resolution.y;
    float hotbarPosX = width - 924;
    for (int i = 1; i <= 8; i++) {
        DrawRectangleRec( { hotbarPosX, height - 80, 64, 64 }, LIGHTGRAY );
        hotbarPosX += 72;
    }
}