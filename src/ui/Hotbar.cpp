#include <raylib.h>
#include <string>
#include "ui/Hotbar.hpp"
#include "core/Input.hpp"
#include "core/WindowManager.hpp"

Hotbar::Hotbar() {}

void Hotbar::Update() {
    int hotbarKey = Input::GetHotbarKeyPressed();
    if (hotbarKey != -1) selectedSlot = hotbarKey;
}

void Hotbar::Draw() {
    float width = WindowManager::GetResolution().x, height = WindowManager::GetResolution().y;
    for (int i = 0; i < 12; i++) {
        Rectangle slotRect = { (width - 1068) + i * 72, height - 80, 64, 64 };
        DrawRectangleRec(slotRect, DARKGRAY);
        if (i == selectedSlot || i == (selectedSlot + 6)) {
            DrawRectangleRec(slotRect, LIGHTGRAY);
            if (i < 6) DrawText(("L" + std::to_string(i + 1)).c_str(), slotRect.x + 10, slotRect.y + 10, 14, BLACK);
            if (i > 5) DrawText(("R" + std::to_string(i - 5)).c_str(), slotRect.x + 10, slotRect.y + 10, 14, BLACK);
        }
        DrawRectangleLinesEx(slotRect, 2, BLACK);
    }
}