#pragma once

#include <memory>
#include <vector>

#include "entities/LivingEntity.hpp"

class Block;

using BlockList = std::vector<std::shared_ptr<Block>>;

class Zombie : public LivingEntity {

public:
    Zombie();

    void Update(float deltaTime) override;
    void Update(float deltaTime, const BlockList& nearbyBlocks);
    void Draw() const override;

private:
    float moveSpeed;

};