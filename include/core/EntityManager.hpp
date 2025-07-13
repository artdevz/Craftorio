#pragma once

#include <memory>
#include <vector>

#include "entities/Entity.hpp"
#include "world/Block.hpp"

using BlockList = std::vector<std::shared_ptr<Block>>;

/**
 * @brief Gerencia entidades do jogo
 * 
 * Centraliza o carregamento, descarregamento e desenho das entidades
 */

class EntityManager {

public:
    void AddEntity(std::shared_ptr<Entity> entity);

    void Update(float deltaTime, const BlockList& nearbyBlocks);
    void Draw() const;

    void CleanUp();

private:
    std::vector<std::shared_ptr<Entity>> entities;

};