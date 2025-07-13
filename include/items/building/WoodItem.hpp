#pragma once

#include <string>

#include "enums/WoodType.hpp"
#include "items/Item.hpp"

class WoodItem : public Item {

public:
    WoodItem(WoodType type, int count = 1);
    
    void Update() override;
    void Draw() const override;
    void Interact() override;

    const std::string& GetName() const noexcept override;
    ItemType GetItemType() const override { return ItemType::BLOCK; }

    WoodType GetWoodType() const { return woodType; }

private:
    WoodType woodType;
    int count;

};