#include "entities/ItemEntity.hpp"

#include "enums/LeafType.hpp"
#include "enums/WoodType.hpp"

#include "items/ItemAgreggator.hpp"

ItemEntity::ItemEntity(std::unique_ptr<Item> it, const Vector3& position) :
    item(std::move(it)) {
        this->position = position;
        SetBoundingBox( { { -0.14f, 0.0f, -0.14f }, { 0.14f, 0.3f, 0.14f } } );
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
                    case WoodType::OAK: color = GetColorForWood(WoodType::OAK); break;
                    case WoodType::SPRUCE: color = GetColorForWood(WoodType::SPRUCE); break;
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

    DrawCube({position.x + 0.0f, position.y + 0.15f, position.z + 0.0f}, 0.3f, 0.3f, 0.3f, color);
    //TraceLog(LOG_DEBUG, "Position %f, %f, %f", position.x, position.y, position.z);
    DrawCubeWires({position.x + 0.0f, position.y + 0.15f, position.z + 0.0f}, 0.3f, 0.3f, 0.3f, GRAY);
    //BoundingBox test = GetWorldBoundingBox(GetPosition());
    //TraceLog(LOG_DEBUG, "BoundingMin: %f, %f, %f", test.min.x, test.min.y, test.min.z);
    //TraceLog(LOG_DEBUG, "BoundingMax: %f, %f, %f", test.max.x, test.max.y, test.max.z);
    DrawBoundingBox(GetWorldBoundingBox(GetPosition()), RED);
}
    
bool ItemEntity::CanBePickedUp() const { 
    return pickupCooldown <= 0.0f;
}

bool ItemEntity::IsExpired() const { 
    return lifespan <= 0.0f; 
}

std::shared_ptr<Item> ItemEntity::TakeItem() {
    TraceLog(LOG_DEBUG, "Pegando item");
    return item;
}