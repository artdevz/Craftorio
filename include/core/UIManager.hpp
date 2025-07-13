#pragma once

#include "items/Item.hpp"
#include "ui/Hotbar.hpp"

class UIManager {
    
public:
    static void DrawItem(const Item* item, float x, float y, float size);

    static void DrawHotbar(const Hotbar& hotbar);

    // static void DrawInventory(const Inventory& inventory);

};