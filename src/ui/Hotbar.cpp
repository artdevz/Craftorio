#include "ui/Hotbar.hpp"

#include <string>

#include <raylib.h>

#include "core/Input.hpp"
#include "core/UIManager.hpp"
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
        
        Color background = (i == selectedSlot || i == (selectedSlot + 6))? Color{ 200, 200, 200, 80 } : Color{ 80, 80, 80, 80 };
        DrawRectangleRec(slotRect, background);

        DrawRectangleLinesEx(slotRect, 2, BLACK);
        
        if (i < 6) DrawText(("L" + std::to_string(i + 1)).c_str(), slotRect.x + 10, slotRect.y + 10, 14, WHITE);
        if (i > 5) DrawText(("R" + std::to_string(i - 5)).c_str(), slotRect.x + 10, slotRect.y + 10, 14, WHITE);
    
        UIManager::DrawItem(slots[i].get(), slotRect.x+20, slotRect.y+20, 24);
        if (selectedSlot == i) {
            if(slots[i]) DrawText(slots[i].get()->GetName().c_str(), slotRect.x, slotRect.y - 15, 16, BLACK);
            if(slots[i+6]) DrawText(slots[i+6].get()->GetName().c_str(), slotRect.x+6*72, slotRect.y - 15, 16, BLACK);
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

std::shared_ptr<Item> Hotbar::GetLeftHandItem() const { return (selectedSlot >= 0 && selectedSlot < 6)? slots[selectedSlot] : nullptr; }

std::shared_ptr<Item> Hotbar::GetRightHandItem() const { return (selectedSlot >= 0 && selectedSlot < 6)? slots[selectedSlot+6] : nullptr; }