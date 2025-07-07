#pragma once
#include "entities/PhysicsEntity.hpp"
#include "items/Item.hpp"
#include <memory>

class Block;
using BlockList = std::vector<std::shared_ptr<Block>>;

class ItemEntity : public PhysicsEntity {

public:
    ItemEntity(std::unique_ptr<Item> item, const Vector3& position);
    ~ItemEntity() override = default;

    // void Update(float deltaTime) override;
    void Update(float deltaTime, const BlockList& nearbyBlocks);
    void Draw() const override;

    bool CanBePickedUp() const;
    bool IsExpired() const;

    std::shared_ptr<Item> TakeItem();

private:
    std::shared_ptr<Item> item;
    float pickupCooldown = 0.5f;
    float lifespan = 300.0f;

};