#pragma once

#include <memory>
#include <unordered_map>
#include <vector>

#include "core/ItemManager.hpp"
#include "enums/BlockType.hpp"
#include "items/Item.hpp"
#include "utils/Vector2i.hpp"

#include "world/Block.hpp"
#include "world/Chunk.hpp"

/**
 * @brief Gerencia blocos e chunks do jogo
 * 
 * Centraliza o carregamento, descarregamento de blocos e chunks
 */

class BlockManager {

public:
    void AddBlock(std::shared_ptr<Block> block);
    void AddBlockAt(Vector3 position, BlockType type);
    void LoadChunkAt(int chunkX, int chunkZ);
    void Update();
    void Draw(const Vector3& playerPosition, float maxRenderDistance) const;
    void Interact(float deltaTime, const Vector3& origin, const Vector3& direction, float maxDistance, std::shared_ptr<Item> item, ItemManager* itemManager = nullptr);

    const std::vector<std::shared_ptr<Block>>& GetBlocks() const;
    std::vector<std::shared_ptr<Block>> GetNearbyBlocks(const Vector3& playerPosition, float radius);

    static Vector2i GetChunkCoords(const Vector3& position) {
        return Vector2i{ (int)floor(position.x / Chunk::SIZE), (int)floor(position.z / Chunk::SIZE) };
    }

private:
    std::vector<std::shared_ptr<Block>> blocks;
    std::unordered_map<Vector2i, Chunk> chunks;

};