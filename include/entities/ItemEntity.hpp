#pragma once
#include "entities/Entity.hpp"
#include "items/Item.hpp"
#include <memory>

class ItemEntity : public Entity {

public:
    ItemEntity(std::unique_ptr<Item> item, const Vector3& position);

    void Update(float deltaTime) override;
    void Draw() const override;
    
    Vector3 GetPosition() const override;
    void SetPosition(Vector3 position) override;

    bool CanBePickedUp() const;
    bool IsExpired() const;

    std::shared_ptr<Item> TakeItem();

private:
    std::shared_ptr<Item> item;
    Vector3 position;
    float pickupCooldown = 0.5f;
    float lifespan = 300.0f;

};