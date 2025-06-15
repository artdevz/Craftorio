#include <raylib.h>
#include "ui/Inventory.hpp"
#include "core/Input.hpp"

bool Inventory::inventoryState = false;

Inventory::Inventory() {}

void Inventory::Update() { if (Input::IsInventoryTogglePressed()) inventoryState = !inventoryState; }

void Inventory::Draw() {
    if (inventoryState) {
        DrawRectangle(100, 100, 600, 400, LIGHTGRAY);
        DrawText("Inventory", 120, 120, 20, DARKGRAY);
    }
}