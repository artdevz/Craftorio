#include "entities/ItemEntity.hpp"

#include "items/ItemAgreggator.hpp"

ItemEntity::ItemEntity(std::unique_ptr<Item> it, const Vector3& position) :
    item(std::move(it)) {
        this->position = position;
    }

// void ItemEntity::Update(float deltaTime) {}

void ItemEntity::Update(float deltaTime, const BlockList& nearbyBlocks) {
    PhysicsEntity::Update(deltaTime, nearbyBlocks);

    if (pickupCooldown > 0.0f) pickupCooldown -= deltaTime;
    if (lifespan > 0.0f) lifespan -= deltaTime;
}

void ItemEntity::Draw() const { 
    TraceLog(LOG_TRACE, "Desenhando...");
    if (!item) return;

    Color color = GRAY;

    switch(item->GetItemType()) {
        case ItemType::BLOCK: {
            auto wood = dynamic_cast<WoodItem*>(item.get());
            if (wood) {
                switch(wood->GetWoodType()) {
                    case WoodType::OAK: color = DARKBROWN; break;
                    case WoodType::SPRUCE: color = BLACK; break;
                    default: color = GRAY; break;
                }
            }
            break;
        }

        case ItemType::TOOL:
            color = DARKGRAY;
            break;

        case ItemType::WEAPON:
            color = RED;
            break;

        default:
            color = GRAY;
            break;
    }

    DrawCube({position.x + 0.5f, position.y + 0.15f, position.z + 0.5f}, 0.3f, 0.3f, 0.3f, color);
    DrawCubeWires({position.x + 0.5f, position.y + 0.15f, position.z + 0.5f}, 0.3f, 0.3f, 0.3f, GRAY);
}
    
bool ItemEntity::CanBePickedUp() const { 
    return pickupCooldown <= 0.0f;
}

bool ItemEntity::IsExpired() const { 
    return lifespan <= 0.0f; 
}

std::shared_ptr<Item> ItemEntity::TakeItem() {
    TraceLog(LOG_DEBUG, "Pegou o Item");
    return item;
}