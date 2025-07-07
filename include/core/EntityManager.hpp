#pragma once
#include "entities/Entity.hpp"
#include "world/Block.hpp"
#include <vector>
#include <memory>

using BlockList = std::vector<std::shared_ptr<Block>>;

class EntityManager {

public:
    void AddEntity(std::shared_ptr<Entity> entity);

    void Update(float deltaTime, const BlockList& nearbyBlocks);
    void Draw() const;

    void CleanUp();

private:
    std::vector<std::shared_ptr<Entity>> entities;

};