#pragma once

#include <memory>

#include "items/Item.hpp"

class Hotbar {
    
public:
    Hotbar();

    void Update();
    void Draw();

    bool AddItem(std::shared_ptr<Item> item);
    
    std::shared_ptr<Item> GetLeftHandItem() const;
    std::shared_ptr<Item> GetRightHandItem() const;

private:
    std::shared_ptr<Item> slots[12];
    int selectedSlot = 0;

};