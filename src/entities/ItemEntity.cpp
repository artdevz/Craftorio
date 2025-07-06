#include "entities/ItemEntity.hpp"

ItemEntity::ItemEntity(std::unique_ptr<Item> itemPtr, const Vector3& position) :
    item(std::move(itemPtr)), position(position) {}

void ItemEntity::Update(float deltaTime) {
    if (pickupCooldown > 0.0f) pickupCooldown -= deltaTime;
    if (lifespan > 0.0f) lifespan -= deltaTime;
}

void ItemEntity::Draw() const {
    if (item) DrawCube(position, 0.4f, 0.4f, 0.4f, GRAY);
}
    
Vector3 ItemEntity::GetPosition() const { return position; }
void ItemEntity::SetPosition(Vector3 position) { this->position = position; } 

bool ItemEntity::CanBePickedUp() const { return pickupCooldown <= 0.0f; }
bool ItemEntity::IsExpired() const { return lifespan <= 0.0f; }

std::shared_ptr<Item> ItemEntity::TakeItem() {
    TraceLog(LOG_DEBUG, "Pegou o Item");
    return item;
}