#pragma once
#include "entities/ItemEntity.hpp"
#include "ui/Hotbar.hpp"
#include "ui/Inventory.hpp"
#include <memory>
#include <vector>
#include <raylib.h>

class ItemManager {

public:
    void Update(float deltaTime, const Vector3& playerPosition);
    void Draw() const;
    
    void AddItem(std::shared_ptr<ItemEntity> item);

    std::vector<std::shared_ptr<ItemEntity>> GetNearbyItems(const Vector3& position, float radius) const;

    void SetHotbar(Hotbar* hotbar);
    void SetInventory(Inventory* inventory);

private:
    std::vector<std::shared_ptr<ItemEntity>> items;
    Hotbar* hotbar = nullptr;
    Inventory* inventory = nullptr;

};