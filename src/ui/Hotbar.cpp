#include <raylib.h>
#include "ui/Hotbar.hpp"
#include "core/Window.hpp"

Hotbar::Hotbar() {}

void Hotbar::Update() {
    Draw();
}

void Hotbar::Draw() {
    float width = Window::resolution.x, height = Window::resolution.y;
    float hotbarPosX = 356;
    for (int i = 1; i <= 8; i++) {
        DrawRectangleRec( { hotbarPosX, 640, 64, 64 }, LIGHTGRAY );
        hotbarPosX += 72;
    }
}