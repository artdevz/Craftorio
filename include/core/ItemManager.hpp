#pragma once

#include <memory>
#include <vector>

#include <raylib.h>

#include "entities/ItemEntity.hpp"
#include "ui/Hotbar.hpp"
#include "ui/Inventory.hpp"

/**
 * @brief Gerencia itens do jogo, sendo dropados ou guardados
 * 
 * Centraliza o carregamento, descarregamento e o desenho de todos os itens
 */

class ItemManager {

public:
    void Update(float deltaTime, const Vector3& playerPosition, const BlockList& nearbyBlocks);
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