#include "ui/Hotbar.hpp"

#include <string>

#include <raylib.h>

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
        
        Color background = (i == selectedSlot || i == (selectedSlot + 6))? LIGHTGRAY : DARKGRAY;
        DrawRectangleRec(slotRect, background);

        DrawRectangleLinesEx(slotRect, 2, BLACK);
        
        if (i < 6) DrawText(("L" + std::to_string(i + 1)).c_str(), slotRect.x + 10, slotRect.y + 10, 14, BLACK);
        if (i > 5) DrawText(("R" + std::to_string(i - 5)).c_str(), slotRect.x + 10, slotRect.y + 10, 14, BLACK);
    
        if (slots[i]) {
            DrawRectangle((int)(slotRect.x + 20), (int)(slotRect.y + 20), 24, 24, GRAY);
        }
    }
}

bool Hotbar::AddItem(std::shared_ptr<Item> item) {
    for (auto& slot : slots) {
        if (!slot) {
            slot = std::move(item);
            return true;
        }
    }
    return false;
}

// std::pair<std::shared_ptr<Item>, std::shared_ptr<Item>> Hotbar::GetSelectedItems() const {
//     if (selectedSlot >= 0 && selectedSlot < 6) return { slots[selectedSlot], slots[selectedSlot+6] };
//     return {nullptr, nullptr};
// }

std::shared_ptr<Item> Hotbar::GetLeftHandItem() const { return (selectedSlot >= 0 && selectedSlot < 6)? slots[selectedSlot] : nullptr; }

std::shared_ptr<Item> Hotbar::GetRightHandItem() const { return (selectedSlot >= 0 && selectedSlot < 6)? slots[selectedSlot+6] : nullptr; }