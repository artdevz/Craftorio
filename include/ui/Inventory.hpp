#pragma once

#include <memory>

#include "items/Item.hpp"

class Inventory {

public:
    Inventory();

    void Update();
    void Draw();

    bool AddItem(std::shared_ptr<Item> item);

private:
    std::shared_ptr<Item> slots[48];
    static bool inventoryState;

};