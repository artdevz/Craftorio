#pragma once
#include <array>
#include <memory>
#include "items/Item.hpp"

class Hotbar {
    
public:
    Hotbar();

    void Update();
    void Draw();

    bool AddItem(std::shared_ptr<Item> item);
    
    // std::pair<std::shared_ptr<Item>, std::shared_ptr<Item>> GetSelectedItems() const;
    std::shared_ptr<Item> GetLeftHandItem() const;
    std::shared_ptr<Item> GetRightHandItem() const;

private:
    std::shared_ptr<Item> slots[12];
    int selectedSlot = 0;

};