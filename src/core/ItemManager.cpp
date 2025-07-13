#include "core/ItemManager.hpp"

#include <algorithm>

#include <raymath.h>

void ItemManager::Update(float deltaTime, const Vector3& playerPosition, const BlockList& nearbyBlocks) {
    for (auto& item : items) item->Update(deltaTime, nearbyBlocks);
    
    items.erase(std::remove_if(items.begin(), items.end(),
        [](const std::shared_ptr<ItemEntity>& item) { return item->IsExpired(); }
    ), items.end());

    if (IsKeyPressed(KEY_E)) {
        for (auto it = items.begin(); it != items.end(); it++) {
            float distance = Vector3Distance((*it)->GetPosition(), playerPosition);
            if (distance <= 1.5f && (*it)->CanBePickedUp()) {                
                auto collectedItem = (*it)->TakeItem();
                bool added = false;
                if (hotbar && hotbar->AddItem(collectedItem)) {
                    TraceLog(LOG_DEBUG, "Item adicionado à Hotbar");
                    added = true;
                }
                if (added) {
                    (*it)->Update(9999, nearbyBlocks);
                    TraceLog(LOG_TRACE, "Sumiu");
                }
                break;
            }
        }
    }
}

void ItemManager::Draw() const { for (const auto& item : items) item->Draw(); }

void ItemManager::AddItem(std::shared_ptr<ItemEntity> item) { items.push_back(item); }

std::vector<std::shared_ptr<ItemEntity>> ItemManager::GetNearbyItems(const Vector3& position, float radius) const {
    std::vector<std::shared_ptr<ItemEntity>> nearby;
    for (const auto& item : items) if (Vector3Distance(item->GetPosition(), position) <= radius) nearby.push_back(item);
    return nearby;
}

void ItemManager::SetHotbar(Hotbar* hotbar) { this->hotbar = hotbar; }

void ItemManager::SetInventory(Inventory* inventory) { this->inventory = inventory; }