#include <raylib.h>
#include <string>
#include "ui/Hotbar.hpp"
#include "core/Input.hpp"
#include "core/WindowManager.hpp"

Hotbar::Hotbar() {}

void Hotbar::Update() {
    int hotbarKey = Input::IsHotbarKeyPressed();
    if (hotbarKey != -1) selectedSlot = hotbarKey;
}

void Hotbar::Draw() {
    float width = WindowManager::resolution.x, height = WindowManager::resolution.y;
    for (int i = 0; i < 8; i++) {
        Rectangle slotRect = { (width - 924) + i * 72, height - 80, 64, 64 };
        DrawRectangleRec(slotRect, DARKGRAY);
        if (i == selectedSlot || i == (selectedSlot + 4)) {
            DrawRectangleRec(slotRect, LIGHTGRAY);
            if (i < 4) DrawText(("L" + std::to_string(i + 1)).c_str(), slotRect.x + 10, slotRect.y + 10, 14, BLACK);
            if (i > 3) DrawText(("R" + std::to_string(i - 3)).c_str(), slotRect.x + 10, slotRect.y + 10, 14, BLACK);
        }
        DrawRectangleLinesEx(slotRect, 2, BLACK);
    }
}