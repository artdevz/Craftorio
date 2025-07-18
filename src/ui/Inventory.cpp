#include "ui/Inventory.hpp"

#include <raylib.h>

#include "core/Input.hpp"
#include "core/UIManager.hpp"
#include "core/WindowManager.hpp"

bool Inventory::inventoryState = false;

Inventory::Inventory() {}

void Inventory::Update() { if (Input::IsInventoryTogglePressed()) inventoryState = !inventoryState; }

void Inventory::Draw() {
    if (inventoryState) {
        float width = WindowManager::GetResolution().x, height = WindowManager::GetResolution().y;

        Color inventoryBackground = { 80, 80, 80, 80 };
        DrawRectangle(width - 1076, height - 600, 876, 400, inventoryBackground);
        DrawText("Inventory", width - 1066, height - 590, 20, WHITE);
        
        for (int i = 0; i < 12; i++) {
            for (int j = 0; j < 4; j++) {
                Rectangle slotRectLine = { (width - 1068) + i * 72, (height - 550) + j * 72, 64, 64 };
                DrawRectangleLinesEx( slotRectLine, 2, BLACK );
                UIManager::DrawItem(slots[i+12*j].get(), slotRectLine.x+20, slotRectLine.y+20, 24);
            }
        }
    }
}

bool Inventory::AddItem(std::shared_ptr<Item> item) {
    for (auto& slot : slots) {
        if (!slot) {
            slot = std::move(item);
            return true;
        }
    }
    return false;
}