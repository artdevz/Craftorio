#include <raylib.h>
#include "ui/Inventory.hpp"
#include "core/Input.hpp"
#include "core/WindowManager.hpp"

bool Inventory::inventoryState = false;

Inventory::Inventory() {}

void Inventory::Update() { if (Input::IsInventoryTogglePressed()) inventoryState = !inventoryState; }

void Inventory::Draw() {
    float width = WindowManager::GetResolution().x, height = WindowManager::GetResolution().y;
    if (inventoryState) {
        DrawRectangle(width - 1076, height - 600, 876, 400, DARKGRAY);
        DrawText("Inventory", width - 1066, height - 590, 20, WHITE);
        for (int i = 0; i < 12; i++) {
            for (int j = 0; j < 4; j++) {
                DrawRectangleLinesEx( { (width - 1068) + i * 72, (height - 550) + j * 72, 64, 64}, 2, BLACK );
            }
        }
    }
}